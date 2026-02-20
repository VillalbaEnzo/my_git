export interface MediaPayload {
    url: string;
    title?: string;
    mimeType: string;
    proxyUrl?: string; 
    streamType?: 'BUFFERED' | 'LIVE'; // 👈 NOUVEAU
}

export interface CastDevice {
    id: string;
    name: string;
    ip: string;
    provider: string; // ex: 'chromecast', 'airplay'
}

// Le contrat que tout plugin de cast devra respecter
export interface ICastProvider {
    name: string;
    discoverDevices(onDeviceFound: (device: CastDevice) => void): void;
    // On ajoutera les méthodes cast(), pause(), stop() à l'étape suivante !
}

export interface ICastProvider {
    name: string;
    discoverDevices(onDeviceFound: (device: CastDevice) => void): void;
    // Nouvelle méthode obligatoire pour nos plugins :
    cast(media: MediaPayload, ip: string): Promise<void>;
}

export interface MediaPayload {
    url: string;
    title?: string;
    mimeType: string;
    proxyUrl?: string; // URL via proxy si nécessaire
}

export interface CastDevice {
    id: string;
    name: string;
    ip: string;
    provider: string;
}

export interface ICastProvider {
    name: string;
    discoverDevices(onDeviceFound: (device: CastDevice) => void): void;
    cast(media: MediaPayload, ip: string): Promise<void>;
    
    // NOUVEAU : Contrôles de lecture obligatoires
    pause(): Promise<void>;
    resume(): Promise<void>;
    stop(): Promise<void>;
}

export interface PlaybackStatus {
    currentTime: number;
    duration: number;
    volumeLevel: number; // de 0.0 à 1.0
    isMuted: boolean;
    playerState: 'PLAYING' | 'PAUSED' | 'IDLE' | 'BUFFERING';
}

export interface ICastProvider {
    name: string;
    discoverDevices(onDeviceFound: (device: CastDevice) => void): void;
    cast(media: MediaPayload, ip: string): Promise<void>;
    pause(): Promise<void>;
    resume(): Promise<void>;
    stop(): Promise<void>;
    
    // NOUVEAU : Son et Temps
    setVolume(level: number): Promise<void>; // Niveau entre 0.0 et 1.0
    seek(time: number): Promise<void>;       // Temps en secondes
    castPage(pageUrl: string, ip: string): Promise<void>;
    // NOUVEAU : Écouteur d'état (pour mettre à jour la barre de progression)
    onStatusChange(callback: (status: PlaybackStatus) => void): void;
}