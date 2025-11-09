declare module "@minecraft" {

    export type CommandPermissionLevel = NativeEnum<{
        Any: 0,
        GameDirectors: 1,
        Admin: 2,
        Host: 3,
        Owner: 4,
        Internal: 5,
    }>;
    export const CommandPermissionLevel: CommandPermissionLevel;

}