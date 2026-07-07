const { renderResetPasswordForm } = require('./auth.view');
const { renderLayout } = require('./layout.view');

const renderUserList = (users, currentUserId) => {
    const rows = users.map(u => {
        const actions = (u.id === currentUserId)
            ? `<a href="/auth/profile">Modifier</a>`
            : `<a href="/users/${u.id}/edit">Modifier</a> |
               <form method="POST" action="/users/${u.id}/delete" style="display:inline;">
                   <button type="submit" onclick="return confirm('Supprimer ce compte définitivement ?')">Supprimer</button>
               </form>`;

        return `
        <tr>
          <td>${u.id}</td>
          <td>${u.nom}</td>
          <td>${u.email}</td>
          <td><strong>${u.role}</strong></td>
          <td>${u.type_client || '—'}</td>
          <td>${new Date(u.created_at).toLocaleString('fr-FR')}</td>
          <td>${actions}</td>
        </tr>`;
    }).join('');

    return renderLayout('Gestion des Comptes', `
    <h1>Panneau d'administration - Key User</h1>
    <p>Liste de tous les comptes enregistrés dans le système.</p>
    <a href="/users/new">+ Ajouter un nouveau compte</a>
    <br>
    <table border="1" cellpadding="5" cellspacing="0" style="width: 100%; text-align: left;">
      <thead>
        <tr>
          <th>ID</th><th>Nom</th><th>Email</th><th>Rôle</th><th>Type</th><th>Créé le</th><th>Actions</th>
        </tr>
      </thead>
      <tbody>
        ${rows || '<tr><td colspan="7">Aucun utilisateur</td></tr>'}
      </tbody>
    </table>
    `, 'key_user');
};

const renderUserCreateForm = () => {
    return renderLayout('Créer un compte', `
    <h1>Créer un nouveau compte</h1>
    <p>Un email contenant un mot de passe temporaire sera envoyé à cette adresse.</p>
    <form method="POST" action="/users/new">
        <label>Email * :</label><br>
        <input type="email" name="email" required><br><br>

        <label>Nom ou Raison Sociale * :</label><br>
        <input type="text" name="nom" required><br><br>

        <label>Rôle * :</label><br>
        <select name="role" required>
            <option value="qualite">Service Qualité</option>
            <option value="employe">Employé (Standard)</option>
            <option value="client">Client</option>
            <option value="key_user">Key User</option>
        </select><br><br>

        <label>Type de client :</label><br>
        <select name="type_client" required>
            <option value="Particulier">Particulier</option>
            <option value="Entreprise">Entreprise</option>
            <option value="Mairie">Mairie</option>
            <option value="key_user">Fournisseur</option>
            <option value="Transalp">Transalp</option>
        </select><br><br>

        <button type="submit">Créer le compte et envoyer l'email</button>
    </form>
    <br>
    <a href="/users">← Retour à la liste</a>
    `, 'key_user');
};

const renderUserEditForm = (user, error = null) => {
    const errorMsg = error ? `<p style="color:red; font-weight:bold;">${error}</p>` : '';
    const emailField = `
        ${errorMsg}
        <label>Email :</label><br>
        <input type="email" name="email" value="${user.email}" required><br><br>
    `;

    return renderLayout(`Modifier l'utilisateur ${user.id}`, `
    <h1>Modifier le compte : ${user.email}</h1>

        <form method="POST" action="/users/${user.id}/reset-password" onsubmit="return confirm('Êtes-vous sûr de vouloir réinitialiser le mot de passe de cet utilisateur ? Un email lui sera envoyé.');">
            <button type="submit">Générer et envoyer un lien pour mettre à jour son mot de passe</button>
        </form>

    <form method="POST" action="/users/${user.id}/edit">
        ${emailField}

        <label>Nom :</label><br>
        <input type="text" name="nom" value="${user.nom}" required><br><br>

        <label>Rôle :</label><br>
        <select name="role" required>
            <option value="client" ${user.role === 'client' ? 'selected' : ''}>Client</option>
            <option value="employe" ${user.role === 'employe' ? 'selected' : ''}>Employé (Standard)</option>
            <option value="qualite" ${user.role === 'qualite' ? 'selected' : ''}>Service Qualité</option>
        </select><br><br>

        <label>Type de client :</label><br>
        <select name="type_client" required>
            <option value="Particulier">Particulier</option>
            <option value="Entreprise">Entreprise</option>
            <option value="Mairie">Mairie</option>
            <option value="key_user">Fournisseur</option>
            <option value="Transalp">Transalp</option>
        </select><br><br>
        <button type="submit">Enregistrer les modifications</button>
    </form>
    <br>
    <a href="/users">← Retour à la liste</a>
    `, 'key_user');
};


module.exports = {
    renderUserList,
    renderUserCreateForm,
    renderUserEditForm
};