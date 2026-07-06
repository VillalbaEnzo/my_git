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

const renderProfileForm = (user, error = null, success = null) => {
    const errorHtml = error ? `<p style="color:red; font-weight:bold;">${error}</p>` : '';
    const layoutType = (user.role === 'key_user') ? 'key_user' : 'logged_in';
    const successHtml = success ? `<p style="color:green; font-weight:bold;">${success}</p>` : '';
    const isKeyUser = user.role === 'key_user';
    const emailField = user.role === 'client'
        ? `<input type="email" name="email" value="${user.email}" required><br><br>`
        : isKeyUser ? `<input type="email" value="${user.email}" disabled style="background-color: #f3f3f3;"><br>
           <small>Vous ne pouvez pas modifier cette adresse e-mail pour des raisons évidentes de sécurité.</small><br><br>` : `<input type="email" value="${user.email}" disabled style="background-color: #f3f3f3;"><br>
           <small>Seul un administrateur peut modifier votre adresse email professionnelle.</small><br><br>`;

    const passwordWarning = isKeyUser
        ? `onsubmit="return confirm('ATTENTION : Vous êtes le Key User (Administrateur principal).\\n\\nSoyez très prudent avec cette modification et gardez votre nouveau mot de passe en lieu sûr !\\n\\nVoulez-vous vraiment continuer ?');"`
        : '';

    return renderLayout('Mon Profil', `
    <h2>Mon Profil</h2>
    ${errorHtml}
    ${successHtml}
    <fieldset style="margin-bottom: 20px;">
        <legend>Mes informations personnelles</legend>
        <form method="POST" action="/auth/profile/info">
          <label>Nom ou Raison Sociale :</label><br>
          <input type="text" name="nom" value="${user.nom}" required><br><br>
          <label>Email :</label><br>
          ${emailField}<br><br>

          <button type="submit">Mettre à jour mes informations</button>
        </form>
    </fieldset>

    <fieldset>
        <legend>Modifier mon mot de passe</legend>
        <!-- L'attribut onsubmit exécute la popup d'alerte si l'utilisateur est key_user -->
        <form method="POST" action="/auth/profile/password" ${passwordWarning}>
          <label>Ancien mot de passe :</label><br>
          <input type="password" name="oldPassword" required><br><br>

          <label>Nouveau mot de passe :</label><br>
          <input type="password" name="newPassword" required minlength="6"><br><br>
          <label>Confirmer le nouveau mot de passe :</label><br>
          <input type="password" name="confirmPassword" required minlength="6"><br><br>

          <button type="submit">Changer le mot de passe</button>
        </form>
    </fieldset>
    `, layoutType);
    };

const renderResetPasswordForm = (token) => {
    return renderLayout('Nouveau mot de passe', `
      <h2>Créer un nouveau mot de passe</h2>
      <form method="POST" action="/auth/reset-password">
          <input type="hidden" name="token" value="${token}">
          <label>Nouveau mot de passe :</label><br>
          <input type="password" name="newPassword" required minlength="6"><br><br>
          <button type="submit">Valider</button>
      </form>
    `);
}

module.exports = {
    renderLoginForm,
    renderChangePasswordForm,
    renderForgotPasswordForm,
    renderProfileForm,
    renderResetPasswordForm
};