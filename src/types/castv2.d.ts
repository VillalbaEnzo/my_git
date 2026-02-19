declare module 'castv2-client' {
    export class Client {
        connect(ip: string, callback: () => void): void;
        launch(receiver: any, callback: (err: Error | null, player: any) => void): void;
        close(): void;
        on(event: string, callback: (err: Error) => void): void;
    }
    export const DefaultMediaReceiver: any;
}