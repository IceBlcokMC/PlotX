#pragma once
#include <memory>


class Player;
namespace plotx {
class PlotX;
class PlotRegistry;
} // namespace plotx

namespace plotx {

class PlotController {
    struct Impl;
    std::unique_ptr<Impl> impl;

public:
    explicit PlotController(PlotRegistry& registry, PlotX& mod);
    ~PlotController();

    void teleportUnownedPlot(Player& player);
};

} // namespace plotx
