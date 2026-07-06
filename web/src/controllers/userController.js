const crypto = require('crypto');
const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const userView = require('../views/user.view');
const { sendAccountCreationEmail, sendPasswordResetEmail } = require('../services/emailService');
const { renderLayout } = require('../views/layout.view');

const listUsers = async (req, res) => {
    try {
        const users = await userQuery.getAllUsers();
        res.send(userView.renderUserList(users, req.session.userId));
    } catch (error) {
        console.error("Error fetching users:", error);sendPasswordResetEmail
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
        if (email && email !== user.email) {
            newEmail = email;
        }
        const existingUser = await userQuery.findUserByEmail(email);
        if (existingUser)
            return res.send(userView.renderUserEditForm(user, 'Cette adresse e-mail est déjà utilisée.'));
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
        const email = user.email;

        if (user) {
            const token = crypto.randomBytes(32).toString('hex');
            const expireDate = new Date(Date.now() + 3600000);
            await userQuery.savePasswordResetToken(email, token, expireDate);
            const resetLink = `http://${req.headers.host}/auth/reset-password?token=${token}`;
            await sendPasswordResetEmail(email, resetLink);
        }
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
        const logs = await userQuery.getAuditLogs();
        let tableRows = logs.map(l => {
            let color = "black";
            if (l.action_type.includes('SUCCESS')) color = "green";
            if (l.action_type.includes('FAILED')) color = "red";
            if (l.action_type.includes('UPDATE') || l.action_type.includes('RESET')) color = "blue";
            const detailsHtml = l.details ? `<pre style="font-size: 10px; margin: 0;">${JSON.stringify(l.details, null, 2)}</pre>` : '-';
            const userName = l.nom ? `${l.nom} (ID:${l.user_id})` : 'Non identifié';

            return `
            <tr style="color: ${color};">
                <td>${new Date(l.created_at).toLocaleString('fr-FR')}</td>
                <td>${l.email_attempt || '-'}</td>
                <td>${userName}</td>
                <td><strong>${l.action_type}</strong></td>
                <td>${l.ip_address}</td>
                <td style="font-size: 11px; max-width: 200px; word-wrap: break-word;">${l.user_agent}</td>
                <td>${detailsHtml}</td>
            </tr>`;
        }).join('');

        res.send(renderLayout('Journal Utilisateurs', `
            <div style="padding: 20px; font-family: sans-serif;">
                <h1>Journal d'Audit Système (Key User)</h1>
                <a href="/users" style="display: inline-block; margin-bottom: 20px;">&larr; Retour à la gestion</a>
                <table border="1" cellpadding="8" cellspacing="0" style="width: 100%; text-align: left; border-collapse: collapse;">
                    <thead style="background-color: #f4f4f4;">
                        <tr>
                            <th>Date</th>
                            <th>Email testé</th>
                            <th>Utilisateur</th>
                            <th>Action</th>
                            <th>IP</th>
                            <th>Navigateur / OS</th>
                            <th>Détails</th>
                        </tr>
                    </thead>
                    <tbody>${tableRows}</tbody>
                </table>
            </div>
        `, 'key_user'));
    } catch (error) {
        res.status(500).send("Erreur de récupération des logs : " + error.message);
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