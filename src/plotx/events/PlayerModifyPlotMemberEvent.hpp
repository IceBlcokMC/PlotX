#pragma once
#include <cstdint>
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/player/PlayerEvent.h>


namespace plotx {
class PlotHandle;
}
class Player;
namespace plotx {

class PlayerModifyPlotMemberEvent final : public ll::event::Cancellable<ll::event::PlayerEvent> {
public:
    enum class ModifyType : bool { Add = true, Remove = false };

    explicit PlayerModifyPlotMemberEvent(
        Player&                     player,
        std::shared_ptr<PlotHandle> handle,
        mce::UUID const&            target,
        ModifyType                  type
    )
    : Cancellable(player),
      handle_(std::move(handle)),
      target_(target),
      type_(type) {}

    std::shared_ptr<PlotHandle> handle() const;

    mce::UUID const& target() const;

    ModifyType type() const;

private:
    std::shared_ptr<PlotHandle> handle_;
    mce::UUID const&            target_;
    ModifyType                  type_;
};

} // namespace plotx
