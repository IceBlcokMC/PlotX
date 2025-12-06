#pragma once
#include <memory>


class Player;

namespace plotx {
class PlotHandle;

struct PlotManagerGUI {
    PlotManagerGUI() = delete;

    static void sendTo(Player& player, std::shared_ptr<PlotHandle> handle);
};

} // namespace plotx
