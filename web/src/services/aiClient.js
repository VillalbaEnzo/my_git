const http = require('http');

function triggerAnalysis({ ticket_id, description, profil, reference, installation_pose, image_paths }) {
  const body = JSON.stringify({
    ticket_id,
    description,
    profil,
    reference:   reference || '',
    installation_pose:   installation_pose  || null,
    image_paths: image_paths || [],
  });

  const options = {
    hostname: 'ai-worker',
    port:     8000,
    path:     '/analyze',
    method:   'POST',
    headers:  { 'Content-Type': 'application/json', 'Content-Length': Buffer.byteLength(body) },
  };

  const req = http.request(options, (res) => {
    console.log(`[AI] Ticket ${ticket_id} → ${res.statusCode}`);
  });
  req.on('error', (e) => console.error(`[AI] Erreur : ${e.message}`));
  req.write(body);
  req.end();
}

module.exports = { triggerAnalysis };
