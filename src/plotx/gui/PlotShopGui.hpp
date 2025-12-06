#pragma once
#include <memory>


namespace plotx {
class PlotHandle;
}
class Player;
namespace plotx {

struct PlotShopGUI {
    PlotShopGUI() = delete;

    static void sendTo(Player& player);

private:
    static void showPlot(Player& player, std::shared_ptr<PlotHandle> handle);

    static void confirmBuyPlot(Player& player, std::shared_ptr<PlotHandle> handle);
};

} // namespace plotx
