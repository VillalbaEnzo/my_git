const express = require('express');
const multer  = require('multer');
const path    = require('path');
const pool    = require('../services/db');
const { triggerAnalysis } = require('../services/aiClient');

const router = express.Router();

const storage = multer.diskStorage({
  destination: '/app/uploads',
  filename: (req, file, cb) => {
    const unique = Date.now() + '-' + Math.round(Math.random() * 1e6);
    cb(null, unique + path.extname(file.originalname));
  },
});
const upload = multer({ storage, limits: { fileSize: 20 * 1024 * 1024 } });

// ── Liste des tickets ────────────────────────────────────────────────────────
router.get('/', async (req, res) => {
  try {
    const [rows] = await pool.query(
      'SELECT id, nc_number, profil, status, ai_type_nc, gravity_label, gravity_score, created_at FROM tickets ORDER BY id DESC'
    );
    res.send(renderList(rows));
  } catch (e) {
    res.status(500).send(`<pre>Erreur DB : ${e.message}</pre>`);
  }
});

// ── Détail d'un ticket ───────────────────────────────────────────────────────
router.get('/:id', async (req, res) => {
  try {
    const [[ticket]] = await pool.query('SELECT * FROM tickets WHERE id = ?', [req.params.id]);
    if (!ticket) return res.status(404).send('<p>Ticket introuvable</p>');
    res.send(renderDetail(ticket));
  } catch (e) {
    res.status(500).send(`<pre>Erreur DB : ${e.message}</pre>`);
  }
});

// ── Formulaire création ──────────────────────────────────────────────────────
router.get('/new/form', (req, res) => {
  res.send(renderForm());
});

// ── Soumission ───────────────────────────────────────────────────────────────
router.post('/', upload.array('fichiers', 10), async (req, res) => {
  try {
    const { profil, email, description, reference, installation_pose } = req.body;
    const files = (req.files || []).map(f => f.filename);

    // Numéro NC auto
    const [[{ max_id }]] = await pool.query('SELECT COALESCE(MAX(id), 0) AS max_id FROM tickets');
    const nc_number = 'NC-' + String(max_id + 1).padStart(4, '0');

    const [result] = await pool.query(
      `INSERT INTO tickets (nc_number, email, profil, description, installation_pose, status)
       VALUES (?, ?, ?, ?, ?, 'pending_ai')`,
      [nc_number, email, profil, description, installation_pose || null]
    );
    const ticket_id = result.insertId;

    // Lance l'IA en arrière-plan
    triggerAnalysis({ ticket_id, description, profil, reference, installation_pose, image_paths: files });

    res.redirect(`/tickets/${ticket_id}?created=1`);
  } catch (e) {
    res.status(500).send(`<pre>Erreur création : ${e.message}</pre>`);
  }
});

// ────────────────────────────────────────────────────────────────────────────
// Rendus HTML
// ────────────────────────────────────────────────────────────────────────────

