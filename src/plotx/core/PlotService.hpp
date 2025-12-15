#pragma once
#include <ll/api/Expected.h>

#include <memory>
#include <string>


namespace mce {
class UUID;
}
class Dimension;
class Player;
namespace plotx {
class PlotHandle;
class PlotCoord;
class PlotX;
class PlotRegistry;
} // namespace plotx

namespace plotx {

class PlotService {
    struct Impl;
    std::unique_ptr<Impl> impl;

public:
    explicit PlotService(PlotRegistry& registry, PlotX& mod);
    ~PlotService();

    ll::Expected<> teleportUnownedPlot(Player& player) const;

    ll::Expected<> teleportToPlot(Player& player, std::shared_ptr<PlotHandle> handle) const;

    ll::Expected<> showPlotGUIFor(Player& player) const;

    ll::Expected<> switchPlayerDimension(Player& player) const;

    ll::Expected<> changePlotName(Player& player, std::shared_ptr<PlotHandle> handle, std::string newName);

    ll::Expected<>
    modifyPlotMember(Player& player, std::shared_ptr<PlotHandle> handle, mce::UUID const& target, bool isAdd);

    ll::Expected<> claimPlot(Player& player, PlotCoord coord);

    ll::Expected<> transferPlotTo(Player& player, std::shared_ptr<PlotHandle> handle);

private:
    ll::Expected<> handleTeleportToPlot(Player& player, int x, int z) const;
};

} // namespace plotx
