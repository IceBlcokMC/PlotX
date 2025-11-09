declare module "@minecraft" {
    export const enum CommandFlagValue {
        // $name(): string;
        None = 0,
        UsageTest = 1 << 0,
        HiddenFromCommandBlockOrigin = 1 << 1,
        HiddenFromPlayerOrigin = 1 << 2,
        HiddenFromAutomationOrigin = 1 << 3,
        SyncLocal = 1 << 4,
        ExecuteDisallowed = 1 << 5,
        TypeMessage = 1 << 6,
        NotCheat = 1 << 7,
        Async = 1 << 8,
        NoEditor = 1 << 9,
        Hidden = HiddenFromPlayerOrigin | HiddenFromCommandBlockOrigin,
        Removed = Hidden | HiddenFromAutomationOrigin,
    }
}