require('dotenv').config();
const express = require('express');
const session = require('express-session');
const app = express();

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.use(session({
  secret: 'transalp-nc-secret-key-2024',
  resave: false,
  saveUninitialized: false
}));

app.use('/auth', require('./routes/auth'));
app.use('/tickets', require('./routes/tickets'));
app.use('/users', require('./routes/users'));

app.get('/', (req, res) => res.redirect('/tickets'));

app.listen(process.env.PORT || 3000, () =>
  console.log(`Transalp NC → http://localhost:3000`)
);