function layout(title, body) {
  return `<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>${title} — Transalp NC</title>
  <style>
    *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }
    body { font-family: system-ui, sans-serif; background: #f4f4f5; color: #18181b; }
    header { background: #1e40af; color: white; padding: 1rem 2rem; display: flex; align-items: center; gap: 1rem; }
    header a { color: white; text-decoration: none; font-weight: 600; font-size: 1.1rem; }
    nav a { color: #93c5fd; font-size: .9rem; }
    main { max-width: 1000px; margin: 2rem auto; padding: 0 1rem; }
    h1 { font-size: 1.4rem; margin-bottom: 1.5rem; }
    h2 { font-size: 1.1rem; margin-bottom: .75rem; color: #3f3f46; }

    /* Boutons */
    .btn { display: inline-block; padding: .5rem 1.2rem; border-radius: 6px; font-size: .9rem; cursor: pointer; text-decoration: none; border: none; }
    .btn-primary { background: #1e40af; color: white; }
    .btn-primary:hover { background: #1d4ed8; }
    .btn-sm { padding: .3rem .8rem; font-size: .8rem; }

    /* Badges statut */
    .badge { display: inline-block; padding: .2rem .6rem; border-radius: 999px; font-size: .75rem; font-weight: 600; }
    .badge-pending  { background: #fef9c3; color: #854d0e; }
    .badge-ai       { background: #dcfce7; color: #166534; }
    .badge-manual   { background: #fee2e2; color: #991b1b; }

    /* Badges gravité */
    .grav-Aucun    { background: #e4e4e7; color: #52525b; }
    .grav-Mineur   { background: #dbeafe; color: #1e40af; }
    .grav-Moyen    { background: #fef9c3; color: #854d0e; }
    .grav-Majeur   { background: #ffedd5; color: #9a3412; }
    .grav-Critique { background: #fee2e2; color: #991b1b; }

    /* Table */
    table { width: 100%; border-collapse: collapse; background: white; border-radius: 8px; overflow: hidden; box-shadow: 0 1px 3px rgba(0,0,0,.1); }
    th { background: #f1f5f9; text-align: left; padding: .75rem 1rem; font-size: .8rem; text-transform: uppercase; letter-spacing: .05em; color: #64748b; }
    td { padding: .75rem 1rem; border-top: 1px solid #f1f5f9; font-size: .9rem; }
    tr:hover td { background: #f8fafc; }

    /* Formulaire */
    .card { background: white; border-radius: 8px; padding: 1.5rem; box-shadow: 0 1px 3px rgba(0,0,0,.1); margin-bottom: 1.5rem; }
    .form-group { margin-bottom: 1rem; }
    label { display: block; font-size: .85rem; font-weight: 600; margin-bottom: .3rem; color: #3f3f46; }
    input, select, textarea {
      width: 100%; padding: .6rem .8rem; border: 1px solid #d4d4d8;
      border-radius: 6px; font-size: .9rem; font-family: inherit;
    }
    input:focus, select:focus, textarea:focus { outline: 2px solid #1e40af; border-color: transparent; }
    textarea { resize: vertical; min-height: 100px; }
    .hint { font-size: .75rem; color: #71717a; margin-top: .25rem; }
    .field-optional { display: none; }

    /* Détail */
    .grid-2 { display: grid; grid-template-columns: 1fr 1fr; gap: 1rem; }
    .kv { margin-bottom: .6rem; }
    .kv .key { font-size: .75rem; color: #71717a; text-transform: uppercase; letter-spacing: .05em; }
    .kv .val { font-size: .95rem; font-weight: 500; margin-top: .1rem; }
    .alert { padding: .75rem 1rem; border-radius: 6px; margin-bottom: 1rem; font-size: .9rem; }
    .alert-success { background: #dcfce7; color: #166534; }
    .score-bar { height: 10px; background: #e4e4e7; border-radius: 999px; margin-top: .4rem; }
    .score-fill { height: 100%; border-radius: 999px; background: #1e40af; }
    pre.raw { background: #f4f4f5; padding: 1rem; border-radius: 6px; font-size: .78rem; overflow-x: auto; white-space: pre-wrap; }
  </style>
</head>
<body>
  <header>
    <a href="/tickets">Transalp NC</a>
    <nav><a href="/tickets/new/form">+ Nouveau ticket</a></nav>
  </header>
  <main>${body}</main>
</body>
</html>`;
}

function statusBadge(status) {
  const map = {
    pending_ai:                 ['badge-pending', 'En attente IA'],
    ai_completed:               ['badge-ai',      'IA complété'],
    manual_completion_required: ['badge-manual',  'Manuel requis'],
  };
  const [cls, label] = map[status] || ['badge-pending', status];
  return `<span class="badge ${cls}">${label}</span>`;
}

function gravBadge(label) {
  if (!label) return '—';
  return `<span class="badge grav-${label}">${label}</span>`;
}

// ── Vue : liste ──────────────────────────────────────────────────────────────
function renderList(rows) {
  const tbody = rows.map(r => `
    <tr>
      <td><a href="/tickets/${r.id}">${r.nc_number}</a></td>
      <td>${r.profil}</td>
      <td>${statusBadge(r.status)}</td>
      <td>${r.ai_type_nc || '—'}</td>
      <td>${gravBadge(r.gravity_label)}${r.gravity_score != null ? ` <small>(${r.gravity_score}/24)</small>` : ''}</td>
      <td>${new Date(r.created_at).toLocaleString('fr-FR')}</td>
      <td><a href="/tickets/${r.id}" class="btn btn-primary btn-sm">Voir</a></td>
    </tr>`).join('');

  return layout('Liste des tickets', `
    <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:1.5rem">
      <h1>Non-Conformités (${rows.length})</h1>
      <a href="/tickets/new/form" class="btn btn-primary">+ Nouveau ticket</a>
    </div>
    <table>
      <thead><tr>
        <th>N° NC</th><th>Profil</th><th>Statut</th>
        <th>Type NC</th><th>Gravité</th><th>Créé le</th><th></th>
      </tr></thead>
      <tbody>${tbody || '<tr><td colspan="7" style="text-align:center;color:#71717a">Aucun ticket</td></tr>'}</tbody>
    </table>`);
}

