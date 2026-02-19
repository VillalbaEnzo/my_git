import { Bonjour } from 'bonjour-service';
import { Client, DefaultMediaReceiver } from 'castv2-client';
import { ICastProvider, CastDevice, MediaPayload } from '../../core/interfaces';

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

    cast(media: MediaPayload, ip: string): Promise<void> {
        return new Promise((resolve, reject) => {
            // Si une session existe déjà, on la ferme proprement avant d'en lancer une nouvelle
            if (this.currentClient) this.currentClient.close();

            const client = new Client();
            this.currentClient = client;

            client.connect(ip, () => {
                console.log(`🔌 [${this.name}] Connecté à la TV.`);
                
                client.launch(DefaultMediaReceiver, (err: any, player: any) => {
                    if (err) return reject(err);
                    
                    this.currentPlayer = player; // On sauvegarde le lecteur !

                    const mediaInfo = {
                        contentId: media.url,
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
    async setVolume(level: number): Promise<void> {
    return new Promise((resolve, reject) => {
        if (!this.currentClient) return reject(new Error("Non connecté"));
        this.currentClient.setVolume({ level: level }, (err: any) => {
            if (err) return reject(err);
            resolve();
        });
    });
    }
    async seek(time: number): Promise<void> {
    return new Promise((resolve, reject) => {
        if (!this.currentPlayer) return reject(new Error("Aucun média"));
        this.currentPlayer.seek(time, (err: any) => {
            if (err) return reject(err);
            resolve();
        });
    });
    }
}
