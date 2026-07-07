const ticketQuery = require('../queries/ticket.query');
const adminView = require('../views/admin.view');

const getDashboard = async (req, res) => {
    try {
        const stats = await ticketQuery.getDashboardStats();
        res.send(adminView.renderDashboard(stats, req.session.role));
    } catch (error) {
        res.status(500).send("Erreur lors du chargement du dashboard : " + error.message);
    }
};

const getValidationIA = async (req, res) => {
    try {
        const tickets = await ticketQuery.getAllTickets();
        const pendingTickets = tickets.filter(t =>
            t.status === 'ai_completed' || t.status === 'manual_completion_required'
        );
        res.send(adminView.renderValidationIA(pendingTickets, req.session.role));
    } catch (error) {
        res.status(500).send("Erreur lors du chargement de la validation : " + error.message);
    }
};

module.exports = {
    getDashboard,
    getValidationIA
};