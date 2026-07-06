const express = require('express');
const userController = require('../controllers/userController');
const { requireAuth, requireKeyUser } = require('../middlewares/auth.middleware');

const router = express.Router();

router.use(requireAuth);
router.use(requireKeyUser);

router.get('/', userController.listUsers);

router.get('/new', userController.getCreateForm);
router.post('/new', userController.createUser);
router.post('/:id/reset-password', userController.resetPasswordByAdmin);

router.get('/:id/edit', userController.getEditForm);
router.post('/:id/edit', userController.updateUser);
router.post('/:id/delete', userController.deleteUser);

module.exports = router;