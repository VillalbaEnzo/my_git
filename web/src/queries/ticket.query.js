const pool = require('../services/db');

const getNextTicketId = async () => {
    const [rows] = await pool.query('SELECT COALESCE(MAX(id), 0) AS max_id FROM tickets');
    return rows[0].max_id + 1;
};

const createTicket = async (ticketData) => {
    const { ncNumber, clientId, email, profile, description, installationDate, reference, orderNumber, photos } = ticketData;
    const photosJson = photos && photos.length > 0 ? JSON.stringify(photos) : null;
    const [result] = await pool.query(
        `INSERT INTO tickets (nc_number, client_id, email, profil, description, installation_pose, reference, order_number, status, photos)
         VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'pending_ai', ?)`,
        [ncNumber, clientId, email, profile, description, installationDate, reference, orderNumber, photosJson]
    );
    return result.insertId;
};

const getAllTickets = async () => {
    const [rows] = await pool.query(
        'SELECT * FROM tickets ORDER BY id DESC'
    );
    return rows;
};

const getTicketsByClientId = async (clientId) => {
    const [rows] = await pool.query(
        'SELECT * FROM tickets WHERE client_id = ? ORDER BY id DESC',
        [clientId]
    );
    return rows;
};

const getTicketById = async (id) => {
    const [rows] = await pool.query(`
        SELECT t.*, u.nom, u.type_client
        FROM tickets t
        LEFT JOIN users u ON t.client_id = u.id
        WHERE t.id = ?
    `, [id]);
    return rows[0];
};

const updateTicketAdminFields = async (id, data) => {
    const {status, ai_type_nc, ai_cause, ai_action_generale, ai_service_impacte, ai_resume, gravity_score, gravity_label} = data;
    await pool.query(
        `UPDATE tickets
         SET status = ?,
             ai_type_nc = ?,
             ai_cause = ?,
             ai_action_generale = ?,
             ai_service_impacte = ?,
             ai_resume = ?,
             gravity_score = ?,
             gravity_label = ?,
             updated_at = NOW()
         WHERE id = ?`,
        [status, ai_type_nc, ai_cause, ai_action_generale, ai_service_impacte, ai_resume, gravity_score, gravity_label, id]
    );
};

const getDashboardStats = async () => {
    const [activeNc] = await pool.query("SELECT COUNT(*) as count FROM tickets WHERE status IN ('open', 'in_progress')");
    const [avgScore] = await pool.query("SELECT AVG(ai_confiance) as avg FROM tickets WHERE ai_confiance IS NOT NULL");
    const [topCauses] = await pool.query("SELECT ai_cause, COUNT(*) as count FROM tickets WHERE ai_cause IS NOT NULL AND ai_cause != '' GROUP BY ai_cause ORDER BY count DESC LIMIT 3");
    const [urgentTickets] = await pool.query("SELECT * FROM tickets WHERE status IN ('open', 'in_progress') ORDER BY created_at DESC LIMIT 5");
    const [pendingTickets] = await pool.query("SELECT * FROM tickets WHERE status IN ('ai_completed', 'manual_completion_required') ORDER BY created_at DESC LIMIT 5");

    return {
        activeNcCount: activeNc[0].count || 0,
        avgScore: avgScore[0].avg ? (avgScore[0].avg * 100).toFixed(1) : 0,
        topCauses: topCauses,
        urgentTickets: urgentTickets,
        pendingTickets: pendingTickets
    };
};

const updateTicketFull = async (id, d) => {
    const pool = require('../services/db');
    await pool.query(`
        UPDATE tickets SET
            reference          = ?,
            order_number       = ?,
            installation_pose  = ?,
            ai_type_nc         = ?,
            ai_cause           = ?,
            ai_action_generale = ?,
            ai_service_impacte = ?,
            ai_resume          = ?,
            ai_confiance       = ?,
            gravity_detail     = ?,
            gravity_score      = ?,
            status             = ?
        WHERE id = ?`,
        [
            d.reference,
            d.order_number,
            d.installation_pose || null,
            d.ai_type_nc,
            d.ai_cause,
            d.ai_action_generale,
            d.ai_service_impacte,
            d.ai_resume,
            d.ai_confiance,
            d.gravity_detail,
            d.gravity_score,
            d.status,
            id
        ]
    );
};

module.exports = {
    getNextTicketId,
    createTicket,
    getAllTickets,
    getTicketsByClientId,
    getTicketById,
    getDashboardStats,
    updateTicketAdminFields,
    updateTicketFull
};