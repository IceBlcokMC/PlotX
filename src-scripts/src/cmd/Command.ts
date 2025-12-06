import { CommandRegistrar } from "@levilamina";

import registerAdminSubcommand from "./subCommand/AdminSubCommand.js";
import { registerSwitchDimSubCommand } from "./subCommand/SwitchDimSubCommand.js";
import { registerCurrentPlotSubCommand } from "./subCommand/CurrentPlotSubCommand.js";

export function registerCommand() {
    const registrar = CommandRegistrar.getInstance();
    const cmd = registrar.getOrCreateCommand("plotx");

    registerAdminSubcommand(registrar, cmd);
    registerSwitchDimSubCommand(registrar, cmd);
    registerCurrentPlotSubCommand(registrar, cmd);
}
