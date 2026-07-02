const express = require('express');
const authController = require('../controllers/authController');
const router = express.Router();

router.get('/login', authController.getLoginForm);
router.post('/login', authController.login);

router.get('/change-password', authController.getChangePasswordForm);
router.post('/change-password', authController.changePassword);

router.get('/logout', authController.logout);

module.exports = router;