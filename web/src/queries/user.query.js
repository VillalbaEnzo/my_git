const pool = require('../services/db');

const findUserByEmail = async (email) => {
    const [rows] = await pool.query('SELECT * FROM users WHERE email = ?', [email]);
    return rows[0];
};

const createUser = async (userData) => {
    const { email, passwordHash, role, name, clientType } = userData;
    const [result] = await pool.query(
        `INSERT INTO users (email, password_hash, role, nom, type_client, must_change_password)
         VALUES (?, ?, ?, ?, ?, TRUE)`,
        [email, passwordHash, role, name, clientType]
    );
    return result.insertId;
};

const updatePassword = async (userId, passwordHash) => {
    await pool.query(
        'UPDATE users SET password_hash = ?, must_change_password = FALSE WHERE id = ?',
        [passwordHash, userId]
    );
};

const getAllUsers = async () => {
    const [rows] = await pool.query('SELECT id, email, role, nom, type_client, created_at FROM users ORDER BY id DESC');
    return rows;
};

const getUserById = async (id) => {
    const [rows] = await pool.query('SELECT id, email, role, nom, type_client FROM users WHERE id = ?', [id]);
    return rows[0];
};

const updateUser = async (id, userData) => {
    const { role, nom, typeClient, email } = userData;
    if (email) {
        await pool.query('UPDATE users SET role = ?, nom = ?, type_client = ?, email = ? WHERE id = ?', [role, nom, typeClient, email, id]);
    } else {
        await pool.query(
            'UPDATE users SET role = ?, nom = ?, type_client = ? WHERE id = ?',
            [role, nom, typeClient, id]
        );
    }
};

const forcePasswordReset = async (id, passwordHash) => {
    await pool.query(
        'UPDATE users SET password_hash = ?, must_change_password = TRUE WHERE id = ?',
        [passwordHash, id]
    );
};

const deleteUser = async (id) => {
    // await pool.query('DELETE FROM tickets WHERE client_id = ?', [id]);
    await pool.query('DELETE FROM users WHERE id = ?', [id]);
};

const savePasswordResetToken = async (email, token, expiryDate) => {
    await pool.query('UPDATE users SET reset_token = ?, reset_token_expires = ? WHERE email = ?', [token, expiryDate, email]);
};

const findUserByResetToken = async (token) => {
    const [rows] = await pool.query('SELECT * FROM users WHERE reset_token = ? AND reset_token_expires > NOW()', [token]);
    return rows[0];
};

const clearResetTokenAndUpdatePassword = async (userId, hashedPassword) => {
    await pool.query('UPDATE users SET password_hash = ?, reset_token = NULL, reset_token_expires = NULL, must_change_password = FALSE WHERE id = ?', [hashedPassword, userId]);
};

const updateUserInfo = async (id, nom, email) => {
    await pool.query('UPDATE users SET nom = ?, email = ? WHERE id = ?', [nom, email, id]);
}

const insertAuditLog = async (userId, emailAttempt, actionType, ip, userAgent, details = null) => {
    const detailsJson = details ? JSON.stringify(details) : null;
    await pool.query(
        'INSERT INTO audit_logs (user_id, email_attempt, action_type, ip_address, user_agent, details) VALUES (?, ?, ?, ?, ?, ?)',
        [userId, emailAttempt, actionType, ip, userAgent, detailsJson]
    );
};

const getAuditLogs = async () => {
    const [rows] = await pool.query(`
        SELECT a.*, u.role, u.nom
        FROM audit_logs a
        LEFT JOIN users u ON a.user_id = u.id
        ORDER BY a.created_at DESC
        LIMIT 200
    `);
    return rows;
};

module.exports = {
    findUserByEmail,
    createUser,
    updatePassword,
    getAllUsers,
    getUserById,
    getUserById,
    updateUser,
    deleteUser,
    forcePasswordReset,
    savePasswordResetToken,
    findUserByResetToken,
    clearResetTokenAndUpdatePassword,
    updateUserInfo,
    insertAuditLog,
    getAuditLogs
};