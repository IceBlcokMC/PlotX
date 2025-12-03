import { CommandHandle, CommandParamKind, CommandRegistrar, PlayerInfo } from "@levilamina";
import { CommandOriginType, UUID } from "@minecraft";

import { ArgType } from "../../utils/TypeUtils";
import { tr } from "../../i18n/I18n.js";
import { PlotRegistry } from "@plotx";

const kPlotXAdminEnumKey = "PlotXAdminActions";
const kPlotXAdminEnumValues = [
    ["add", 0],
    ["remove", 1],
] as const;

type AdminActionEnumNameType = (typeof kPlotXAdminEnumValues)[number][0];

function handleAction(type: AdminActionEnumNameType, target: UUID) {
    const registry = PlotRegistry.getInstance();
    if (!registry) {
        throw new Error("Plot registry is not initialized");
    }
    const logger = ScriptMod.current().getLogger();
    switch (type) {
        case "add": {
            if (registry.isAdmin(target)) {
                logger.error(tr("The player {} is already an admin", PlayerInfo.fromUuid(target)?.name ?? "<unknown>"));
                return;
            }
            registry.addAdmin(target);
            logger.info(tr("The player {} is now an admin", PlayerInfo.fromUuid(target)?.name ?? "<unknown>"));
            break;
        }
        case "remove": {
            if (!registry.isAdmin(target)) {
                logger.error(tr("The player {} is not an admin", PlayerInfo.fromUuid(target)?.name ?? "<unknown>"));
                return;
            }
            registry.removeAdmin(target);
            logger.info(tr("The player {} is no longer an admin", PlayerInfo.fromUuid(target)?.name ?? "<unknown>"));
            break;
        }
        default:
            throw new Error(`Unknown action ${type}`);
    }
}

export default function registerAdminSubcommand(registrar: CommandRegistrar, cmd: CommandHandle) {
    if (!registrar.hasEnum(kPlotXAdminEnumKey)) {
        type RuntimeEnumType = ArgType<typeof CommandRegistrar.prototype.tryRegisterRuntimeEnum, 1>;
        registrar.tryRegisterRuntimeEnum(kPlotXAdminEnumKey, kPlotXAdminEnumValues as unknown as RuntimeEnumType);
    }

    // plotx admin <add|remove> <realName: string>
    cmd.runtimeOverload()
        .text("admin")
        .required("action", CommandParamKind.Enum, kPlotXAdminEnumKey)
        .required("realName", CommandParamKind.String)
        .execute((origin, output, args) => {
            if (origin.getOriginType() != CommandOriginType.DedicatedServer) {
                output.error(tr("Only server can execute this command"));
                return;
            }
            const { realName, action } = args;
            if (!realName) {
                output.error(tr("No real name specified"));
                return;
            }
            const entry = PlayerInfo.fromName(realName);
            if (entry === null) {
                output.error(tr("The player {} does not exists", realName));
                return;
            }
            handleAction(action as AdminActionEnumNameType, entry.uuid);
        });

    // plotx admins <add|remove> <players: target>
    cmd.runtimeOverload()
        .text("admins")
        .required("action", CommandParamKind.Enum, kPlotXAdminEnumKey)
        .required("players", CommandParamKind.Player)
        .execute((origin, output, args) => {
            if (origin.getOriginType() !== CommandOriginType.DedicatedServer) {
                output.error(tr("Only server can execute this command"));
                return;
            }
            const { players, action } = args;
            switch (players.length) {
                case 0:
                    output.error(tr("No players specified"));
                    return;
                case 1:
                    handleAction(action as AdminActionEnumNameType, players[0].uuid);
                    break;
                default:
                    output.error(tr("Only one player can be specified"));
            }
        });
}
