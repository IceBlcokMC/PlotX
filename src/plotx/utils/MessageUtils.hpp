#pragma once
#include <string>
#include <unordered_map>

#include "fmt/format.h"

#include <mc/server/commands/CommandOutput.h>
#include <mc/world/actor/player/Player.h>

namespace plotx::message_utils {

// Template function sendText, usage: sendText() or sendText<LogLevel::Success>().
enum class LogLevel : int { Normal = -1, Debug = 0, Info = 1, Warn = 2, Error = 3, Fatal = 4, Success = 5 };
inline static std::unordered_map<LogLevel, std::string> Color = {
    {LogLevel::Normal,  "§b"},
    {LogLevel::Debug,   "§7"},
    {LogLevel::Info,    "§r"},
    {LogLevel::Warn,    "§e"},
    {LogLevel::Error,   "§c"},
    {LogLevel::Fatal,   "§4"},
    {LogLevel::Success, "§a"}
};

template <typename... Args>
[[nodiscard]] inline std::string format(const std::string& fmt, Args... args) {
    try {
        return fmt::vformat(fmt, fmt::make_format_args(args...));
    } catch (...) {
        return fmt;
    }
}

template <LogLevel type = LogLevel::Normal, typename... Args>
inline void sendText(Player& player, const std::string& fmt, Args&&... args) {
    player.sendMessage(format("[PlotX]" + Color[type] + fmt, args...));
}

template <LogLevel type = LogLevel::Normal, typename... Args>
inline void sendText(CommandOutput& output, const std::string& fmt, Args&&... args) {
    if constexpr (type == LogLevel::Error || type == LogLevel::Fatal) {
        output.error(format("[PlotX]" + Color[type] + fmt, args...));
    } else {
        output.success(format("[PlotX]" + Color[type] + fmt, args...));
    }
}

template <LogLevel type = LogLevel::Normal, typename... Args>
inline void sendText(Player* player, const std::string& fmt, Args&&... args) {
    if (player) {
        return sendText<type>(*player, fmt, args...);
    }
    throw std::runtime_error("Failed in sendText: player is nullptr");
}

} // namespace plotx::message_utils