import { WebSocketServer, WebSocket } from 'ws';
import { ChromecastProvider } from './providers/chromecast';
import { AirPlayProvider } from './providers/airplay'
import { CastDevice } from './core/interfaces';
import * as http from 'http';
import * as https from 'https';
import * as url from 'url';

const PORT = 8080;
const HOST = '127.0.0.1';
const PROXY_PORT = 8081;
const PROXY_HOST = '0.0.0.0'; // Écoute sur toutes les interfaces
const LOCAL_IP = '192.168.1.208'; // Utiliser l'IP pour les URLs envoyées à Chromecast

const providers = [
    new ChromecastProvider(),
    new AirPlayProvider()
];


// NOUVEAU : On stocke tous les appareils trouvés dans un dictionnaire (clé = id, valeur = CastDevice)
const chromecastProvider = new ChromecastProvider();
const discoveredDevices = new Map<string, CastDevice>();

// On lance la découverte sur TOUS les protocoles en même temps !
providers.forEach(provider => {
    provider.discoverDevices((device) => {
        discoveredDevices.set(device.id, device);
        console.log(`📡 Appareil disponible : ${device.name} [${device.provider}]`);
    });
});

chromecastProvider.discoverDevices((device) => {
    discoveredDevices.set(device.id, device);
    console.log(`📡 Appareil disponible : ${device.name} [${device.provider}]`);
});

// ========================
// PROXY HTTP POUR LES VIDÉOS
// ========================

// Cache pour stocker les cookies/headers des sessions
const proxySessionCache: { [key: string]: any } = {};
let sessionCounter = 0;

const proxyServer = http.createServer((req, res) => {
	if (!req.url) return res.writeHead(400).end();

	const urlParts = new url.URL(req.url, `http://localhost`);
	const sessionId = urlParts.searchParams.get('session');
	let proxyUrl = '';
	let requestHeaders: any = {
		'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) Chrome/120.0.0.0',
		'Accept': '*/*',
		'Accept-Language': 'en-US,en;q=0.9',
		'Accept-Encoding': 'gzip, deflate, br',
	};

	// Récupérer l'URL et les headers du cache si sessionId existe
	if (sessionId && proxySessionCache[sessionId]) {
		const session = proxySessionCache[sessionId];
		proxyUrl = session.url;

		// Appliquer les headers et cookies de la session
		if (session.headers) {
			Object.assign(requestHeaders, session.headers);
		}
		if (session.cookies) {
			const cookieString = Object.entries(session.cookies)
				.map(([name, value]) => `${name}=${value}`)
				.join('; ');
			requestHeaders['Cookie'] = cookieString;
		}
		console.log(`✅ Session trouvée pour ${sessionId}`);
	} else {
		// Fallback: URL encodée directement (mode legacy)
		proxyUrl = decodeURIComponent(req.url.slice(1));
	}

	if (!proxyUrl.startsWith('http')) {
		res.writeHead(400, { 'Content-Type': 'text/plain' }).end('Invalid URL');
		return;
	}

	console.log(`📡 Proxy: Demande pour ${proxyUrl}`);

	// Déterminer le protocole (HTTP ou HTTPS)
	const protocol = proxyUrl.startsWith('https') ? https : http;
	const parsedUrl = new url.URL(proxyUrl);

	// Ajouter les headers par défaut
	requestHeaders['Referer'] = parsedUrl.origin;
	requestHeaders['Origin'] = parsedUrl.origin;

	const options = {
		hostname: parsedUrl.hostname,
		port: parsedUrl.port,
		path: parsedUrl.pathname + parsedUrl.search,
		method: 'GET',
		headers: requestHeaders,
		timeout: 30000,
	};

	const proxyReq = protocol.request(options, (proxyRes) => {
		// Copier les headers importants
		const headersToPass = [
			'content-type',
			'content-length',
			'content-range',
			'accept-ranges',
			'access-control-allow-origin',
			'cache-control',
		];

		const responseHeaders: { [key: string]: any } = {};
		headersToPass.forEach((header) => {
			if (proxyRes.headers[header]) {
				responseHeaders[header] = proxyRes.headers[header];
			}
		});

		// Ajouter CORS pour Chromecast
		responseHeaders['Access-Control-Allow-Origin'] = '*';
		responseHeaders['Access-Control-Allow-Methods'] = 'GET, HEAD, OPTIONS';
		responseHeaders['Access-Control-Allow-Headers'] = 'Content-Type, Range, Authorization';

		res.writeHead(proxyRes.statusCode || 200, responseHeaders);
		proxyRes.pipe(res);
	});

	proxyReq.on('error', (error) => {
		console.error('❌ Proxy error:', error);
		res.writeHead(502, { 'Content-Type': 'text/plain' }).end('Bad Gateway');
	});

	proxyReq.on('timeout', () => {
		proxyReq.destroy();
		res.writeHead(504, { 'Content-Type': 'text/plain' }).end('Gateway Timeout');
	});

	req.pipe(proxyReq);
});

