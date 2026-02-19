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
                    if (data.action === 'PAUSE') await chromecastProvider.pause();
                    if (data.action === 'RESUME') await chromecastProvider.resume();
                    if (data.action === 'STOP') await chromecastProvider.stop();
                    ws.send(JSON.stringify({ type: 'CONTROL_SUCCESS', action: data.action }));
                } catch (error) {
                    console.error(`❌ Échec de l'action ${data.action}`);
                }
            }
        } catch (error) {
            console.error('❌ Erreur générale :', error);
        }
    });
});