const { renderLayout } = require('./layout.view');

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
    <p style="margin-top: 15px;"><a href="/auth/forgot-password">J'ai oublié mon mot de passe</a></p>
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
    `, 'pending');
};

const renderForgotPasswordForm = (message = null, isSuccess = false) => {
    const msgHtml = message ? `<p style="color:${isSuccess ? 'green' : 'red'}; font-weight:bold;">${message}</p>` : '';
    return renderLayout('Mot de passe oublié', `
    <h2>Réinitialisation du mot de passe</h2>
    ${msgHtml}
    ${!isSuccess ? `
    <form method="POST" action="/auth/forgot-password">
      <label>Entrez votre adresse email :</label><br>
      <input type="email" name="email" required placeholder="votre@email.fr"><br><br>
      <button type="submit">Recevoir un nouveau mot de passe</button>
    </form>
    ` : ''}
    <br><a href="/auth/login">← Retour à la connexion</a>
    `);
};

const renderProfileForm = (error = null, success = null) => {
    const errorHtml = error ? `<p style="color:red; font-weight:bold;">${error}</p>` : '';
    const successHtml = success ? `<p style="color:green; font-weight:bold;">${success}</p>` : '';

    return renderLayout('Sécurité du compte', `
    <h2>Modifier mon mot de passe</h2>
    ${errorHtml}
    ${successHtml}
    <form method="POST" action="/auth/profile">
      <label>Ancien mot de passe :</label><br>
      <input type="password" name="oldPassword" required><br><br>

      <label>Nouveau mot de passe :</label><br>
      <input type="password" name="newPassword" required minlength="6"><br><br>

      <button type="submit">Mettre à jour</button>
    </form>
    `, 'logged_in');
};

module.exports = {
    renderLoginForm,
    renderChangePasswordForm,
    renderForgotPasswordForm,
    renderProfileForm
};