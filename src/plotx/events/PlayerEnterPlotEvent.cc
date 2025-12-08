#include "PlayerEnterPlotEvent.hpp"

#include "Helper.hpp"

namespace plotx::event {


PlayerEnterPlotEvent::PlayerEnterPlotEvent(
    Player*          player,
    Vec3 const&      currentPos,
    int const&       currentDimId,
    PlotCoord const& currentPlotCoord,
    int const&       lastDimId,
    PlotCoord const& lastPlotCoord
)
: IPlayerOnPlotMoveEvent(player, currentPos, currentDimId, currentPlotCoord, lastDimId, lastPlotCoord) {}

IMPL_EVENT_EMITTER(PlayerEnterPlotEvent)

} // namespace plotx::event