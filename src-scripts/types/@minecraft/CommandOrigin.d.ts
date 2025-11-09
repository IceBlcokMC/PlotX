declare module "@minecraft" {

    export const CommandOriginType: CommandOriginType;
    export type CommandOriginType = NativeEnum<{
        Player: 0,
        CommandBlock: 1,
        MinecartCommandBlock: 2,
        DevConsole: 3,
        Test: 4,
        AutomationPlayer: 5,
        ClientAutomation: 6,
        DedicatedServer: 7,
        Entity: 8,
        Virtual: 9,
        GameArgument: 10
        EntityServer: 11
        Precompiled: 12
        GameDirectorEntityServer: 13
        Scripting: 14
        ExecuteContext: 15
    }>;

    export class CommandOrigin implements InstanceClassHelper<CommandOrigin> {
        $equals(other: CommandOrigin): boolean;

        getEntity(): Actor;

        getOriginType(): EnumValue<CommandOriginType>;
    }

}