#include "MainGUI.hpp"
#include "PlotManagerGui.hpp"
#include "PlotPicker.hpp"
#include "PlotShopGui.hpp"
#include "plotx/PlotX.hpp"
#include "plotx/core/PlotController.hpp"

#include "ll/api/form/SimpleForm.h"
#include "ll/api/i18n/I18n.h"


namespace plotx {

void MainGUI::sendTo(Player& player) {
    using ll::i18n_literals::operator""_trl;
    auto localeCode = player.getLocaleCode();

    auto fm = ll::form::SimpleForm{};
    fm.setTitle("PlotX - 菜单"_trl(localeCode));
    fm.setContent("请选择一个操作"_trl(localeCode));

    if (player.getDimensionId() == PlotX::getDimensionId()) {
        fm.appendButton("前往主世界"_trl(localeCode), "textures/ui/realmsIcon", "path", [](Player& pl) {
            PlotX::getInstance().getController()->switchPlayerDimension(pl, true);
        });
    } else {
        fm.appendButton("前往地皮世界"_trl(localeCode), "textures/ui/realmsIcon", "path", [](Player& pl) {
            PlotX::getInstance().getController()->switchPlayerDimension(pl, false);
        });
    }
    fm.appendButton("管理脚下地皮"_trl(localeCode), "textures/ui/icon_recipe_item", "path", [](Player& pl) {
        PlotX::getInstance().getController()->sendPlayerCurrentPlot(pl);
    });
    fm.appendButton("管理地皮"_trl(localeCode), "textures/ui/icon_recipe_nature", "path", [](Player& pl) {
        PlotPicker::sendTo(pl, [](Player& player, std::shared_ptr<PlotHandle> handle) {
            PlotManagerGUI::sendTo(player, handle);
        });
    });
    fm.appendButton("地皮商店"_trl(localeCode), "textures/ui/store_home_icon", "path", [](Player& pl) {
        PlotShopGUI::sendTo(pl);
    });
    fm.appendButton("关闭"_trl(localeCode));
    fm.sendTo(player);
}

} // namespace plotx