declare module "@levilamina" {

    export class Logger implements InstanceClassHelper<Logger> {
        $equals(other: Logger): boolean;

        log(level: EnumValue<LogLevel>, ...args: any[]): void;

        fatal(...args: any[]): void;

        error(...args: any[]): void;

        warn(...args: any[]): void;

        info(...args: any[]): void;

        debug(...args: any[]): void;

        trace(...args: any[]): void;

        getTitle(): string;

        getLevel(): EnumValue<LogLevel>;

        shouldLog(level: EnumValue<LogLevel>): boolean;

        setLevel(level: EnumValue<LogLevel>): void;

        setFlushLevel(level: EnumValue<LogLevel>): void;

        flush(): void;
    }

    export const LogLevel: LogLevel;
    export type LogLevel = NativeEnum<{
        Off: -1,
        Fatal: 0,
        Error: 1,
        Warn: 2,
        Info: 3,
        Debug: 4,
        Trace: 5,
    }>

}