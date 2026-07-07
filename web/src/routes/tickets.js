const express = require('express');
const multer  = require('multer');
const path    = require('path');
const ticketController = require('../controllers/ticketController');
const adminController = require('../controllers/adminController');
const { requireAuth, requireQualite } = require('../middlewares/auth.middleware');

const router = express.Router();

const storage = multer.diskStorage({
  destination: '/app/uploads',
  filename: (req, file, cb) => {
    const unique = Date.now() + '-' + Math.round(Math.random() * 1e6);
    cb(null, unique + path.extname(file.originalname));
  },
});
const upload = multer({ storage, limits: { fileSize: 20 * 1024 * 1024 }, dest: '/app/uploads' });

//Public Routes
router.get('/new/form', ticketController.getTicketForm);
router.post('/', upload.array('fichiers', 10), ticketController.createTicket);

//Secure Routes
router.use(requireAuth);
router.get('/', ticketController.getAllTickets);
router.get('/:id', ticketController.getTicketById);

router.post('/:id/admin-update', requireQualite, ticketController.updateTicketAdmin);
router.get('/:id/edit', requireQualite, ticketController.getEditAiForm);
router.post('/:id/confirm', requireQualite, upload.array('fichiers', 10), ticketController.confirmAiData);

module.exports = router;