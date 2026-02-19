console.log("🛠️ Background script chargé.");
const detectedMedia = {};
let socket = null;
let reconnectDelay = 2000;

function connectWebSocket() {
    // Si on est déjà connecté ou en cours de connexion, on ne fait rien
    if (socket && (socket.readyState === WebSocket.OPEN || socket.readyState === WebSocket.CONNECTING)) {
        return;
    }

    socket = new WebSocket("ws://127.0.0.1:8080");

    socket.onopen = () => {
        console.log("✅ Connecté au serveur Node.js !");
        reconnectDelay = 2000; // Réinitialise le délai après un succès
    };

    socket.onclose = () => {
        console.log(`❌ Déconnecté. Nouvelle tentative dans ${reconnectDelay / 1000}s...`);
        socket = null;
        setTimeout(connectWebSocket, reconnectDelay);
        // Augmente le délai pour ne pas spammer le CPU (max 10 secondes)
        reconnectDelay = Math.min(reconnectDelay * 1.5, 10000); 
    };

    socket.onerror = (err) => {
        console.error("⚠️ Erreur WebSocket.");
        // L'événement onclose sera appelé juste après, gérant la reconnexion
    };
}

// On lance la première tentative
connectWebSocket();

// Écoute les requêtes venant de popup.js
chrome.runtime.onMessage.addListener((request, sender, sendResponse) => {
    connectWebSocket();

    if (request.action === "GET_DEVICES") {
        // On écoute temporairement le prochain message DEVICE_LIST
        const onMessage = (event) => {
            const data = JSON.parse(event.data);
            if (data.type === 'DEVICE_LIST') {
                socket.removeEventListener('message', onMessage);
                sendResponse({ devices: data.devices });
            }
        };
        socket.addEventListener('message', onMessage);
        
        // On demande la liste au serveur
        if (socket.readyState === WebSocket.OPEN) {
            socket.send(JSON.stringify({ type: "GET_DEVICES" }));
        } else {
            // Si le socket vient de s'ouvrir, on attend 1/2 seconde
            setTimeout(() => socket.send(JSON.stringify({ type: "GET_DEVICES" })), 500);
        }
        return true; // Asynchrone
    }

    else if (request.action === "START_CAST") {
        chrome.tabs.query({ active: true, currentWindow: true }, async (tabs) => {
            const tabId = tabs[0].id;
            
            // PRIORITÉ 1 : Est-ce qu'on a intercepté un flux réseau (.m3u8 ou .mp4) ?
            if (detectedMedia[tabId]) {
                const videoData = detectedMedia[tabId];
                console.log("🎥 Utilisation du flux réseau intercepté :", videoData);
                socket.send(JSON.stringify({ type: "CAST_REQUEST", deviceId: request.deviceId, media: videoData }));
                sendResponse({ success: true, media: videoData });
                return;
            }

            // PRIORITÉ 2 : Sinon, on fouille le DOM (l'ancienne méthode)
            try {
                const results = await chrome.scripting.executeScript({ target: { tabId: tabId }, func: extractVideoUrl });
                const videoData = results[0]?.result;
                
                if (videoData && videoData.url) {
                    socket.send(JSON.stringify({ type: "CAST_REQUEST", deviceId: request.deviceId, media: videoData }));
                    sendResponse({ success: true, media: videoData });
                } else {
                    sendResponse({ success: false, error: "Aucune vidéo HTML5 trouvée." });
                }
            } catch (err) {
                sendResponse({ success: false, error: "Erreur d'analyse." });
            }
        });
        return true;
    }    
    else if (request.action === "CONTROL") {
        socket.send(JSON.stringify({ type: "CONTROL_REQUEST", action: request.command }));
        sendResponse({ success: true });
        return true;
    }
});

function extractVideoUrl() {
    const videoElement = document.querySelector('video');
    if (!videoElement) return null;
    let url = videoElement.src;
    if (!url || url === "") {
        const sourceElement = videoElement.querySelector('source');
        if (sourceElement) url = sourceElement.src;
    }
    if (url && url.startsWith('http')) {
        return { url: url, title: document.title, mimeType: "video/mp4" };
    }
    return null;
}

chrome.webRequest.onHeadersReceived.addListener(
    (details) => {
        const url = details.url;
        const tabId = details.tabId;
        
        if (tabId === -1) return; // Ignore les requêtes hors onglet (comme celles du background script)

        // On cherche les flux HLS (.m3u8) ou les MP4 directs
        if (url.includes('.m3u8') || url.includes('.mp4')) {
            
            // On ignore les petits segments vidéo (pour ne garder que la playlist maître)
            if (url.includes('segment') || url.includes('frag') || url.includes('ts')) return;

            let mimeType = url.includes('.m3u8') ? 'application/x-mpegurl' : 'video/mp4';
            
            console.log(`📡 Flux média intercepté dans l'onglet ${tabId}:`, url);
            
            detectedMedia[tabId] = {
                url: url,
                mimeType: mimeType,
                title: "Vidéo Web Automatique"
            };
        }
    },
    { urls: ["<all_urls>"] },
    ["responseHeaders"]
);