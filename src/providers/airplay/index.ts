import { Bonjour } from 'bonjour-service';
import { ICastProvider, CastDevice, MediaPayload } from '../../core/interfaces';

export class AirPlayProvider implements ICastProvider {
    name = 'airplay';
    private bonjour = new Bonjour();

    discoverDevices(onDeviceFound: (device: CastDevice) => void): void {
        console.log(`🔍 [${this.name}] Recherche d'Apple TV...`);
        
        // AirPlay utilise le protocole mDNS sous le nom "_airplay._tcp"
        this.bonjour.find({ type: 'airplay' }, (service) => {
            const ipv4 = service.addresses?.find(ip => ip.includes('.')) || '';
            if (ipv4) {
                onDeviceFound({
                    id: service.txt?.deviceid || service.host,
                    name: service.name,
                    ip: ipv4,
                    provider: this.name
                });
            }
        });
    }

    async cast(media: MediaPayload, ip: string): Promise<void> {
        console.log(`[${this.name}] 🚧 Implémentation du cast vidéo vers ${ip} (URL: ${media.url})`);
        // Ici viendra la librairie AirPlay plus tard (ex: 'airplay-protocol')
    }

    async pause(): Promise<void> { console.log(`[${this.name}] 🚧 Pause`); }
    async resume(): Promise<void> { console.log(`[${this.name}] 🚧 Reprise`); }
    async stop(): Promise<void> { console.log(`[${this.name}] 🚧 Stop`); }
}