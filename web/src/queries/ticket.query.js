const pool = require('../services/db');

const getNextTicketId = async () => {
    const [rows] = await pool.query('SELECT COALESCE(MAX(id), 0) AS max_id FROM tickets');
    return rows[0].max_id + 1;
};

const createTicket = async (ticketData) => {
    const { ncNumber, clientId, email, profile, description, installationDate, reference, orderNumber } = ticketData;
    const [result] = await pool.query(
        `INSERT INTO tickets (nc_number, client_id, email, profil, description, installation_pose, reference, order_number, status)
         VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'pending_ai')`,
        [ncNumber, clientId, email, profile, description, installationDate, reference, orderNumber]
    );
    return result.insertId;
};

const getAllTickets = async () => {
    const [rows] = await pool.query(
        'SELECT id, nc_number, profil, status, ai_type_nc, gravity_label, gravity_score, created_at FROM tickets ORDER BY id DESC'
    );
    return rows;
};

const getTicketsByClientId = async (clientId) => {
    const [rows] = await pool.query(
        'SELECT id, nc_number, profil, status, ai_type_nc, gravity_label, gravity_score, created_at FROM tickets WHERE client_id = ? ORDER BY id DESC',
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

const updateTicketStatus = async (id, status) => {
    await pool.query('UPDATE tickets SET status = ?, updated_at = NOW() WHERE id = ?', [status, id]);
};

module.exports = {
    getNextTicketId,
    createTicket,
    getAllTickets,
    getTicketsByClientId,
    getTicketById,
    updateTicketStatus
};