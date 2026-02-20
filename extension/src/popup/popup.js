const volumeSlider = document.getElementById('volume-slider');
const btnSeek = document.getElementById('btn-seek');
const timeInput = document.getElementById('time-input');
// const btnCast = document.getElementById('btn-cast');
const btnPause = document.getElementById('btn-pause');
const btnResume = document.getElementById('btn-resume');
const btnStop = document.getElementById('btn-stop');
const statusDiv = document.getElementById('status');
const deviceSelect = document.getElementById('device-select');
const btnCheckCast = document.getElementById('btn-check-cast');
const castOptions = document.getElementById('cast-options');
const btnCastVideo = document.getElementById('btn-cast-video');
const btnCastPage = document.getElementById('btn-cast-page');

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
btnCheckCast.addEventListener('click', () => {
    const selectedDeviceId = deviceSelect.value;
    if (!selectedDeviceId) {
        statusDiv.innerText = "❌ Sélectionnez un appareil.";
        return;
    }

    statusDiv.innerText = "Analyse de la page...";
    btnCheckCast.style.display = 'none'; // On cache le bouton d'analyse

    // On demande au background s'il y a une vidéo
    sendCommand("CHECK_MEDIA", { deviceId: selectedDeviceId }, (response) => {
        if (response && response.hasVideo) {
            // Vidéo trouvée : On affiche le choix à l'utilisateur
            statusDiv.innerText = "Que voulez-vous caster ?";
            castOptions.style.display = 'block';

            btnCastVideo.onclick = () => {
                statusDiv.innerText = "Lancement de la vidéo...";
                sendCommand("START_CAST", { type: "VIDEO", deviceId: selectedDeviceId });
            };

            btnCastPage.onclick = () => {
                statusDiv.innerText = "Lancement de la page...";
                sendCommand("START_CAST", { type: "PAGE", url: response.pageUrl, deviceId: selectedDeviceId });
            };
        } else {
            // Pas de vidéo : On cast la page directement
            statusDiv.innerText = "Aucune vidéo. Casting de la page...";
            sendCommand("START_CAST", { type: "PAGE", url: response.pageUrl, deviceId: selectedDeviceId });
        }
    });
});

// Contrôle du volume
volumeSlider.addEventListener('input', (e) => {
    const vol = parseFloat(e.target.value);
    sendCommand("CONTROL", { command: "SET_VOLUME", level: vol });
});

// Contrôle du temps
btnSeek.addEventListener('click', () => {
    const time = parseFloat(timeInput.value);
    if (!isNaN(time)) {
        sendCommand("CONTROL", { command: "SEEK", time: time }, () => {
            statusDiv.innerText = `Déplacement à ${time}s...`;
        });
    }
});

btnPause.addEventListener('click', () => sendCommand("CONTROL", { command: "PAUSE" }));
btnResume.addEventListener('click', () => sendCommand("CONTROL", { command: "RESUME" }));
btnStop.addEventListener('click', () => sendCommand("CONTROL", { command: "STOP" }));
