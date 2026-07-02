const renderLayout = (title, content) => {
    return `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>${title} — Transalp NC</title>
</head>
<body>
  <header>
    <h1>Transalp NC - Espace Sécurisé</h1>
  </header>
  <hr>
  <main>${content}</main>
</body>
</html>`;
};

const renderLoginForm = (error = null) => {
    const errorHtml = error ? `<p style="color:red; font-weight:bold;">${error}</p>` : '';
    return renderLayout('Connexion', `
    <h2>Connexion</h2>
    ${errorHtml}
    <form method="POST" action="/auth/login">
      <label>Email :</label><br>
      <input type="email" name="email" required><br><br>

      <label>Mot de passe :</label><br>
      <input type="password" name="password" required><br><br>

      <button type="submit">Se connecter</button>
    </form>
    `);
};

const renderChangePasswordForm = (error = null) => {
    const errorHtml = error ? `<p style="color:red; font-weight:bold;">${error}</p>` : '';
    return renderLayout('Changement obligatoire', `
    <h2>Bienvenue ! Veuillez sécuriser votre compte</h2>
    <p>Ceci est votre première connexion. Vous devez modifier le mot de passe provisoire reçu par mail.</p>
    ${errorHtml}
    <form method="POST" action="/auth/change-password">
      <label>Nouveau mot de passe :</label><br>
      <input type="password" name="newPassword" required minlength="6"><br><br>

      <label>Confirmer le mot de passe :</label><br>
      <input type="password" name="confirmPassword" required minlength="6"><br><br>

      <button type="submit">Mettre à jour et continuer</button>
    </form>
    `);
};

module.exports = { renderLoginForm, renderChangePasswordForm };