// ── Vue : formulaire ─────────────────────────────────────────────────────────
function renderForm() {
  return layout('Nouveau ticket', `
    <h1>Nouveau ticket NC</h1>
    <form method="POST" action="/tickets" enctype="multipart/form-data">
      <div class="card">
        <h2>Qui êtes-vous ?</h2>
        <div class="form-group">
          <label>Je suis *</label>
          <select name="profil" id="profil" onchange="toggleFields()" required>
            <option value="">-- Choisir --</option>
            <option value="client">Client</option>
            <option value="employe">Employé Transalp</option>
          </select>
        </div>
        <div class="form-group">
          <label>Email *</label>
          <input type="email" name="email" required placeholder="votre@email.fr">
        </div>
      </div>

      <div class="card">
        <h2>La non-conformité</h2>
        <div class="form-group field-optional" id="field-reference">
          <label>Référence produit</label>
          <input type="text" name="reference" placeholder="ex: 1.02, BC01...">
          <p class="hint">Si vous avez la référence article, l'IA s'en servira en priorité.</p>
        </div>
        <div class="form-group">
          <label>Description détaillée *</label>
          <textarea name="description" required placeholder="Décrivez le problème avec le maximum de détails..."></textarea>
        </div>
        <div class="form-group">
          <label>Date de pose / livraison estimée</label>
          <input type="date" name="installation_pose">
          <p class="hint">Permet de distinguer NCE, SAV, etc.</p>
        </div>
        <div class="form-group">
          <label>Photos / Vidéos</label>
          <input type="file" name="fichiers" multiple accept="image/*,video/*">
          <p class="hint">Plusieurs fichiers acceptés. Vidéo : une frame sera extraite.</p>
        </div>
      </div>

      <button type="submit" class="btn btn-primary">Soumettre le ticket</button>
    </form>

    <script>
      function toggleFields() {
        const profil = document.getElementById('profil').value;
        const refField = document.getElementById('field-reference');
        refField.style.display = profil === 'employe' ? 'block' : 'none';
      }
    </script>`);
}

