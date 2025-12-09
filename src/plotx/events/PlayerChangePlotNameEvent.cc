#include "PlayerChangePlotNameEvent.hpp"

#include "Helper.hpp"

namespace plotx {

std::shared_ptr<PlotHandle> PlayerChangePlotNameEvent::getPlotHandle() const { return handle_; }

std::string& PlayerChangePlotNameEvent::getNewName() const { return newName_; }

IMPL_EVENT_EMITTER(PlayerChangePlotNameEvent)

} // namespace plotx