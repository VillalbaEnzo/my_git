const { renderLayout } = require('./layout.view');

const renderTicketList = (tickets, userRole) => {
    const isAdmin = userRole === 'qualite' || userRole === 'key_user';
    let listHtml = '<table><tr><th>N° Ticket</th><th>Produit</th><th>Commande</th><th>Date</th><th>Statut</th><th>Gravité</th><th>Responsable</th><th>Actions</th></tr>';

    tickets.forEach(ticket => {
        let actionBtn = `<a href="/tickets/${ticket.id}">Voir</a>`;
        if (isAdmin && (ticket.status === 'ai_completed' || ticket.status === 'manual_completion_required')) {
            actionBtn = `<a href="/admin/validation" style="color: #e67e22; font-weight:bold;">↳ Valider l'IA</a> <br> <a href="/tickets/${ticket.id}">Voir</a>`;
        }
        else if (ticket.status === 'pending_ai') {
            actionBtn = `<span style="color: #7f8c8d; font-size: 0.9em;">En cours d'analyse IA...</span> <br> <a href="/tickets/${ticket.id}">Voir</a>`;
        }

        listHtml += `<tr>
            <td><strong>${ticket.nc_number}</strong></td>
            <td>${ticket.reference || '-'}</td>
            <td>${ticket.order_number || '-'}</td>
            <td>${new Date(ticket.created_at).toLocaleDateString('fr-FR')}</td>
            <td>${ticket.status}</td>
            <td>${ticket.gravity_label || 'En attente'}</td>
            <td>${ticket.assigned_to || 'Non assigné'}</td>
            <td>${actionBtn}</td>
        </tr>`;
    });
    listHtml += '</table>';

    return renderLayout('Tous les tickets', `
    <h1>Tous les tickets</h1>
    ${listHtml}
    `, userRole);
};

const renderTicketDetail = (ticket, userRole) => {
    let adminSection = '';
    if (userRole === 'qualite' || userRole === 'key_user') {
        adminSection = `
            <button onclick="window.location.href='/tickets/${ticket.id}/edit'">
                Modifier l'analyse IA
            </button>
        `;
    }
    let photosHtml = '';
    if (ticket.photos) {
        try {
            const photosArray = typeof ticket.photos === 'string' ? JSON.parse(ticket.photos) : ticket.photos;
            if (photosArray && photosArray.length > 0) {
                photosHtml = `
                <h3>Documents joints</h3>
                <div style="display: flex; gap: 15px; flex-wrap: wrap;">
                    ${photosArray.map(fileName => {
                        const icon = getFileIcon(fileName);
                        const isImage = /\.(jpg|jpeg|png|gif)$/i.test(fileName);
                        return `
                        <a href="/uploads/${fileName}" target="_blank" style="text-decoration: none; color: #333; width: 100px; text-align: center;">
                            <div style="font-size: 40px; height: 80px; display: flex; align-items: center; justify-content: center;">
                                ${isImage ? `<img src="/uploads/${fileName}" style="width:80px; height:80px; object-fit:cover;">` : `<i class="fa-solid ${icon}"></i>`}
                            </div>
                            <div style="font-size: 11px; white-space: nowrap; overflow: hidden; text-overflow: ellipsis;">
                                ${fileName.split('-').slice(1).join('-')}
                            </div>
                        </a>`;
                    }).join('')}
                </div>`;
            }
        } catch(e) { console.error("Erreur affichage photos :", e); }
    }
    return renderLayout(`Ticket ${ticket.nc_number}`, `
    <h1>Ticket ${ticket.nc_number}</h1>
    <p><a href="/tickets">← Retour liste</a></p>
    ${adminSection}

    <h2>Informations générales du ticket</h2>
    <ul>
      <li><strong>Statut actuel :</strong> <span style="background: #e2e7ee; padding: 2px 8px; border-radius: 4px; font-weight: bold;">${ticket.status}</span></li>
      <li><strong>Profil émetteur :</strong> ${ticket.profil}</li>
      <li><strong>Email de contact :</strong> ${ticket.email}</li>
      <li><strong>Nom / Raison Sociale :</strong> ${ticket.nom || '—'}</li>
      <li><strong>Type de client :</strong> ${ticket.type_client || '—'}</li>
      <li><strong>Référence produit :</strong> ${ticket.reference || '—'}</li>
      <li><strong>N° de commande :</strong> ${ticket.order_number || '—'}</li>
      <li><strong>Date de pose :</strong> ${ticket.installation_pose ? new Date(ticket.installation_pose).toLocaleDateString('fr-FR') : '—'}</li>
    </ul>

    <h3>Description fournie par le déclarant</h3>
    <div style="background: #fff; padding: 15px; border: 1px solid #ddd; border-radius: 4px;">
        <p style="white-space: pre-wrap;">${ticket.description || '—'}</p>
    </div>

    <h2>Synthèse actuelle (IA / Validée par Qualité)</h2>
    <ul>
      <li><strong>Type NC retenu :</strong> ${ticket.ai_type_nc || '—'}</li>
      <li><strong>Cause sous-jacente :</strong> ${ticket.ai_cause || '—'}</li>
      <li><strong>Plan d'action standard :</strong> ${ticket.ai_action_generale || '—'}</li>
      <li><strong>Département / Service concerné :</strong> ${ticket.ai_service_impacte || '—'}</li>
      <li><strong>Criticité :</strong> <strong>${ticket.gravity_label || '—'}</strong> ${ticket.gravity_score !== null ? `(${ticket.gravity_score}/24)` : ''}</li>
      <li><strong>Indice de confiance de l'analyse initiale :</strong> ${ticket.ai_confiance ? Math.round(ticket.ai_confiance * 100) + '%' : '—'}</li>
    </ul>
    ${photosHtml}
    <p><strong>Résumé textuel complet :</strong></p>
    <div style="background: #fdfefe; padding: 10px 15px; border-left: 4px solid #0056b3;">
        ${ticket.ai_resume || '—'}
    </div>
    `, userRole);
};

