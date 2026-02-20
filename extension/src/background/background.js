console.log("🛠️ Background script chargé.");

let socket = null;
let reconnectDelay = 2000;

// === LE NOUVEAU SCRAPPER ROBUSTE (INTERCEPTION RÉSEAU) ===
const detectedMedia = {};

chrome.webRequest.onHeadersReceived.addListener(
    (details) => {
        const url = details.url;
        const tabId = details.tabId;
        if (tabId === -1) return;

        // Filtrer les requêtes non-pertinentes
        if (url.includes('tracking') || url.includes('analytics') || url.includes('ads')) return;

        // Détection des flux vidéo HLS
        if (url.includes('.m3u8')) {
            // Ignorer les variantes et les sous-segments
            if (url.includes('variant') || url.includes('segment') || url.includes('frag') || url.match(/\d+\.ts$/)) return;

            console.log(`📡 Flux HLS intercepté (Onglet ${tabId}):`, url);
            detectedMedia[tabId] = { url: url, mimeType: 'application/x-mpegurl', title: "Vidéo Web (HLS)" };
        }
        // Détection des flux vidéo MP4 et autres formats
        else if (url.match(/\.(mp4|webm|mkv|flv|mov)(\?|$)/i)) {
            // Ignorer les sous-segments
            if (url.includes('segment') || url.includes('frag')) return;

            const mimeType = url.includes('.webm') ? 'video/webm' :
                            url.includes('.mkv') ? 'video/x-matroska' :
                            url.includes('.mov') ? 'video/quicktime' : 'video/mp4';

            console.log(`📡 Flux vidéo intercepté (Onglet ${tabId}):`, url);
            detectedMedia[tabId] = { url: url, mimeType: mimeType, title: "Vidéo Web" };
        }
        // Détection des manifestes DASH (MPD)
        else if (url.includes('.mpd')) {
            console.log(`📡 Flux DASH intercepté (Onglet ${tabId}):`, url);
            detectedMedia[tabId] = { url: url, mimeType: 'application/dash+xml', title: "Vidéo Web (DASH)" };
        }
    },
    { urls: ["<all_urls>"] },
    ["responseHeaders"]
);
// ========================================================

function connectWebSocket() {
    if (socket && (socket.readyState === WebSocket.OPEN || socket.readyState === WebSocket.CONNECTING)) return;
    socket = new WebSocket("ws://127.0.0.1:8080");
    socket.onopen = () => { console.log("✅ Connecté au serveur Node.js !"); reconnectDelay = 2000; };
    socket.onclose = () => { socket = null; setTimeout(connectWebSocket, reconnectDelay); reconnectDelay = Math.min(reconnectDelay * 1.5, 10000); };
    socket.onerror = () => {};
}

connectWebSocket();

chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    connectWebSocket();

    if (request.action === "GET_DEVICES") {
        const onMessage = (event) => {
            const data = JSON.parse(event.data);
            if (data.type === 'DEVICE_LIST') {
                socket.removeEventListener('message', onMessage);
                sendResponse({ devices: data.devices });
            }
        };
        socket.addEventListener('message', onMessage);
        if (socket.readyState === WebSocket.OPEN) socket.send(JSON.stringify({ type: "GET_DEVICES" }));
        else setTimeout(() => socket.send(JSON.stringify({ type: "GET_DEVICES" })), 500);
        return true;
    }

    else if (request.action === "START_CAST") {
        chrome.tabs.query({ active: true, currentWindow: true }, async (tabs) => {
            const tabId = tabs[0].id;
            const tab = tabs[0];

            // Récupérer les cookies du domaine actuel
            let cookies = {};
            try {
                const allCookies = await chrome.cookies.getAll({ url: tab.url });
                allCookies.forEach(cookie => {
                    cookies[cookie.name] = cookie.value;
                });
            } catch (err) {
                console.warn("⚠️ Erreur lors de la récupération des cookies:", err);
            }

            // Récupérer les headers intéressants du navigateur
            let headers = {
                'User-Agent': navigator.userAgent,
                'Accept': 'application/vnd.apple.mpegurl, application/x-mpegurl, application/json, */*',
                'Accept-Language': navigator.language,
                'Accept-Encoding': 'gzip, deflate, br',
                'Referer': tab.url,
                'Origin': new URL(tab.url).origin,
            };

            // Extraire les tokens d'authentification du localStorage/sessionStorage
            try {
                const authTokens = await chrome.scripting.executeScript({
                    target: { tabId: tabId },
                    func: () => {
                        const tokens: any = {};
                        // Chercher les tokens dans localStorage
                        for (let i = 0; i < localStorage.length; i++) {
                            const key = localStorage.key(i);
                            if (key && (key.toLowerCase().includes('token') || key.toLowerCase().includes('auth') || key.toLowerCase().includes('jwt'))) {
                                const value = localStorage.getItem(key);
                                if (value) {
                                    tokens[key] = value;
                                    console.log(`🔑 Token trouvé en localStorage: ${key}`);
                                }
                            }
                        }
                        // Chercher dans sessionStorage
                        for (let i = 0; i < sessionStorage.length; i++) {
                            const key = sessionStorage.key(i);
                            if (key && (key.toLowerCase().includes('token') || key.toLowerCase().includes('auth') || key.toLowerCase().includes('jwt'))) {
                                const value = sessionStorage.getItem(key);
                                if (value) {
                                    tokens[key] = value;
                                    console.log(`🔑 Token trouvé en sessionStorage: ${key}`);
                                }
                            }
                        }
                        return tokens;
                    }
                });

                const tokenData = authTokens[0]?.result || {};
                // Ajouter les tokens comme headers Authorization si pertinent
                Object.entries(tokenData).forEach(([key, value]: [string, any]) => {
                    if (key.toLowerCase().includes('bearer') || key.toLowerCase().includes('jwt')) {
                        headers['Authorization'] = `Bearer ${value}`;
                    } else if (value && typeof value === 'string' && value.length > 20) {
                        headers['Authorization'] = value;
                    }
                });
            } catch (err) {
                console.warn("⚠️ Erreur lors de l'extraction des tokens:", err);
            }

            // 1. Priorité au scrapping réseau
            if (detectedMedia[tabId]) {
                const videoData = { ...detectedMedia[tabId], cookies, headers };
                socket.send(JSON.stringify({ type: "CAST_REQUEST", deviceId: request.deviceId, media: videoData }));
                sendResponse({ success: true, media: videoData });
                return;
            }

            // 2. Fallback sur l'ancien scrapping HTML
            try {
                const results = await chrome.scripting.executeScript({ target: { tabId: tabId }, func: extractVideoUrl });
                const videoData = results[0]?.result;
                if (videoData && videoData.url) {
                    videoData.cookies = cookies;
                    videoData.headers = headers;
                    socket.send(JSON.stringify({ type: "CAST_REQUEST", deviceId: request.deviceId, media: videoData }));
                    sendResponse({ success: true, media: videoData });
                } else sendResponse({ success: false, error: "Aucun flux vidéo détecté." });
            } catch (err) { sendResponse({ success: false, error: "Erreur d'analyse." }); }
        });
        return true;
    } 
    
    // NOUVEAU : Transmission des paramètres (volume, temps) au serveur
    else if (request.action === "CONTROL") {
        socket.send(JSON.stringify({ 
            type: "CONTROL_REQUEST", 
            action: request.command,
            level: request.level,
            time: request.time 
        }));
        sendResponse({ success: true });
        return true;
    }
});

function extractVideoUrl() {
    const video = document.querySelector('video');
    if (!video) return null;

    // 1. Chercher d'abord dans les éléments <source>
    const sources = video.querySelectorAll('source');
    for (const source of sources) {
        const url = source.src;
        if (url && url.startsWith('http')) {
            let mimeType = source.type;
            if (!mimeType) {
                if (url.includes('.m3u8')) mimeType = 'application/x-mpegurl';
                else if (url.includes('.mpd')) mimeType = 'application/dash+xml';
                else if (url.includes('.webm')) mimeType = 'video/webm';
                else mimeType = 'video/mp4';
            }
            console.log(`📹 Source trouvée (HTML)`, url);
            return { url, title: document.title, mimeType };
        }
    }

    // 2. Fallback sur l'attribut src du <video>
    const videoUrl = video.src;
    if (videoUrl && videoUrl.startsWith('http')) {
        const mimeType = videoUrl.includes('.m3u8') ? 'application/x-mpegurl' : 'video/mp4';
        return { url: videoUrl, title: document.title, mimeType };
    }

    // 3. Si le src est un blob, chercher dans les attributs data ou autres éléments
    if (videoUrl && videoUrl.startsWith('blob:')) {
        console.log(`🔍 Blob URL détecté, recherche des sources alternatives...`);
        // Chercher les sources qui pourraient être masquées
        const allSources = Array.from(document.querySelectorAll('video source, source[type*="video"], source[type*="playlist"]'));
        for (const source of allSources) {
            const url = source.src;
            if (url && url.startsWith('http')) {
                let mimeType = source.type;
                if (!mimeType) {
                    if (url.includes('.m3u8')) mimeType = 'application/x-mpegurl';
                    else if (url.includes('.mpd')) mimeType = 'application/dash+xml';
                    else if (url.includes('.webm')) mimeType = 'video/webm';
                    else mimeType = 'video/mp4';
                }
                console.log(`📹 Source alternative trouvée (fallback blob)`, url);
                return { url, title: document.title, mimeType };
            }
        }
    }

    return null;
}