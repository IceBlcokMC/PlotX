declare module "@minecraft" {
    export const enum CommandParameterOption {
        // $name(): string;
        None = 0,
        EnumAutocompleteExpansion = 1 << 0,
        HasSemanticConstraint = 1 << 1,
        EnumAsChainedCommand = 1 << 2,
    }
}