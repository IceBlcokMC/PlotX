declare module "@levilamina" {

    export class Logger implements InstanceClassHelper<Logger> {
        $equals(other: Logger): boolean;

        log(level: LogLevel, ...args: any[]): void;

        fatal(...args: any[]): void;

        error(...args: any[]): void;

        warn(...args: any[]): void;

        info(...args: any[]): void;

        debug(...args: any[]): void;

        trace(...args: any[]): void;

        getTitle(): string;

        getLevel(): LogLevel;

        shouldLog(level: LogLevel): boolean;

        setLevel(level: LogLevel): void;

        setFlushLevel(level: LogLevel): void;

        flush(): void;
    }

    export const LogLevel: LogLevel;
    export type LogLevel = NativeEnum<[
        "Off",
        "Fatal",
        "Error",
        "Warn",
        "Info",
        "Debug",
        "Trace"
    ]>

}