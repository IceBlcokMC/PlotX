#include "PlayerLeavePlotEvent.hpp"

#include "Helper.hpp"

namespace plotx::event {


PlayerLeavePlotEvent::PlayerLeavePlotEvent(
    Player*          player,
    Vec3 const&      currentPos,
    int const&       currentDimId,
    PlotCoord const& currentPlotCoord,
    int const&       lastDimId,
    PlotCoord const& lastPlotCoord
)
: IPlayerOnPlotMoveEvent(player, currentPos, currentDimId, currentPlotCoord, lastDimId, lastPlotCoord) {}

IMPL_EVENT_EMITTER(PlayerLeavePlotEvent)

} // namespace plotx::event