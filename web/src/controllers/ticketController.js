const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const ticketQuery = require('../queries/ticket.query');
const ticketView = require('../views/ticket.view');
const { triggerAnalysis } = require('../services/aiClient');
const { sendAccountCreationEmail } = require('../services/emailService');

const getAllTickets = async (req, res) => {
    try {
        let tickets;
        if (req.session.role === 'qualite' || req.session.role === 'key_user') {
            tickets = await ticketQuery.getAllTickets();
        }
        else {
            tickets = await ticketQuery.getTicketsByClientId(req.session.userId);
        }
        res.send(ticketView.renderTicketList(tickets, req.session.role));
    } catch (error) {
        console.error("Error fetching tickets list:", error);
        res.status(500).send(`<pre>Erreur DB : ${error.message}</pre>`);
    }
};

const getTicketById = async (req, res) => {
    try {
        const ticket = await ticketQuery.getTicketById(req.params.id);
        if (!ticket) {
            return res.status(404).send('<p>Ticket introuvable</p>');
        }

        if ((req.session.role === 'client' || req.session.role === 'employe') && ticket.client_id !== req.session.userId) {
            return res.status(403).send('<p>Accès refusé : Ce ticket ne vous appartient pas.</p>');
        }

        res.send(ticketView.renderTicketDetail(ticket, req.session.role));
    } catch (error) {
        console.error("Error fetching ticket details:", error);
        res.status(500).send(`<pre>Erreur DB : ${error.message}</pre>`);
    }
};

const getTicketForm = async (req, res) => {
    try {
        let user = null;
        if (req.session.userId) {
            user = await userQuery.getUserById(req.session.userId);
        }
        res.send(ticketView.renderTicketForm(user, req.session.role));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const createTicket = async (req, res) => {
    try {
        const {
            profile,
            email,
            name,
            clientType,
            description,
            reference,
            orderNumber,
            installationDate
        } = req.body;
        const files = (req.files || []).map(f => f.filename);

        if (profile === 'employe') {
            if (!reference || !orderNumber) {
                return res.status(400).send("Erreur : La référence produit et le N° de commande sont obligatoires pour un employé.");
            }
            if (!email.endsWith('@transalp.fr')) {
                return res.status(400).send("Erreur : Votre adresse e-mail n'a pas été reconnue comme étant une adresse e-mail d'un employé de Transalp.");
            }
        }
        // USERS
        let userId = req.session.userId || null;
        if (email) {
            const existingUser = await userQuery.findUserByEmail(email);
            if (existingUser) {
                if (!req.session.userId) {
                    return res.redirect('/auth/login?error=account_exists');
                }
                if (req.session.userId && req.session.userId !== existingUser.id) {
                    return res.status(403).send("Erreur : Vous ne pouvez pas créer un ticket avec l'adresse e-mail d'un autre utilisateur.");
                }
                userId = existingUser.id;
            } else {
                const randomPassword = Math.random().toString(36).slice(-8);
                const hashedPassword = await bcrypt.hash(randomPassword, 10);

                userId = await userQuery.createUser({
                    email,
                    passwordHash: hashedPassword,
                    role: profile === 'employe' ? 'employe' : 'client',
                    name: name || 'Non renseigné',
                    clientType: clientType || 'Inconnu'
                });

                await sendAccountCreationEmail(email, randomPassword);
            }
        }
        //TICKETS
        const nextId = await ticketQuery.getNextTicketId();

        const year = new Date().getFullYear();
        const ncNumber = `NC-${year}-${String(nextId).padStart(3, '0')}`;
        const ticketId = await ticketQuery.createTicket({
            ncNumber,
            clientId: userId,
            email,
            profile,
            description,
            installationDate: installationDate || null,
            reference: reference || null,
            orderNumber: orderNumber || null,
            photos: files
        });

        triggerAnalysis({
            ticket_id: ticketId,
            description,
            profil: profile,
            reference: reference || '',
            date_pose: installationDate || null,
            image_paths: files
        });

        res.redirect(`/tickets/${ticketId}?created=1`);
    } catch (error) {
        console.error("Ticket creation error:", error);
        res.status(500).send(`<pre>Erreur serveur : ${error.message}</pre>`);
    }
};

const updateTicketAdmin = async (req, res) => {
    try {
        const ticketId = req.params.id;
        const {
            status,
            ai_type_nc,
            ai_cause,
            ai_action_generale,
            ai_service_impacte,
            ai_resume,
            gravity_score,
            gravity_label
        } = req.body;

        await ticketQuery.updateTicketAdminFields(ticketId, {
            status,
            ai_type_nc: ai_type_nc || null,
            ai_cause: ai_cause || null,
            ai_action_generale: ai_action_generale || null,
            ai_service_impacte: ai_service_impacte || null,
            ai_resume: ai_resume || null,
            gravity_score: gravity_score ? parseInt(gravity_score, 10) : null,
            gravity_label: gravity_label || null
        });

        res.redirect(`/tickets/${ticketId}?updated=1`);
    } catch (error) {
        console.error("Erreur lors de la mise à jour admin du ticket :", error);
        res.status(500).send(`<pre>Erreur serveur : ${error.message}</pre>`);
    }
};

const getEditAiForm = async (req, res) => {
    const ticket = await ticketQuery.getTicketById(req.params.id);
    res.send(ticketView.renderEditAiForm(ticket, req.session.role));
};

const confirmAiData = async (req, res) => {
    try {
        const { id } = req.params;
        const b = req.body;

        const oldTicket = await ticketQuery.getTicketById(id);
        let currentPhotos = [];
        if (oldTicket.photos) {
            try {
                currentPhotos = typeof oldTicket.photos === 'string'
                    ? JSON.parse(oldTicket.photos)
                    : oldTicket.photos;
            } catch (e) {
                console.error("Erreur parsing photos existantes:", e);
                currentPhotos = [];
            }
        }

        if (req.files && req.files.length > 0) {
            const newFiles = req.files.map(f => f.filename);
            currentPhotos = [...currentPhotos, ...newFiles];
        }

        const newDetail = {
            securite:      { niveau: parseInt(b.grav_securite), coeff: 3 },
            client:        { niveau: parseInt(b.grav_client),   coeff: 2 },
            cout:          { niveau: parseInt(b.grav_cout),     coeff: 1 },
            impact_poseur: { niveau: parseInt(b.grav_impact_poseur), coeff: 2 }
        };
        const totalScore = Object.values(newDetail).reduce((acc, curr) => acc + (curr.niveau * curr.coeff), 0);

        await ticketQuery.updateTicketFull(id, {
            ...b,
            photos: JSON.stringify(currentPhotos),
            gravity_detail: JSON.stringify(newDetail),
            gravity_score: totalScore,
            status: 'open'
        });

        res.redirect('/admin/dashboard');
    } catch (e) {
        console.error("Erreur lors de la validation:", e);
        res.status(500).send("Erreur serveur : " + e.message);
    }
};

module.exports = {
    getAllTickets,
    getTicketById,
    getTicketForm,
    createTicket,
    updateTicketAdmin,
    confirmAiData,
    getEditAiForm
};