proxyServer.listen(PROXY_PORT, PROXY_HOST, () => {
	console.log(`🔀 Proxy HTTP démarré sur http://${PROXY_HOST}:${PROXY_PORT}`);
});

// ========================
// WebSocket pour commandes
// ========================

const wss = new WebSocketServer({ port: PORT, host: HOST });
console.log(`🚀 Serveur Cast initialisé sur ws://${HOST}:${PORT}`);

wss.on('connection', (ws: WebSocket) => {
	ws.on('message', async (message: Buffer) => {
		try {
			const data = JSON.parse(message.toString());

			// NOUVEAU : L'extension demande la liste des TV
			if (data.type === 'GET_DEVICES') {
				const deviceList = Array.from(discoveredDevices.values());
				ws.send(JSON.stringify({ type: 'DEVICE_LIST', devices: deviceList }));
			}

			// MODIFIÉ : On utilise le deviceId envoyé par l'extension avec les cookies
			else if (data.type === 'CAST_REQUEST') {
				const targetDevice = discoveredDevices.get(data.deviceId);

				if (targetDevice) {
					try {
                        if (data.castType === "PAGE") {
                            console.log(`➡️ Envoi de la PAGE WEB vers : ${targetDevice.name}...`);
                            // On appelle une nouvelle méthode castPage
                            await chromecastProvider.castPage(data.media.url, targetDevice.ip);
                            ws.send(JSON.stringify({ type: 'CAST_SUCCESS' }));
                        } else {
                            console.log(`➡️ Envoi de la VIDÉO vers : ${targetDevice.name}...`);

				if (targetDevice) {
					console.log(`➡️ Envoi vers : ${targetDevice.name}...`);
					try {
						// Préparer le media avec le proxy si nécessaire
						const media = { ...data.media };
						if (media.url && (media.url.startsWith('http://') || media.url.startsWith('https://'))) {
							// Créer une session ID de proxy
							const sessionId = `session_${++sessionCounter}_${Date.now()}`;

							// Stocker la session avec cookies et headers
							proxySessionCache[sessionId] = {
								url: media.url,
								cookies: data.media.cookies || {},
								headers: data.media.headers || {}
							};

							// Créer l'URL du proxy avec la session ID
							media.proxyUrl = `http://${LOCAL_IP}:${PROXY_PORT}/?session=${sessionId}`;
							console.log(`🔀 Proxy Session: ${sessionId}`);
							console.log(`🔀 URL Proxy: ${media.proxyUrl}`);

							// Nettoyer la session après 1 heure
							setTimeout(() => {
								delete proxySessionCache[sessionId];
							}, 3600000);
						}
						await chromecastProvider.cast(media, targetDevice.ip);
						ws.send(JSON.stringify({ type: 'CAST_SUCCESS' }));
					} catch (error) {
						console.error('❌ Échec du cast :', error);
					}
				} else {
					console.error('⚠️ Appareil cible introuvable.');
				}
			}
			else if (data.type === 'CONTROL_REQUEST') {
				try {
					switch (data.action) {
						case 'PAUSE': await chromecastProvider.pause(); break;
						case 'RESUME': await chromecastProvider.resume(); break;
						case 'STOP': await chromecastProvider.stop(); break;
						// NOUVELLES COMMANDES :
						case 'SET_VOLUME':
							if (data.level !== undefined) await chromecastProvider.setVolume(data.level);
							break;
						case 'SEEK':
							if (data.time !== undefined) await chromecastProvider.seek(data.time);
							break;
						default: console.log('⚠️ Action inconnue :', data.action);
					}
					ws.send(JSON.stringify({ type: 'CONTROL_SUCCESS', action: data.action }));
				} catch (error) {
					console.error(`❌ Échec de l'action ${data.action} :`, error);
				}
			}
		} catch (error) {
			console.error('❌ Erreur générale :', error);
		}
	});
});
