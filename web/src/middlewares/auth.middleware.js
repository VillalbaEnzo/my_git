const requireAuth = (req, res, next) => {
    if (!req.session.userId) {
        return res.redirect('/auth/login');
    }
    if (req.session.mustChangePassword && req.path !== '/change-password') {
        return res.redirect('/auth/change-password');
    }
    next();
};

const requireQualite = (req, res, next) => {
    if (req.session.role !== 'qualite' && req.session.role !== 'key_user') {
        return res.status(403).send('Accès refusé : Réservé au service Qualité.');
    }
    next();
};

// Réservé uniquement au Key User (pour gérer les comptes)
const requireKeyUser = (req, res, next) => {
    if (req.session.role !== 'key_user') {
        return res.status(403).send('Accès refusé : Réservé au Key User.');
    }
    next();
};

module.exports = { requireAuth, requireQualite, requireKeyUser };