// ── Vue : détail ─────────────────────────────────────────────────────────────
function renderDetail(t) {
  const created = t.created_at ? new Date(t.created_at).toLocaleString('fr-FR') : '—';
  const updated = t.updated_at ? new Date(t.updated_at).toLocaleString('fr-FR') : '—';
  const score   = t.gravity_score ?? 0;
  const pct     = Math.round((score / 24) * 100);

  const created_param = '';
  const alertHtml = `
    <div class="alert alert-success">
      ✅ Ticket <strong>${t.nc_number}</strong> créé. L'IA analyse en arrière-plan — 
      rafraîchis la page dans 1 à 2 minutes.
    </div>`;

  let gravDetail = '';
  try {
    const d = typeof t.gravity_detail === 'string' ? JSON.parse(t.gravity_detail) : t.gravity_detail;
    if (d) {
      const rows = Object.entries(d).map(([k, v]) =>
        `<tr><td>${k}</td><td>${v.niveau}/3</td><td>×${v.coeff}</td><td><strong>${v.points} pts</strong></td></tr>`
      ).join('');
      gravDetail = `<table style="width:100%;font-size:.85rem">
        <thead><tr><th>Critère</th><th>Niveau</th><th>Coeff</th><th>Points</th></tr></thead>
        <tbody>${rows}</tbody>
      </table>`;
    }
  } catch (_) {}

  let visualHtml = '';
  try {
    const va = typeof t.ai_visual_analyses === 'string' ? JSON.parse(t.ai_visual_analyses) : t.ai_visual_analyses;
    if (va && va.length) {
      visualHtml = va.map(a => `
        <div style="margin-bottom:.75rem;padding:.75rem;background:#f8fafc;border-radius:6px;font-size:.85rem">
          <strong>${a.file}</strong><br>
          ${a.description_visuelle || a.error || ''}
          ${a.elements_omis?.length ? `<br><em>Éléments omis : ${a.elements_omis.join(', ')}</em>` : ''}
        </div>`).join('');
    }
  } catch (_) {}

  return layout(`Ticket ${t.nc_number}`, `
    <div style="display:flex;justify-content:space-between;align-items:center;margin-bottom:1rem">
      <h1>${t.nc_number} ${statusBadge(t.status)}</h1>
      <a href="/tickets" style="font-size:.85rem;color:#1e40af">← Retour liste</a>
    </div>

    <div class="card">
      <h2>Informations générales</h2>
      <div class="grid-2">
        <div class="kv"><div class="key">Profil</div><div class="val">${t.profil}</div></div>
        <div class="kv"><div class="key">Email</div><div class="val">${t.email}</div></div>
        <div class="kv"><div class="key">Date pose</div><div class="val">${t.installation_pose || '—'}</div></div>
        <div class="kv"><div class="key">Créé le</div><div class="val">${created}</div></div>
        <div class="kv"><div class="key">Mis à jour</div><div class="val">${updated}</div></div>
      </div>
      <div class="kv" style="margin-top:.5rem">
        <div class="key">Description</div>
        <div class="val">${t.description || '—'}</div>
      </div>
    </div>

    <div class="card">
      <h2>Résultat IA</h2>
      <div class="grid-2">
        <div class="kv"><div class="key">Type NC</div><div class="val">${t.ai_type_nc || '—'}</div></div>
        <div class="kv"><div class="key">Cause</div><div class="val">${t.ai_cause || '—'}</div></div>
        <div class="kv"><div class="key">Action générale</div><div class="val">${t.ai_action_generale || '—'}</div></div>
        <div class="kv"><div class="key">Service impacté</div><div class="val">${t.ai_service_impacte || '—'}</div></div>
        <div class="kv"><div class="key">Famille achat détectée</div><div class="val">${t.matched_famille_achat || '—'} ${t.matched_keyword ? `<small>(«${t.matched_keyword}»)</small>` : ''}</div></div>
        <div class="kv"><div class="key">Confiance IA</div><div class="val">${t.ai_confiance ? Math.round(t.ai_confiance * 100) + '%' : '—'}</div></div>
      </div>
      ${t.ai_resume ? `<div class="kv"><div class="key">Résumé</div><div class="val">${t.ai_resume}</div></div>` : ''}
      ${t.ai_errors ? `<div class="kv"><div class="key">Erreurs IA</div><div class="val"><pre class="raw">${t.ai_errors}</pre></div></div>` : ''}
    </div>

    <div class="card">
      <h2>Indice de gravité — ${gravBadge(t.gravity_label)} ${t.gravity_score != null ? `${t.gravity_score}/24` : ''}</h2>
      ${t.gravity_score != null ? `<div class="score-bar"><div class="score-fill" style="width:${pct}%"></div></div>` : ''}
      <div style="margin-top:1rem">${gravDetail}</div>
    </div>

    ${visualHtml ? `<div class="card"><h2>Analyse visuelle</h2>${visualHtml}</div>` : ''}

    <p style="text-align:right;margin-top:1rem;display:flex;gap:.5rem;justify-content:flex-end">
      <button onclick="location.reload()" class="btn btn-primary btn-sm">↻ Rafraîchir</button>
      <form method="POST" action="/tickets/${t.id}/reanalyze" style="margin:0">
        <button type="submit" class="btn btn-sm" style="background:#7c3aed;color:white"
          onclick="return confirm('Relancer l\\'analyse IA sur ce ticket ?')">
          ⚡ Re-analyser
        </button>
      </form>
    </p>`);
}

router.post('/:id/reanalyze', async (req, res) => {
  try {
    const [[ticket]] = await pool.query(
      'SELECT * FROM tickets WHERE id = ?', [req.params.id]
    );
    if (!ticket) return res.status(404).send('Ticket introuvable');

    // Remet le statut en pending
    await pool.query(
      "UPDATE tickets SET status = 'pending_ai', updated_at = NOW() WHERE id = ?",
      [ticket.id]
    );

    // Récupère les fichiers déjà uploadés
    const visual = typeof ticket.ai_visual_analyses === 'string'
      ? JSON.parse(ticket.ai_visual_analyses || '[]')
      : (ticket.ai_visual_analyses || []);
    const image_paths = visual.map(v => v.file).filter(Boolean);

    triggerAnalysis({
      ticket_id:   ticket.id,
      description: ticket.description,
      profil:      ticket.profil,
      reference:   ticket.reference || '',
      date_pose:   ticket.date_pose || null,
      image_paths,
    });

    res.redirect(`/tickets/${ticket.id}`);
  } catch (e) {
    res.status(500).send(`<pre>Erreur : ${e.message}</pre>`);
  }
});

module.exports = router;