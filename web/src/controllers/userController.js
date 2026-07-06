const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const userView = require('../views/user.view');
const { sendAccountCreationEmail, sendPasswordResetEmail } = require('../services/emailService');

const listUsers = async (req, res) => {
    try {
        const users = await userQuery.getAllUsers();
        res.send(userView.renderUserList(users, req.session.userId));
    } catch (error) {
        console.error("Error fetching users:", error);
        res.status(500).send(`<pre>Erreur DB : ${error.message}</pre>`);
    }
};

const getCreateForm = (req, res) => {
    res.send(userView.renderUserCreateForm());
};

const createUser = async (req, res) => {
    try {
        const { email, role, nom, type_client } = req.body;

        if ((role === 'employe' || role === 'qualite' || role === 'key_user') && !email.endsWith('@transalp.fr')) {
            return res.status(400).send('<p>Erreur : Les comptes du personnel Transalp doivent avoir une adresse @transalp.fr</p><a href="/users/new">Retour</a>');
        }

        const existingUser = await userQuery.findUserByEmail(email);
        if (existingUser) {
            return res.status(400).send('<p>Erreur : Cet email est déjà utilisé.</p><a href="/users/new">Retour</a>');
        }
        const randomPassword = Math.random().toString(36).slice(-8);
        const hashedPassword = await bcrypt.hash(randomPassword, 10);

        await userQuery.createUser({
            email,
            passwordHash: hashedPassword,
            role,
            name: nom,
            clientType: type_client || 'Inconnu'
        });

        await sendAccountCreationEmail(email, randomPassword);

        res.redirect('/users');
    } catch (error) {
        console.error("Error creating user:", error);
        res.status(500).send(`<pre>Erreur lors de la création : ${error.message}</pre>`);
    }
};

const getEditForm = async (req, res) => {
    try {
        if (parseInt(req.params.id) === req.session.userId) {
            return res.status(403).send('<p>Action refusée : Vous ne pouvez pas modifier votre propre compte.</p><a href="/users">Retour</a>');
        }

        const user = await userQuery.getUserById(req.params.id);
        if (!user) return res.status(404).send('<p>Utilisateur introuvable</p>');
        res.send(userView.renderUserEditForm(user));
    } catch (error) {
        console.error("Error fetching user for edit:", error);
        res.status(500).send(`<pre>Erreur DB : ${error.message}</pre>`);
    }
};

const updateUser = async (req, res) => {
    try {
        if (parseInt(req.params.id) === req.session.userId) {
            return res.status(403).send('<p>Action refusée : Vous ne pouvez pas modifier votre propre compte.</p><a href="/users">Retour</a>');
        }
        const user = await userQuery.getUserById(req.params.id);
        const { role, nom, type_client, email } = req.body;
        let newEmail = null;
        if (user.role === 'client' && email && email !== user.email) {
            newEmail = email;
        }

        await userQuery.updateUser(req.params.id, { role, nom, typeClient: type_client, email: newEmail });
        res.redirect('/users');
    } catch (error) {
        console.error("Error updating user:", error);
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const resetPasswordByAdmin = async (req, res) => {
    try {
        const user = await userQuery.getUserById(req.params.id);
        if (!user) return res.status(404).send('Utilisateur introuvable');

        const randomPassword = Math.random().toString(36).slice(-8);
        const hashedPassword = await bcrypt.hash(randomPassword, 10);

        await userQuery.forcePasswordReset(user.id, hashedPassword);
        await sendPasswordResetEmail(user.email, randomPassword);

        res.send(`<script>alert("Mot de passe réinitialisé et envoyé par email."); window.location.href="/users/${user.id}/edit";</script>`);
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const deleteUser = async (req, res) => {
    try {
        if (parseInt(req.params.id) === req.session.userId) {
            return res.status(403).send('<p>Action refusée : Vous ne pouvez pas supprimer votre propre compte.</p><a href="/users">Retour</a>');
        }
        await userQuery.deleteUser(req.params.id);
        res.redirect('/users');
    } catch (error) {
        console.error("Error deleting user:", error);
        res.status(500).send(`<pre>Erreur lors de la suppression : ${error.message}</pre>`);
    }
};

const viewLogs = async (req, res) => {
    try {
        const logs = await userQuery.getLoginLogs();
        let tableRows = logs.map(l => `
            <tr style="color: ${l.status === 'SUCCESS' ? 'green' : 'red'};">
                <td>${l.created_at.toLocaleString('fr-FR')}</td>
                <td>${l.email_attempt}</td>
                <td>${l.status}</td>
                <td>${l.ip_address}</td>
            </tr>
        `).join('');
        res.send(`
            <h1>Logs de connexion (Réservé au Key User)</h1>
            <a href="/users">Retour</a><br><br>
            <table border="1" cellpadding="5" cellspacing="0">
                <thead><tr><th>Date</th><th>Email</th><th>Statut</th><th>IP</th></tr></thead>
                <tbody>${tableRows}</tbody>
            </table>
        `);
    } catch (error) {
        res.status(500).send("Erreur de récupération des logs");
    }
};

module.exports = {
    listUsers,
    getCreateForm,
    createUser,
    getEditForm,
    updateUser,
    deleteUser,
    resetPasswordByAdmin,
    viewLogs
};