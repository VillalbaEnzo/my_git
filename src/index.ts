import { WebSocketServer, WebSocket } from 'ws';
import { ChromecastProvider } from './providers/chromecast';
import { AirPlayProvider } from './providers/airplay'
import { CastDevice } from './core/interfaces';

const PORT = 8080;
const HOST = '127.0.0.1';

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

// -------------------------
// Ajout: utilitaires d'extraction média
// -------------------------
type MediaSource = {
	url: string;
	type?: string;
	quality?: string;
	thumbnail?: string;
	raw?: any;
};

async function fetchText(url: string, timeout = 10000): Promise<string> {
	const controller = new AbortController();
	const id = setTimeout(() => controller.abort(), timeout);
	try {
		const res = await fetch(url, { signal: controller.signal, redirect: 'follow' });
		return await res.text();
	} finally {
		clearTimeout(id);
	}
}

function resolveUrl(base: string, relative: string) {
	try { return new URL(relative, base).toString(); }
	catch { return relative; }
}

async function parseM3U8(manifestUrl: string): Promise<MediaSource[]> {
	try {
		const txt = await fetchText(manifestUrl);
		const variants: MediaSource[] = [];
		const re = /#EXT-X-STREAM-INF:([^\n\r]*)[\r\n]+([^\r\n]+)/g;
		let m;
		while ((m = re.exec(txt)) !== null) {
			const attrs = m[1];
			const uri = m[2].trim();
			const resMatch = attrs.match(/RESOLUTION=(\d+x\d+)/);
			const bwMatch = attrs.match(/BANDWIDTH=(\d+)/);
			const quality = resMatch ? resMatch[1] : bwMatch ? `${Math.round(parseInt(bwMatch[1], 10) / 1000)}kbps` : undefined;
			variants.push({ url: resolveUrl(manifestUrl, uri), type: 'application/x-mpegurl', quality, raw: attrs });
		}
		if (variants.length) return variants;
		return [{ url: manifestUrl, type: 'application/x-mpegurl' }];
	} catch (e) {
		return [{ url: manifestUrl, type: 'application/x-mpegurl' }];
	}
}

async function extractMediaFromUrl(pageUrl: string) {
	const result: { title?: string; thumbnail?: string; sources: MediaSource[] } = { sources: [] };
	try {
		const html = await fetchText(pageUrl);
		const titleMatch = html.match(/<title[^>]*>([^<]+)<\/title>/i);
		if (titleMatch) result.title = titleMatch[1].trim();
		const ogMatch = html.match(/<meta[^>]+property=["']og:image["'][^>]+content=["']([^"']+)["']/i)
			|| html.match(/<meta[^>]+name=["']twitter:image["'][^>]+content=["']([^"']+)["']/i);
		if (ogMatch) result.thumbnail = resolveUrl(pageUrl, ogMatch[1]);

		const videoSrcs: string[] = [];
		const videoTagRe = /<video\b[^>]*>([\s\S]*?)<\/video>/gi;
		let vTag;
		while ((vTag = videoTagRe.exec(html)) !== null) {
			const videoBlock = vTag[0];
			const srcMatch = videoBlock.match(/<video[^>]*\ssrc=["']([^"']+)["']/i);
			if (srcMatch) videoSrcs.push(resolveUrl(pageUrl, srcMatch[1]));
			const sourceRe = /<source[^>]*\ssrc=["']([^"']+)["'][^>]*>/gi;
			let s;
			while ((s = sourceRe.exec(videoBlock)) !== null) {
				videoSrcs.push(resolveUrl(pageUrl, s[1]));
			}
		}

		const m3u8Re = /(["'])(\/?[^"'>]+\.(m3u8)(?:\?[^"'>]*)?)\1/gi;
		let m;
		const foundM3u8 = new Set<string>();
		while ((m = m3u8Re.exec(html)) !== null) {
			foundM3u8.add(resolveUrl(pageUrl, m[2]));
		}
		const plainM3u8Re = /https?:\/\/[^\s"'<>]+\.m3u8[^\s"'<>]*/gi;
		while ((m = plainM3u8Re.exec(html)) !== null) {
			foundM3u8.add(m[0]);
		}

		for (const s of videoSrcs) {
			if (s.includes('.m3u8')) foundM3u8.add(s);
			else result.sources.push({ url: s, type: s.includes('.mp4') ? 'video/mp4' : undefined });
		}

		for (const m3u8 of Array.from(foundM3u8)) {
			const variants = await parseM3U8(m3u8);
			variants.forEach(v => { if (!v.thumbnail && result.thumbnail) v.thumbnail = result.thumbnail; });
			result.sources.push(...variants);
		}

		const jsSrcRe = /sources\s*[:=]\s*\[([^\]]+)\]/i;
		const jsMatch = html.match(jsSrcRe);
		if (jsMatch) {
			const block = jsMatch[1];
			const urlRe = /["'](https?:\/\/[^"']+\.(mp4|m3u8)[^"']*)["']/gi;
			let u;
			while ((u = urlRe.exec(block)) !== null) {
				const url = u[1];
				if (url.includes('.m3u8')) {
					const variants = await parseM3U8(url);
					result.sources.push(...variants);
				} else {
					result.sources.push({ url, type: 'video/mp4' });
				}
			}
		}

		const seen = new Set<string>();
		result.sources = result.sources.filter(s => {
			if (!s.url) return false;
			if (seen.has(s.url)) return false;
			seen.add(s.url);
			return true;
		});
		result.sources.forEach(s => { if (!s.thumbnail && result.thumbnail) s.thumbnail = result.thumbnail; });

	} catch (error) {
		console.error('❌ extractMediaFromUrl error:', error);
	}
	return result;
}
// -------------------------
// Fin des utilitaires
// -------------------------

const wss = new WebSocketServer({ port: PORT, host: HOST });
console.log(`🚀 Serveur Cast initialisé sur ws://${HOST}:${PORT}`);

wss.on('connection', (ws: WebSocket) => {
	ws.on('message', async (message: Buffer) => {
		try {
			const data = JSON.parse(message.toString());

			// NOUVEAU : Extraction média depuis une URL
			if (data.type === 'EXTRACT_MEDIA' && data.url) {
				console.log(`🔎 Extraction média pour ${data.url}`);
				const extracted = await extractMediaFromUrl(data.url);
				ws.send(JSON.stringify({ type: 'MEDIA_SOURCES', url: data.url, result: extracted }));
			}

			// NOUVEAU : L'extension demande la liste des TV
			else if (data.type === 'GET_DEVICES') {
				const deviceList = Array.from(discoveredDevices.values());
				ws.send(JSON.stringify({ type: 'DEVICE_LIST', devices: deviceList }));
			}
			
			// MODIFIÉ : On utilise le deviceId envoyé par l'extension
			else if (data.type === 'CAST_REQUEST') {
				const targetDevice = discoveredDevices.get(data.deviceId);
				
				if (targetDevice) {
					console.log(`➡️ Envoi vers : ${targetDevice.name}...`);
					try {
						await chromecastProvider.cast(data.media, targetDevice.ip);
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