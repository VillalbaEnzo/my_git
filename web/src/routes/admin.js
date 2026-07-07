const express = require('express');
const adminController = require('../controllers/adminController');
const { requireAuth, requireQualite } = require('../middlewares/auth.middleware');

const router = express.Router();

// On applique la sécurité sur toutes les routes admin
router.use(requireAuth);
router.use(requireQualite);

// Les routes (le préfixe /admin est déjà géré par server.js)
router.get('/dashboard', adminController.getDashboard);
router.get('/validation', adminController.getValidationIA);

module.exports = router;