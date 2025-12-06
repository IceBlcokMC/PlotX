#pragma once


class Player;
namespace plotx {
class PlotCoord;

struct BuyPlotGUI {
    BuyPlotGUI() = delete;

    static void sendTo(Player& player, PlotCoord coord);
};

} // namespace plotx
