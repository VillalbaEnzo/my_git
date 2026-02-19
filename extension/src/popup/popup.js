const btnCast = document.getElementById('btn-cast');
const btnPause = document.getElementById('btn-pause');
const btnResume = document.getElementById('btn-resume');
const btnStop = document.getElementById('btn-stop');
const statusDiv = document.getElementById('status');
const deviceSelect = document.getElementById('device-select');

// Fonction utilitaire pour parler au background.js
function sendCommand(action, payload = {}, callback = null) {
    chrome.runtime.sendMessage({ action, ...payload }, (response) => {
        if (chrome.runtime.lastError) {
            statusDiv.innerText = "⚠️ Erreur serveur local.";
            return;
        }
        if (callback) callback(response);
    });
}

// 1. Au chargement du popup, on demande les appareils disponibles
sendCommand("GET_DEVICES", {}, (response) => {
    if (response && response.devices && response.devices.length > 0) {
        deviceSelect.innerHTML = ''; // On vide la liste
        response.devices.forEach(device => {
            const option = document.createElement('option');
            option.value = device.id;
            // Affiche "Nom de la TV (chromecast)"
            option.innerText = `${device.name} (${device.provider})`;
            deviceSelect.appendChild(option);
        });
    } else {
        deviceSelect.innerHTML = '<option value="">Aucun appareil trouvé</option>';
    }
});

// 2. Lancement du cast avec l'appareil sélectionné
btnCast.addEventListener('click', () => {
    const selectedDeviceId = deviceSelect.value;
    if (!selectedDeviceId) {
        statusDiv.innerText = "❌ Sélectionnez un appareil.";
        return;
    }

    statusDiv.innerText = "Recherche de vidéo...";
    sendCommand("START_CAST", { deviceId: selectedDeviceId }, (response) => {
        if (response && response.success) {
            statusDiv.innerText = "Lecture de : " + response.media.title;
        } else {
            statusDiv.innerText = "❌ " + (response ? response.error : "Erreur");
        }
    });
});

btnPause.addEventListener('click', () => sendCommand("CONTROL", { command: "PAUSE" }));
btnResume.addEventListener('click', () => sendCommand("CONTROL", { command: "RESUME" }));
btnStop.addEventListener('click', () => sendCommand("CONTROL", { command: "STOP" }));