const renderTicketForm = (user = null, userRole = null) => {
    let profileSection = '';
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
    } else if (user && user.role === 'client') {
        profileSection = `
          <input type="hidden" name="profile" id="profile" value="client">
          <input type="hidden" name="email" value="${user.email}">
          <input type="hidden" name="name" value="${user.nom}">
          <input type="hidden" name="clientType" value="${user.type_client}">
          <p><strong>Profil :</strong> Client</p>
          <p><strong>Email :</strong> ${user.email}</p>
          <p><strong>Nom :</strong> ${user.nom}</p>
        `;
    } else {
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
            <option value="Particulier">Particulier</option>
            <option value="Entreprise">Entreprise</option>
            <option value="Mairie">Mairie</option>
            <option value="Fournisseur">Fournisseur</option>
            <option value="Transalp">Transalp</option>
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
        if(!profile) return;
        const isEmployee = (profile.value === 'employe');
        const employeFields = document.getElementById('employe-fields');
        const refInput = document.getElementById('input-reference');
        const orderInput = document.getElementById('input-order');
        employeFields.style.display = isEmployee ? 'block' : 'none';
        refInput.required = isEmployee;
        orderInput.required = isEmployee;
      }
      document.addEventListener('DOMContentLoaded', toggleFields);
    </script>
    `, userRole);
};

const renderEditAiForm = (ticket, userRole) => {
    const g = typeof ticket.gravity_detail === 'string' ? JSON.parse(ticket.gravity_detail) : (ticket.gravity_detail || {});
    const typesNC = ["NCE", "NCF", "NCI", "Non recevable", "SAV"];
    const causes = ["Défaut de fabrication", "Défaut de montage sur site", "Demande d'information", "Erreur de conception", "Info client incorrecte", "Manquement en production", "Manquement en visserie", "Manquement sur site", "Mauvaise communication interservices", "Non respect des délais", "Non-conformités d'audit", "Notice incorrecte", "Pièce endommagée", "Plan incorrect", "Problème de devis", "Rouille"];
    const actions = ["Correction sur le site", "Devis", "Mise à jour conception", "Mise à jour documents", "Réclamation au fournisseur", "Refabrication", "Renvoi pièces"];
    const services = ["Achats / Appro", "ADV", "BE Com", "BE Methode", "Commercial", "Expédition / Assemblage Jeux", "Expédition / Assemblage Sport", "Fournisseur", "Peinture", "Poseur", "Serrurerie", "Transport", "Transalp"];

    const renderOptions = (list, selected) => list.map(item => `<option value="${item}" ${item === selected ? 'selected' : ''}>${item}</option>`).join('');

    return renderLayout(`Validation ${ticket.nc_number}`, `
    <h1>Analyse Complète : ${ticket.nc_number}</h1>
    <form method="POST" action="/tickets/${ticket.id}/confirm" enctype="multipart/form-data" style="max-width: 900px; padding: 20px; background: white;">
        <fieldset style="margin-bottom: 20px;"><legend><strong>Informations Fixes</strong></legend>
            <div style="display:grid; grid-template-columns: 1fr 1fr; gap:10px;">
                <p><strong>Statut :</strong> ${ticket.status}</p>
                <p><strong>Profil :</strong> ${ticket.profil}</p>
                <p><strong>Email :</strong> ${ticket.email}</p>
                <p><strong>Client :</strong> ${ticket.nom || '—'}</p>
            </div>
            <p><strong>Description :</strong><br>${ticket.description}</p>
        </fieldset>

        <fieldset style="margin-bottom: 20px;"><legend><strong>Informations Modifiables</strong></legend>
            <div style="display:grid; grid-template-columns: 1fr 1fr; gap:15px;">
                <div><label>Référence produit :</label><input type="text" name="reference" value="${ticket.reference || ''}" style="width:100%"></div>
                <div><label>N° Commande :</label><input type="text" name="order_number" value="${ticket.order_number || ''}" style="width:100%"></div>
                <div><label>Date de pose :</label><input type="date" name="installation_pose" value="${ticket.installation_pose ? ticket.installation_pose.toISOString().split('T')[0] : ''}" style="width:100%"></div>
            </div>
        </fieldset>

        <fieldset style="margin-bottom: 20px;"><legend><strong>Analyse IA (A valider)</strong></legend>
            <div style="display:grid; grid-template-columns: 1fr 1fr; gap:15px;">
                <div><label>Type NC :</label><select name="ai_type_nc" style="width:100%">${renderOptions(typesNC, ticket.ai_type_nc)}</select></div>
                <div><label>Cause :</label><select name="ai_cause" style="width:100%">${renderOptions(causes, ticket.ai_cause)}</select></div>
                <div><label>Plan d'action :</label><select name="ai_action_generale" style="width:100%">${renderOptions(actions, ticket.ai_action_generale)}</select></div>
                <div><label>Service impacté :</label><select name="ai_service_impacte" style="width:100%">${renderOptions(services, ticket.ai_service_impacte)}</select></div>
            </div>
            <label>Résumé :</label><textarea name="ai_resume" style="width:100%; height:80px;">${ticket.ai_resume || ''}</textarea>
            <label>Indice de confiance :</label><input type="number" step="0.01" name="ai_confiance" value="${ticket.ai_confiance || 0}" style="width:100%">
        </fieldset>
            <fieldset style="margin-bottom: 20px;"><legend><strong>Documents complémentaires</strong></legend>
            <label>Ajouter des photos/documents :</label><br>
            <input type="file" name="fichiers" multiple accept="image/*,.pdf,.doc,.docx">
        </fieldset>
        <h3>Criticité (Gravité)</h3>
        <table style="width:100%; text-align:left;">
            <tr>
                <th>Critère</th>
                <th>Niveau</th>
                <th>Coeff</th>
            </tr>
            ${[
                { key: 'securite', coeff: 3 },
                { key: 'client', coeff: 2 },
                { key: 'cout', coeff: 1 },
                { key: 'impact_poseur', coeff: 2 }
            ].map(({ key, coeff }) => `
                <tr>
                    <td>${key.toUpperCase()}</td>
                    <td>
                        <input type="number" name="grav_${key}" value="${g[key]?.niveau || 0}" min="0" max="3">
                    </td>
                    <td>${coeff}</td>
                </tr>
            `).join('')}
        </table>

        <button type="submit" style="background:#2ecc71; color:white; padding:15px; width:100%; border:none; margin-top:20px;">Valider l'Analyse</button>
    </form>
    `, userRole);
};

const getFileIcon = (fileName) => {
    const ext = fileName.split('.').pop().toLowerCase();
    const icons = {
        'pdf': 'fa-file-pdf',
        'sldprt': 'fa-cube',
        'sldasm': 'fa-cubes',
        'docx': 'fa-file-word',
        'xlsx': 'fa-file-excel',
        'png': 'fa-file-image',
        'jpg': 'fa-file-image',
        'jpeg': 'fa-file-image',
        'zip': 'fa-file-zipper'
    };
    return icons[ext] || 'fa-file';
};

module.exports = {
    renderTicketList,
    renderTicketDetail,
    renderTicketForm,
    renderEditAiForm
};