import { Bonjour } from 'bonjour-service';
import { Client, DefaultMediaReceiver } from 'castv2-client';
import { ICastProvider, CastDevice, MediaPayload, PlaybackStatus } from '../../core/interfaces';

export class ChromecastProvider implements ICastProvider {
    name = 'chromecast';
    private bonjour = new Bonjour();
    
    // NOUVEAU : variables pour garder la session active en mémoire
    private currentClient: any = null;
    private currentPlayer: any = null;

    discoverDevices(onDeviceFound: (device: CastDevice) => void): void {
        console.log(`🔍 [${this.name}] Lancement du scan mDNS (_googlecast._tcp)...`);
        
        // On crée un "navigateur" mDNS qui va écouter en continu
        const browser = this.bonjour.find({ type: 'googlecast' });

        // Événement déclenché à chaque fois qu'un appareil diffuse sa présence
        browser.on('up', (service) => {
            console.log(`📡 Service mDNS brut détecté : ${service.name}`);
            
            const ipv4 = service.addresses?.find((ip: string) => ip.includes('.')) || '';
            if (ipv4) {
                const device: CastDevice = {
                    id: service.txt?.id || service.host,
                    name: service.name,
                    ip: ipv4,
                    provider: this.name
                };
                console.log(`📺 [${this.name}] Appareil validé : ${device.name} (${device.ip})`);
                onDeviceFound(device);
            }
        });

        // Événement déclenché si la TV se déconnecte ou s'éteint
        browser.on('down', (service) => {
            console.log(`🔻 Appareil perdu/éteint : ${service.name}`);
        });

        // Relance un scan actif sur le réseau local
        browser.start(); 
    }
    castPage(pageUrl: string, ip: string): Promise<void> {
        return new Promise((resolve, reject) => {
            if (this.currentClient) this.currentClient.close();
            const client = new Client();
            this.currentClient = client;

            client.connect(ip, () => {
                console.log(`🔌 [${this.name}] Connecté pour caster une page web.`);
                
                // ⚠️ IMPORTANT : Tu dois créer une application "Custom Receiver"
                // sur la Google Cast Developer Console (ça coûte 5$) pour obtenir un App ID valide.
                // Le DefaultMediaReceiver plantera si tu lui envoies du HTML.
                const CUSTOM_APP_ID = 'TON_APP_ID_CUSTOM'; 

                client.launch(CUSTOM_APP_ID, (err: any, player: any) => {
                    if (err) return reject(err);
                    this.currentPlayer = player;

                    // Envoi d'un message spécifique à ton application Web TV pour charger l'iframe
                    player.send({ type: 'LOAD_PAGE', url: pageUrl });
                    console.log(`🌐 [${this.name}] Commande d'affichage de la page web envoyée !`);
                    resolve();
                });
            });

            client.on('error', (err: any) => {
                console.error(`❌ [${this.name}] Erreur de connexion:`, err.message);
                if (this.currentClient) this.currentClient.close();
            });
        });
    }
    cast(media: MediaPayload, ip: string): Promise<void> {
        return new Promise((resolve, reject) => {
            // Si une session existe déjà, on la ferme proprement avant d'en lancer une nouvelle
            if (this.currentClient) this.currentClient.close();

            const client = new Client();
            this.currentClient = client;

            // Construire l'URL du proxy local
            // Si une URL proxy est fournie, l'utiliser. Sinon, construire une URL proxy
            let contentId = media.url;

            if (media.proxyUrl) {
                // Utiliser l'URL proxy fournie par le serveur principal
                contentId = media.proxyUrl;
                console.log(`📡 Utilisation de l'URL proxy fournie`);
            } else if (media.url.startsWith('http://') || media.url.startsWith('https://')) {
                // Fallback: construire une URL proxy locale (127.0.0.1)
                contentId = `http://127.0.0.1:8081/${encodeURIComponent(media.url)}`;
                console.log(`📡 Construction d'une URL proxy locale`);
            }

            client.connect(ip, () => {
                console.log(`🔌 [${this.name}] Connecté à la TV.`);

                client.launch(DefaultMediaReceiver, (err: any, player: any) => {
                    if (err) return reject(err);

                    this.currentPlayer = player; // On sauvegarde le lecteur !

                    const mediaInfo = {
                        contentId: contentId,
                        contentType: media.mimeType,
                        streamType: 'BUFFERED',
                        metadata: { type: 0, metadataType: 0, title: media.title || 'Vidéo Web', images: [] }
                    };

                    player.load(mediaInfo, { autoplay: true }, (err: any, status: any) => {
                        if (err) return reject(err);
                        console.log(`▶️ [${this.name}] Lecture démarrée !`);
                        resolve();
                    });
                });
            });

            client.on('error', (err: any) => {
                console.error(`❌ [${this.name}] Erreur de connexion:`, err.message);
                if (this.currentClient) this.currentClient.close();
            });
        });
    }

    // NOUVEAU : Implémentation des contrôles
    pause(): Promise<void> {
        return new Promise((resolve, reject) => {
            if (!this.currentPlayer) return reject(new Error("Aucun média en cours de lecture."));
            this.currentPlayer.pause((err: any) => {
                if (err) return reject(err);
                console.log(`⏸️ [${this.name}] Vidéo en pause.`);
                resolve();
            });
        });
    }

    resume(): Promise<void> {
        return new Promise((resolve, reject) => {
            if (!this.currentPlayer) return reject(new Error("Aucun média en cours de lecture."));
            this.currentPlayer.play((err: any) => {
                if (err) return reject(err);
                console.log(`▶️ [${this.name}] Reprise de la vidéo.`);
                resolve();
            });
        });
    }

    stop(): Promise<void> {
        return new Promise((resolve, reject) => {
            if (!this.currentClient) return resolve(); // Déjà arrêté
            this.currentClient.stop(this.currentPlayer, (err: any) => {
                console.log(`⏹️ [${this.name}] Vidéo arrêtée, déconnexion.`);
                this.currentClient.close();
                this.currentClient = null;
                this.currentPlayer = null;
                resolve();
            });
        });
    }
private statusCallback: ((status: PlaybackStatus) => void) | null = null;

    onStatusChange(callback: (status: PlaybackStatus) => void): void {
        this.statusCallback = callback;
    }

    setVolume(level: number): Promise<void> {
        return new Promise((resolve, reject) => {
            if (!this.currentClient) return reject(new Error("Non connecté"));
            this.currentClient.setVolume({ level: level }, (err: any) => {
                if (err) return reject(err);
                console.log(`🔊 [${this.name}] Volume mis à ${level}`);
                resolve();
            });
        });
    }

    seek(time: number): Promise<void> {
        return new Promise((resolve, reject) => {
            if (!this.currentPlayer) return reject(new Error("Aucun média en cours de lecture."));
            this.currentPlayer.seek(time, (err: any) => {
                if (err) return reject(err);
                console.log(`⏱️ [${this.name}] Déplacement à ${time}s`);
                resolve();
            });
        });
    }
}
