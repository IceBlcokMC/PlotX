#pragma once
#include <functional>
#include <memory>


class Player;
namespace plotx {
class PlotHandle;
}

namespace plotx {

struct PlotPicker {
    PlotPicker() = delete;

    static void sendTo(Player& player, std::function<void(Player&, std::shared_ptr<PlotHandle>)> const& callback);
};

} // namespace plotx
