#include "PlotController.hpp"

#include "PlotRegistry.hpp"
#include "plotx/PlotX.hpp"
#include "plotx/math/PlotCoord.hpp"
#include "plotx/utils/MessageUtils.hpp"

#include "ll/api/i18n/I18n.h"

namespace plotx {

struct PlotController::Impl {
    PlotRegistry& registry;
    PlotX&        mod;
};

using ll::i18n_literals::operator""_tr;
using ll::i18n_literals::operator""_trl;

PlotController::PlotController(PlotRegistry& registry, PlotX& mod) : impl(std::make_unique<Impl>(registry, mod)) {}
PlotController::~PlotController() {}

void PlotController::teleportUnownedPlot(Player& player) {
    if (auto coord = impl->registry.findUnownedPlot()) {
        // TODO: impl
    } else {
        message_utils::sendText<message_utils::LogLevel::Error>(
            player,
            "未找到最近的无主地皮"_trl(player.getLocaleCode())
        );
    }
}


} // namespace plotx