import { CommandHandle, CommandParamKind, CommandRegistrar } from "@levilamina";
import { CommandOriginType, Player } from "@minecraft";
import { isMoreDimension } from "@plotx";
import { tr, trl } from "src/i18n/I18n";

const kTargetDimEnum = [
    ["overworld", 0],
    ["plotx", 1],
] as const;
const kTargetDimEnumKey = "plotx_sw_dim";

type TargetDim = (typeof kTargetDimEnum)[number][0];

export function registerSwitchDimSubCommand(registrar: CommandRegistrar, handle: CommandHandle) {
    if (!isMoreDimension) {
        ScriptMod.current()
            .getLogger()
            .debug(`SwitchDimSubCommand: build target are not more_dimensions, skip register`);
        return;
    }

    if (!registrar.hasEnum(kTargetDimEnumKey)) {
        registrar.tryRegisterRuntimeEnum(kTargetDimEnumKey, kTargetDimEnum as unknown as pair<string, number>[]);
    }

    handle
        .runtimeOverload()
        .text("switch_dim")
        .required("dim", CommandParamKind.Enum, kTargetDimEnumKey)
        .execute((origin, output, args) => {
            if (origin.getOriginType() !== CommandOriginType.Player) {
                output.error(tr("Only player can use this command"));
                return;
            }

            const player = origin.getEntity() as Player;
            switch (args.dim as TargetDim) {
                case "overworld": {
                    // TODO: teleport to overworld
                    break;
                }
                case "plotx": {
                    // TODO: teleport to plotx
                    break;
                }
                default:
                    output.error(trl("Unknown dimension: {}", player.getLocaleCode(), args.dim));
            }
        });
}
