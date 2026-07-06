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
        const user = await userQuery.findUserByEmail(email);

        if (!user) {
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }

        const isMatch = await bcrypt.compare(password, user.password_hash);
        if (!isMatch) {
            return res.send(authView.renderLoginForm('Email ou mot de passe incorrect.'));
        }

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
        const user = await userQuery.findUserByEmail(req.body.email);
        if (user) {
            const randomPassword = Math.random().toString(36).slice(-8);
            const hashedPassword = await bcrypt.hash(randomPassword, 10);
            await userQuery.forcePasswordReset(user.id, hashedPassword);
            await sendPasswordResetEmail(user.email, randomPassword);
        }
        // Même si l'email n'existe pas, on affiche un succès pour ne pas fuiter d'informations
        res.send(authView.renderForgotPasswordForm("Si cet email existe, un mot de passe temporaire a été envoyé.", true));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
};

const getProfileForm = (req, res) => {
    if (req.session.role === 'key_user') {
        return res.status(403).send('<p>Action refusée : Le Key User doit utiliser la procédure de "Mot de passe oublié" pour modifier ses accès.</p><a href="/users">Retour</a>');
    }
    res.send(authView.renderProfileForm());
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

        res.send(authView.renderProfileForm(null, "Votre mot de passe a été mis à jour avec succès."));
    } catch (error) {
        res.status(500).send(`<pre>Erreur : ${error.message}</pre>`);
    }
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
    updateProfilePassword
};