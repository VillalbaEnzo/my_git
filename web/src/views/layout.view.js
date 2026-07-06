const renderLayout = (title, content, userRole = null) => {
    let menu = `<a href="/tickets/new/form">+ Nouveau ticket</a>`;
    if (userRole) {
        menu = `<a href="/tickets">Liste des Tickets</a> | ` + menu;
    }
    if (userRole === 'key_user') {
        menu += ` | <a href="/users">Gestion des Comptes</a>`;
    }
    if (userRole) {
        if (userRole !== 'key_user') {
            menu += ` | <a href="/auth/profile">Sécurité</a>`;
        }
        menu += ` | <a href="/auth/logout">Déconnexion</a>`;
    } else {
        menu += ` | <a href="/auth/login">Connexion</a>`;
    }

    return `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>${title} — Transalp NC</title>
</head>
<body>
  <header>${menu}</header>
  <hr>
  <main>${content}</main>
</body>
</html>`;
};

module.exports = { renderLayout };