const crypto = require('crypto');
const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const authView = require('../views/auth.view');
const { sendPasswordResetEmail } = require('../services/emailService');

const getLoginForm = (req, res) => {
    if (req.session.userId)
        return res.redirect('/tickets');
    let errorMessage = null;
    if (req.query.error === 'account_exists') {
        errorMessage = "Un compte avec cette adresse e-mail existe déjà. Veuillez vous connecter pour créer votre ticket.";
    }
    res.send(authView.renderLoginForm(errorMessage));
};

const login = async (req, res) => {
    try {
        const { email, password } = req.body;
        const ip = req.ip || req.connection.remoteAddress;
        const userAgent = req.headers['user-agent'] || 'Inconnu';
        const user = await userQuery.findUserByEmail(email);

        if (!user) {
            await userQuery.insertAuditLog(null, email, 'LOGIN_FAILED_NO_USER', ip, userAgent);
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }
        const isMatch = await bcrypt.compare(password, user.password_hash);
        if (!isMatch) {
            await userQuery.insertAuditLog(user.id, email, 'LOGIN_FAILED_WRONG_PWD', ip, userAgent);
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }
        await userQuery.insertAuditLog(user.id, email, 'LOGIN_SUCCESS', ip, userAgent, { role: user.role });
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
        const ip = req.ip || req.connection.remoteAddress;
        const userAgent = req.headers['user-agent'] || 'Inconnu';

        if (user) {
            const token = crypto.randomBytes(32).toString('hex');
            const expireDate = new Date(Date.now() + 3600000);
            await userQuery.savePasswordResetToken(email, token, expireDate);
            const resetLink = `http://${req.headers.host}/auth/reset-password?token=${token}`;
            await sendPasswordResetEmail(email, resetLink);
        }
        await userQuery.insertAuditLog(user.id, email, 'RESET_PASSWORD_REQUESTED', ip, userAgent);
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
    return res.send(authView.renderResetPasswordForm(token));
};

const getProfileForm = async (req, res) => {
    try {
        const user = await userQuery.getUserById(req.session.userId);
        if (!user)
            return res.redirect('/auth/login');
    res.send(authView.renderProfileForm(user));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const updateProfileInfo = async (req, res) => {
    try {
        const { nom, email } = req.body;
        const userId = req.session.userId;
        const ip = req.ip || req.connection.remoteAddress;
        const userAgent = req.headers['user-agent'];
        const currentUser = await userQuery.getUserById(userId);

        let finalEmail = currentUser.email;

        if (currentUser.role === 'client' && email && email !== currentUser.email) {
            const existingUser = await userQuery.findUserByEmail(email);
            if (existingUser) {
                return res.send(authView.renderProfileForm(currentUser, "Cet email est déjà utilisé par un autre compte."));
            }
            finalEmail = email;
        }
        await userQuery.updateUserInfo(userId, nom, finalEmail);
        const updatedUser = await userQuery.getUserById(userId);
        await userQuery.insertAuditLog(userId, updatedUser.email, 'PROFILE_UPDATE', ip, userAgent, {old_name: currentUser.nom, new_name: nom, old_email: currentUser.email, new_email: email});
        res.send(authView.renderProfileForm(updatedUser, null, "Informations mises à jour avec succès."));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const updateProfilePassword = async (req, res) => {
    try {
        const { oldPassword, newPassword, confirmPassword } = req.body;
        const user = await userQuery.getUserById(req.session.userId);
        if (newPassword !== confirmPassword) {
            return res.send(authView.renderProfileForm(user, 'Les nouveaux mots de passe ne correspondent pas.'));
        }
        const userFull = await userQuery.findUserByEmail(user.email);
        const isMatch = await bcrypt.compare(oldPassword, userFull.password_hash);
        if (!isMatch) {
            const errorMsg = `Ancien mot de passe incorrect. <a href="/auth/forgot-password">J'ai oublié mon mot de passe</a>`;
            return res.send(authView.renderProfileForm(user, errorMsg));
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
    getResetPasswordForm,
    processResetPassword,
    getProfileForm,
    updateProfileInfo,
    updateProfilePassword
};