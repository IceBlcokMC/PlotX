#include "PlayerModifyPlotMemberEvent.hpp"

#include "Helper.hpp"

namespace plotx {

PlayerModifyPlotMemberEvent::ModifyType PlayerModifyPlotMemberEvent::type() const { return type_; }

std::shared_ptr<PlotHandle> PlayerModifyPlotMemberEvent::handle() const { return handle_; }
mce::UUID const&            PlayerModifyPlotMemberEvent::target() const { return target_; }

IMPL_EVENT_EMITTER(PlayerModifyPlotMemberEvent)

} // namespace plotx