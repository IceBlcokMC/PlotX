#include "PlotManagerGui.hpp"

#include "plotx/PlotX.hpp"
#include "plotx/core/PlotHandle.hpp"
#include "plotx/core/PlotRegistry.hpp"

#include <ll/api/form/SimpleForm.h>
#include <ll/api/i18n/I18n.h>
#include <ll/api/service/PlayerInfo.h>
#include <stdexcept>

namespace plotx {

using ll::i18n_literals::operator""_trl;

void PlotManagerGUI::sendTo(Player& player, std::shared_ptr<PlotHandle> handle) {
    if (!handle) {
        throw std::runtime_error("PlotManagerGUI::sendTo: handle is null");
    }
    auto localeCode = player.getLocaleCode();

    auto ownerInfo = ll::service::PlayerInfo::getInstance().fromUuid(handle->getOwner());

    bool const isAdmin  = PlotX::getInstance().getPlotRegistry()->isAdmin(player.getUuid());
    bool const isOwner  = handle->isOwner(player.getUuid());
    bool const isMember = handle->isMember(player.getUuid());
    bool const isGuest  = !isAdmin && !isOwner && !isMember;

    auto f = ll::form::SimpleForm{};
    f.setTitle("PlotX - 地皮管理"_trl(localeCode));
    f.setContent(
        "位置: {},{}\n所有者: {}\n名称: {}\n状态: {}"_trl(
            localeCode,
            handle->getCoord().x,
            handle->getCoord().z,
            ownerInfo ? ownerInfo->name : handle->getOwner().asString(),
            handle->getName(),
            handle->isForSale() ? "出售中 (价格:{})"_trl(localeCode, handle->getSellingPrice())
                                : "未出售"_trl(localeCode)
        )
    );
    if (!isGuest) {
        f.appendButton("传送到此地皮"_trl(localeCode), "textures/ui/move", "path", [handle](Player& player) {
            // TODO: impl
        });
    }
}


} // namespace plotx