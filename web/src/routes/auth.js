const { requireAuth } = require('../middlewares/auth.middleware');
const express = require('express');
const authController = require('../controllers/authController');
const router = express.Router();

router.get('/login', authController.getLoginForm);
router.post('/login', authController.login);

router.get('/forgot-password', authController.getForgotPasswordForm);
router.post('/forgot-password', authController.processForgotPassword);

router.get('/change-password', authController.getChangePasswordForm);
router.post('/change-password', authController.changePassword);

router.get('/profile', requireAuth, authController.getProfileForm);
router.post('/profile', requireAuth, authController.updateProfilePassword);

router.get('/logout', authController.logout);

module.exports = router;