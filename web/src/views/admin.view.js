const { renderLayout } = require('./layout.view');

const renderDashboard = (stats, userRole) => {
    const causesHtml = stats.topCauses.map(c => `<li>${c.ai_cause} (${c.count})</li>`).join('') || '<li>Aucune donnée</li>';
    const urgentHtml = stats.urgentTickets.map(t => `<li><a href="/tickets/${t.id}">Ticket ${t.nc_number}</a> - ${t.reference || 'N/A'}</li>`).join('') || '<li>Aucun ticket urgent</li>';
    const pendingHtml = stats.pendingTickets.map(t => `<li><a href="/admin/validation">Ticket ${t.nc_number}</a> - En attente IA</li>`).join('') || '<li>Rien à valider</li>';

    const content = `
        <h1>📊 Dashboard Principal</h1>
        <div style="display: flex; gap: 20px; margin-bottom: 30px;">
            <div style="flex: 1; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);">
                <h3 style="margin:0; color: #7f8c8d;">NC Actives</h3>
                <p style="font-size: 32px; font-weight: bold; margin: 10px 0; color: #e74c3c;">${stats.activeNcCount}</p>
            </div>
            <div style="flex: 1; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);">
                <h3 style="margin:0; color: #7f8c8d;">Score IA Moyen</h3>
                <p style="font-size: 32px; font-weight: bold; margin: 10px 0; color: #2980b9;">${stats.avgScore}%</p>
            </div>
            <div style="flex: 1; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);">
                <h3 style="margin:0; color: #7f8c8d;">Top Causes</h3>
                <ul style="margin: 10px 0; padding-left: 20px;">${causesHtml}</ul>
            </div>
        </div>

        <div style="display: flex; gap: 20px;">
            <div style="flex: 1; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);">
                <h3>🚨 Tickets Urgents</h3>
                <ul>${urgentHtml}</ul>
            </div>
            <div style="flex: 1; background: white; padding: 20px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1);">
                <h3>🤖 Validation IA Récentes</h3>
                <ul>${pendingHtml}</ul>
            </div>
        </div>
    `;
    return renderLayout("Dashboard Admin", content, userRole);
};

const renderValidationIA = (tickets, userRole) => {
    let cardsHtml = '';
    if (tickets.length === 0) {
        cardsHtml = '<p>✅ Aucune non-conformité en attente de validation IA.</p>';
    } else {
        cardsHtml = `<div style="display: grid; grid-template-columns: repeat(auto-fill, minmax(300px, 1fr)); gap: 20px;">`;
        tickets.forEach(t => {
            const shortDesc = t.description ? t.description.substring(0, 80) + '...' : 'Aucune description fournie.';
            const graviteText = t.gravity_label ? `${t.gravity_label} (${t.gravity_score}/24)` : 'En attente';

            let photoHtml = `<div style="height: 150px; background: #ddd; display: flex; align-items: center; justify-content: center; color: #888;">Pas de photo</div>`;
            if (t.photos) {
                try {
                    const photosArray = typeof t.photos === 'string' ? JSON.parse(t.photos) : t.photos;
                    if (photosArray && photosArray.length > 0) {
                        photoHtml = `<div style="height: 150px; background: url('/uploads/${photosArray[0]}') center/cover; border-bottom: 1px solid #ddd;"></div>`;
                    }
                } catch(e) {
                    console.error("Erreur lecture photo :", e);
                }
            }

            cardsHtml += `
            <div style="background: white; border-radius: 8px; box-shadow: 0 2px 5px rgba(0,0,0,0.1); overflow: hidden;">
                ${photoHtml} <div style="padding: 15px;">
                    <h3 style="margin: 0 0 10px 0;">${t.nc_number}</h3>
                    <p style="font-size: 14px; color: #555; height: 40px; overflow: hidden;"><em>"${shortDesc}"</em></p>
                    <hr style="border:0; border-top:1px solid #eee;">
                    <p style="margin: 5px 0;"><strong>Cause IA :</strong> <span style="color:#d35400;">${t.ai_cause || 'Inconnue'}</span></p>
                    <p style="margin: 5px 0;"><strong>Gravité :</strong> ${graviteText}</p>
                    <div style="display: flex; gap: 10px; margin-top: 15px;">
                        <a href="/tickets/${t.id}/edit" style="width:100%; text-align: center; background: #3498db; color: white; text-decoration: none; padding: 10px; border-radius: 4px; font-weight: bold;">
                            Accéder à l'analyse et valider
                        </a>
                    </div>
                </div>
            </div>`;
        });
        cardsHtml += `</div>`;
    }

    const content = `
        <h1>🤖 Validation IA</h1>
        <p>Vérifiez les analyses générées par l'IA et validez la création des tickets.</p>
        ${cardsHtml}
    `;
    return renderLayout("Validation IA", content, userRole);
};

module.exports = {
    renderDashboard,
    renderValidationIA
};