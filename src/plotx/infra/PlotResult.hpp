#pragma once
#include "ll/api/Expected.h"

#include <filesystem>
#include <optional>
#include <source_location>
#include <string>

namespace plotx {

struct PlotError : ll::ErrorInfoBase {
    std::string                         userMessage_;
    std::string                         systemMessage_;
    std::optional<std::source_location> sourceLocation_;

    PlotError(std::string userMsg, std::string sysMsg, std::optional<std::source_location> sloc)
    : userMessage_(std::move(userMsg)),
      systemMessage_(std::move(sysMsg)),
      sourceLocation_(sloc) {}

    std::string message() const noexcept override { return userMessage_; }

    [[nodiscard]] inline bool hasSourceLocation() const noexcept { return sourceLocation_.has_value(); }
    [[nodiscard]] inline bool hasSystemMessage() const noexcept { return !systemMessage_.empty(); }

    [[nodiscard]] inline std::string getLogMessage() const noexcept {
        if (!hasSystemMessage()) {
            return userMessage_;
        }
        if (!hasSourceLocation()) {
            return systemMessage_;
        }

        try {
            std::filesystem::path p{sourceLocation_->file_name()};

            return fmt::format(
                "{} \n\t-> at {} ({}:{})",
                systemMessage_,
                sourceLocation_->function_name(),
                p.filename().string(),
                sourceLocation_->line()
            );
        } catch (...) {
            return systemMessage_ + " (Format Error)";
        }
    }

    inline void log(ll::io::Logger& logger) {
        if (hasSystemMessage()) {
            logger.error(getLogMessage());
        }
    }
};

[[nodiscard]] inline ll::Unexpected makeUserError(std::string userMsg) noexcept {
    return ll::makeError<PlotError>(std::move(userMsg), "", std::nullopt);
}

[[nodiscard]] inline ll::Unexpected makeSystemError(
    std::string          userMsg,
    std::string          sysMsg,
    std::source_location loc = std::source_location::current()
) noexcept {
    return ll::makeError<PlotError>(std::move(userMsg), std::move(sysMsg), loc);
}

} // namespace plotx