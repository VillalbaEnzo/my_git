const renderLayout = (title, content, userRole = null) => {
    // Construction dynamique du menu
    let menu = `<a href="/tickets">Transalp NC</a> | <a href="/tickets/new/form">+ Nouveau ticket</a>`;
    
    if (userRole === 'key_user') {
        menu += ` | <a href="/users">Gestion des Comptes</a>`;
    }
    
    if (userRole) {
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

const renderTicketList = (tickets, userRole) => {
    const rows = tickets.map(t => `
    <tr>
      <td><a href="/tickets/${t.id}">${t.nc_number}</a></td>
      <td>${t.profil}</td>
      <td>${t.status}</td>
      <td>${t.ai_type_nc || '—'}</td>
      <td>${t.gravity_label || '—'} ${t.gravity_score !== null ? `(${t.gravity_score}/24)` : ''}</td>
      <td>${new Date(t.created_at).toLocaleString('fr-FR')}</td>
      <td><a href="/tickets/${t.id}">Voir</a></td>
    </tr>`).join('');

    return renderLayout('Liste des tickets', `
    <h1>Non-Conformités (${tickets.length})</h1>
    <table border="1" cellpadding="5" cellspacing="0">
      <thead>
        <tr>
          <th>N° NC</th><th>Profil</th><th>Statut</th><th>Type NC</th><th>Gravité</th><th>Créé le</th><th></th>
        </tr>
      </thead>
      <tbody>
        ${rows || '<tr><td colspan="7">Aucun ticket</td></tr>'}
      </tbody>
    </table>`, userRole);
};

const renderTicketDetail = (ticket, userRole) => {
    return renderLayout(`Ticket ${ticket.nc_number}`, `
    <h1>Ticket ${ticket.nc_number}</h1>
    <p><a href="/tickets">← Retour liste</a></p>
    
    <h2>Informations générales</h2>
    <ul>
      <li><strong>Statut :</strong> ${ticket.status}</li>
      <li><strong>Profil :</strong> ${ticket.profil}</li>
      <li><strong>Email :</strong> ${ticket.email}</li>
      <li><strong>Nom/Raison Sociale :</strong> ${ticket.nom || '—'}</li>
      <li><strong>Type de client :</strong> ${ticket.type_client || '—'}</li>
      <li><strong>Référence produit :</strong> ${ticket.reference || '—'}</li>
      <li><strong>N° de commande :</strong> ${ticket.order_number || '—'}</li>
      <li><strong>Date de pose :</strong> ${ticket.installation_pose || '—'}</li>
    </ul>
    
    <h3>Description brute</h3>
    <p>${ticket.description || '—'}</p>
    
    <h2>Analyse IA</h2>
    <ul>
      <li><strong>Type NC détecté :</strong> ${ticket.ai_type_nc || '—'}</li>
      <li><strong>Cause détectée :</strong> ${ticket.ai_cause || '—'}</li>
      <li><strong>Action générale :</strong> ${ticket.ai_action_generale || '—'}</li>
      <li><strong>Service impacté :</strong> ${ticket.ai_service_impacte || '—'}</li>
      <li><strong>Confiance IA :</strong> ${ticket.ai_confiance ? Math.round(ticket.ai_confiance * 100) + '%' : '—'}</li>
    </ul>
    <p><strong>Résumé de l'IA :</strong><br>${ticket.ai_resume || '—'}</p>
    `, userRole);
};

const renderTicketForm = (user = null, userRole = null) => {
    let profileSection = '';
    
    // Si connecté et Employé
    if (user && user.role === 'employe') {
        profileSection = `
          <input type="hidden" name="profile" id="profile" value="employe">
          <p><strong>Profil :</strong> Employé Transalp</p>
          <label>Email *</label><br>
          <input type="email" name="email" value="${user.email}" required><br><br>
          <label>Nom complet *</label><br>
          <input type="text" name="name" value="${user.nom}" required><br><br>
          <input type="hidden" name="clientType" value="Interne">
        `;
    } 
    // Si connecté et Client
    else if (user && user.role === 'client') {
        profileSection = `
          <input type="hidden" name="profile" id="profile" value="client">
          <input type="hidden" name="email" value="${user.email}">
          <input type="hidden" name="name" value="${user.nom}">
          <input type="hidden" name="clientType" value="${user.type_client}">
          <p><strong>Profil :</strong> Client</p>
          <p><strong>Email :</strong> ${user.email}</p>
          <p><strong>Nom :</strong> ${user.nom}</p>
        `;
    } 
    // Si non connecté (Public)
    else {
        profileSection = `
          <label>Je suis *</label><br>
          <select name="profile" id="profile" onchange="toggleFields()" required>
            <option value="">-- Choisir --</option>
            <option value="client">Client</option>
            <option value="employe">Employé Transalp</option>
          </select><br><br>
          
          <label>Email *</label><br>
          <input type="email" name="email" required placeholder="votre@email.fr"><br><br>
          
          <label>Nom complet ou Raison Sociale *</label><br>
          <input type="text" name="name" required placeholder="Ex: Jean Dupont"><br><br>
          
          <label>Type de client *</label><br>
          <select name="clientType" required>
            <option value="Particulier">Particulier (B2C)</option>
            <option value="Entreprise">Entreprise (B2B)</option>
            <option value="Revendeur">Revendeur</option>
          </select><br><br>
        `;
    }

    return renderLayout('Nouveau ticket', `
    <h1>Nouveau ticket NC</h1>
    <form method="POST" action="/tickets" enctype="multipart/form-data">
      <h3>Identité</h3>
      ${profileSection}
      
      <h3>La non-conformité</h3>
      <div id="employe-fields" style="display: ${user && user.role === 'employe' ? 'block' : 'none'};">
          <label>Référence produit <span style="color:red">*</span></label><br>
          <input type="text" name="reference" id="input-reference" placeholder="ex: BC01" ${user && user.role === 'employe' ? 'required' : ''}><br><br>
          
          <label>N° de commande <span style="color:red">*</span></label><br>
          <input type="text" name="orderNumber" id="input-order" placeholder="ex: CMD-123" ${user && user.role === 'employe' ? 'required' : ''}><br><br>
      </div>
      
      <label>Description détaillée *</label><br>
      <textarea name="description" required placeholder="Description..."></textarea>
      <br><br>
      
      <label>Date de pose</label><br>
      <input type="date" name="installationDate">
      <br><br>
      
      <label>Photos / Vidéos</label><br>
      <input type="file" name="fichiers" multiple accept="image/*,video/*">
      <br><br>
      
      <button type="submit">Soumettre le ticket</button>
    </form>

    <script>
      function toggleFields() {
        const profile = document.getElementById('profile');
        if(!profile) return; // Sécurité si le select n'existe pas (client connecté)
        
        const isEmployee = (profile.value === 'employe');
        const employeFields = document.getElementById('employe-fields');
        const refInput = document.getElementById('input-reference');
        const orderInput = document.getElementById('input-order');
        
        employeFields.style.display = isEmployee ? 'block' : 'none';
        refInput.required = isEmployee;
        orderInput.required = isEmployee;
      }
      
      // Exécuter au chargement pour s'assurer du bon état
      document.addEventListener('DOMContentLoaded', toggleFields);
    </script>
    `, userRole);
};

module.exports = {
    renderTicketList,
    renderTicketDetail,
    renderTicketForm
};