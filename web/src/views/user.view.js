const renderLayout = (title, content) => {
    return `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>${title} — Transalp NC</title>
</head>
<body>
  <header>
    <a href="/tickets">Transalp NC</a> | 
    <a href="/tickets/new/form">+ Nouveau ticket</a> |
    <a href="/users">Gestion des Comptes (Key User)</a> | 
    <a href="/auth/logout">Déconnexion</a>
  </header>
  <hr>
  <main>${content}</main>
</body>
</html>`;
};

// On ajoute currentUserId en paramètre pour savoir qui est connecté
const renderUserList = (users, currentUserId) => {
    const rows = users.map(u => {
        // Si c'est le compte de l'utilisateur connecté, on ne met pas les liens de modification
        const actions = (u.id === currentUserId) 
            ? `<i>(Votre compte)</i>` 
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
    
    <div style="margin-bottom: 20px;">
        <a href="/users/new" style="padding: 8px 15px; background: #28a745; color: white; text-decoration: none; border-radius: 4px;">+ Ajouter un nouveau compte</a>
    </div>

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
    `);
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

        <label>Type de client (si applicable) :</label><br>
        <input type="text" name="type_client" placeholder="Ex: B2B, Particulier..."><br><br>

        <button type="submit" style="padding: 8px 15px; background: #007bff; color: white; border: none; cursor: pointer;">Créer le compte et envoyer l'email</button>
    </form>
    <br>
    <a href="/users">← Retour à la liste</a>
    `);
};

const renderUserEditForm = (user) => {
    return renderLayout(`Modifier l'utilisateur ${user.id}`, `
    <h1>Modifier le compte : ${user.email}</h1>
    <form method="POST" action="/users/${user.id}/edit">
        <label>Nom :</label><br>
        <input type="text" name="nom" value="${user.nom}" required><br><br>

        <label>Rôle :</label><br>
        <select name="role" required>
            <option value="client" ${user.role === 'client' ? 'selected' : ''}>Client</option>
            <option value="employe" ${user.role === 'employe' ? 'selected' : ''}>Employé (Standard)</option>
            <option value="qualite" ${user.role === 'qualite' ? 'selected' : ''}>Service Qualité</option>
            <option value="key_user" ${user.role === 'key_user' ? 'selected' : ''}>Key User</option>
        </select><br><br>

        <label>Type de client (si applicable) :</label><br>
        <input type="text" name="type_client" value="${user.type_client || ''}"><br><br>

        <button type="submit">Enregistrer les modifications</button>
    </form>
    <br>
    <a href="/users">← Retour à la liste</a>
    `);
};

module.exports = {
    renderUserList,
    renderUserCreateForm,
    renderUserEditForm
};