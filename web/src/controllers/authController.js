const bcrypt = require('bcrypt');
const userQuery = require('../queries/user.query');
const authView = require('../views/auth.view');

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
        }

        res.redirect('/tickets');
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

module.exports = {
    getLoginForm,
    login,
    getChangePasswordForm,
    changePassword,
    logout
};