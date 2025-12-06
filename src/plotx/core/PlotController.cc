#include "PlotController.hpp"

#include "PlotRegistry.hpp"
#include "plotx/PlotX.hpp"
#include "plotx/math/PlotCoord.hpp"
#include "plotx/utils/MessageUtils.hpp"

#include "ll/api/i18n/I18n.h"
#include "plotx/gui/PlotManagerGui.hpp"

namespace plotx {

struct PlotController::Impl {
    PlotRegistry& registry;
    PlotX&        mod;
};

using ll::i18n_literals::operator""_tr;
using ll::i18n_literals::operator""_trl;

PlotController::PlotController(PlotRegistry& registry, PlotX& mod) : impl(std::make_unique<Impl>(registry, mod)) {}
PlotController::~PlotController() {}

void PlotController::teleportUnownedPlot(Player& player) const {
    if (auto coord = impl->registry.findUnownedPlot()) {
        // TODO: impl
    } else {
        message_utils::sendText<message_utils::LogLevel::Error>(
            player,
            "未找到最近的无主地皮"_trl(player.getLocaleCode())
        );
    }
}
void PlotController::sendPlayerCurrentPlot(Player& player) const {
    auto coord = PlotCoord{player.getPosition()};
    if (!coord.isValid()) {
        message_utils::sendText<message_utils::LogLevel::Error>(
            player,
            "您当前所在的位置不是地皮"_trl(player.getLocaleCode())
        );
        return;
    }
    if (impl->registry.hasPlot(coord)) {
        PlotManagerGUI::sendTo(player, impl->registry.getPlot(coord));
    } else {
        // TODO: send buy gui
    }
}

void PlotController::switchPlayerDimension(Player& player, bool toOverworld) const {
    if (toOverworld) {
        player.teleport(player.getExpectedSpawnPosition(), player.getExpectedSpawnDimensionId(), player.getRotation());
    } else {
        // TODO: teleport to plotx dimension
    }
}


} // namespace plotx