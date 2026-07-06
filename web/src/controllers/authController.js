const crypto = require('crypto');
const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const authView = require('../views/auth.view');
const { sendPasswordResetEmail } = require('../services/emailService');

const getLoginForm = (req, res) => {
    if (req.session.userId) return res.redirect('/tickets');
    res.send(authView.renderLoginForm());
};

const login = async (req, res) => {
    try {
        const { email, password } = req.body;
        const ip = req.ip || req.connection.remoteAddress;
        const user = await userQuery.findUserByEmail(email);

        if (!user) {
            await userQuery.logConnectionAttempt(email, 'FAILED - NO USER', ip);
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }

        const isMatch = await bcrypt.compare(password, user.password_hash);
        if (!isMatch) {
            await userQuery.logConnectionAttempt(email, 'FAILED - WRONG PASSWORD', ip);
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }

        await userQuery.logConnectionAttempt(email, 'SUCCESS', ip);

        req.session.userId = user.id;
        req.session.role = user.role;
        req.session.mustChangePassword = user.must_change_password;

        if (user.must_change_password) {
            return res.redirect('/auth/change-password');
        }
        if (user.role === 'key_user') {
            return res.redirect('/users');
        } else {
            res.redirect('/tickets');
        }
    } catch (error) {
        console.error("Login error:", error);
        res.status(500).send(`<pre>Erreur serveur : ${error.message}</pre>`);
    }
};

const getChangePasswordForm = (req, res) => {
    if (!req.session.userId) {
        return res.redirect('/auth/login');
    }
    if (!req.session.mustChangePassword) {
        return res.redirect('/tickets');
    }
    res.send(authView.renderChangePasswordForm());
};

const changePassword = async (req, res) => {
    try {
        if (!req.session.userId || !req.session.mustChangePassword) {
            return res.redirect('/tickets');
        }

        const { newPassword, confirmPassword } = req.body;

        if (newPassword !== confirmPassword) {
            return res.send(authView.renderChangePasswordForm('Les mots de passe ne correspondent pas.'));
        }

        const hashedPassword = await bcrypt.hash(newPassword, 10);
        await userQuery.updatePassword(req.session.userId, hashedPassword);

        req.session.mustChangePassword = false;
        res.redirect('/tickets');

    } catch (error) {
        console.error("Password change error:", error);
        res.status(500).send(`<pre>Erreur serveur : ${error.message}</pre>`);
    }
};

const logout = (req, res) => {
    req.session.destroy(() => {
        res.redirect('/auth/login');
    });
};

const getForgotPasswordForm = (req, res) => {
    res.send(authView.renderForgotPasswordForm());
};

const processForgotPassword = async (req, res) => {
    try {
        const email = req.body.email;
        const user = await userQuery.findUserByEmail(email);

        if (user) {
            // Générer un token sécurisé
            const token = crypto.randomBytes(32).toString('hex');
            // Expire dans 1 heure
            const expireDate = new Date(Date.now() + 3600000);
            await userQuery.savePasswordResetToken(email, token, expireDate);
            // Simuler l'envoi d'email (A intégrer dans ton emailService)
            const resetLink = `http://${req.headers.host}/auth/reset-password?token=${token}`;
            console.log(`[EMAIL SIMULÉ] Lien de reset pour ${email} : ${resetLink}`);
            // await sendPasswordResetTokenEmail(email, resetLink);
        }
        res.send(authView.renderForgotPasswordForm("Si cet email existe, un lien de réinitialisation vous a été envoyé.", true));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const getResetPasswordForm = async (req, res) => {
    const token = req.query.token;
    if (!token)
        return res.send("Token manquant.");

    const user = await userQuery.findUserByResetToken(token);
    if (!user)
        return res.send("Ce lien est invalide ou a expiré.");
    res.send(authView.renderResetPasswordForm(token));
};

const getProfileForm = async (req, res) => {
    if (req.session.role === 'key_user') {
        return res.status(403).send('<p>Action refusée : Le Key User doit utiliser la procédure de "Mot de passe oublié".</p><a href="/users">Retour</a>');
    }
    try {
        const user = await userQuery.getUserById(req.session.userId);
        res.send(authView.renderProfileForm(user));
    } catch (error) {
        res.status(500).send("Erreur serveur");
    }
};

const updateProfileInfo = async (req, res) => {
    try {
        const { nom, email } = req.body;
        const userId = req.session.userId;
        const currentUser = await userQuery.getUserById(userId);

        if (email !== currentUser.email) {
            const existingUser = await userQuery.findUserByEmail(email);
            if (existingUser) {
                return res.send(authView.renderProfileForm(currentUser, "Cet email est déjà utilisé par un autre compte."));
            }
        }
        await userQuery.updateUserInfo(userId, nom, email);
        const updatedUser = await userQuery.getUserById(userId);
        res.send(authView.renderProfileForm(updatedUser, null, "Informations mises à jour avec succès."));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const updateProfilePassword = async (req, res) => {
    try {
        if (req.session.role === 'key_user') {
            return res.status(403).send('<p>Action refusée.</p><a href="/users">Retour</a>');
        }

        const { oldPassword, newPassword } = req.body;
        const user = await userQuery.getUserById(req.session.userId);
        const userFull = await userQuery.findUserByEmail(user.email);

        const isMatch = await bcrypt.compare(oldPassword, userFull.password_hash);
        if (!isMatch) {
            const errorMsg = `Ancien mot de passe incorrect. <a href="/auth/forgot-password" style="color: blue;">J'ai oublié mon mot de passe</a>`;
            return res.send(authView.renderProfileForm(errorMsg));
        }

        const hashedPassword = await bcrypt.hash(newPassword, 10);
        await userQuery.updatePassword(user.id, hashedPassword);
        const updatedUser = await userQuery.getUserById(req.session.userId);
        res.send(authView.renderProfileForm(updatedUser, null, "Mot de passe mis à jour avec succès."));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const processResetPassword = async (req, res) => {
    const { token, newPassword } = req.body;
    const user = await userQuery.findUserByResetToken(token);
    if (!user)
        return res.send("Ce lien est invalide ou a expiré.");

    const hashedPassword = await bcrypt.hash(newPassword, 10);
    await userQuery.clearResetTokenAndUpdatePassword(user.id, hashedPassword);

    res.send("Mot de passe mis à jour avec succès. <a href='/auth/login'>Se connecter</a>");
};

module.exports = {
    getLoginForm,
    login,
    getChangePasswordForm,
    changePassword,
    logout,
    getForgotPasswordForm,
    processForgotPassword,
    getProfileForm,
    updateProfilePassword,
    processResetPassword,
    getResetPasswordForm
};