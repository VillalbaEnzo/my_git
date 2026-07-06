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
        await pool.query(
            'UPDATE users SET role = ?, nom = ?, type_client = ?, email = ? WHERE id = ?',
            [role, nom, typeClient, email, id]
        );
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
    await pool.query('DELETE FROM users WHERE id = ?', [id]);
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
    forcePasswordReset
};