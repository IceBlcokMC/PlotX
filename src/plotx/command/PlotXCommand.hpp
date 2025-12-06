#pragma once

class CommandOutput;
class CommandOrigin;

namespace plotx {

struct PlotXCommand {
    PlotXCommand() = delete;

    static void setup();

    static bool ensureConsoleExecute(CommandOrigin const& origin, CommandOutput& output);
    static bool ensurePlayerExecute(CommandOrigin const& origin, CommandOutput& output);
};

} // namespace plotx
