require('dotenv').config();
const express = require('express');
const app = express();

app.use(express.urlencoded({ extended: true }));
app.use(express.json());

app.use('/tickets', require('./routes/tickets'));
app.get('/', (req, res) => res.redirect('/tickets'));

app.listen(process.env.PORT || 3000, () =>
  console.log(`Transalp NC → http://localhost:3000`)
);
