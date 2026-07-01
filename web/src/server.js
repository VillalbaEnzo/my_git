const express = require('express');
const mysql = require('mysql2/promise');

const app = express();
app.use(express.json());

const PORT = process.env.PORT || 3000;

// Pool de connexion MySQL
const pool = mysql.createPool({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASS,
  database: process.env.DB_NAME,
  waitForConnections: true,
  connectionLimit: 10,
});

// Route de santé simple
app.get('/', (req, res) => {
  res.json({ status: 'ok', service: 'transalp-nc-web' });
});

// Route de test : vérifie la connexion DB et liste les tickets
app.get('/test-db', async (req, res) => {
  try {
    const [rows] = await pool.query('SELECT * FROM tickets');
    res.json({ db_status: 'connected', tickets: rows });
  } catch (err) {
    res.status(500).json({ db_status: 'error', error: err.message });
  }
});

// Route de test : insère un ticket factice
app.post('/test-db/insert', async (req, res) => {
  try {
    const [result] = await pool.query(
      `INSERT INTO tickets (nc_number, email, profil, description) VALUES (?, ?, ?, ?)`,
      [`NC-TEST-${Date.now()}`, 'test@example.com', 'client', 'Ticket de test']
    );
    res.json({ inserted_id: result.insertId });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
