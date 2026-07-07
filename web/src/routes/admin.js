const express = require('express');
const adminController = require('../controllers/adminController');
const { requireAuth, requireQualite } = require('../middlewares/auth.middleware');

const router = express.Router();

router.use(requireAuth);
router.use(requireQualite);

router.get('/dashboard', adminController.getDashboard);
router.get('/validation', adminController.getValidationIA);

module.exports = router;