#pragma once
#include <functional>
#include <mc/platform/UUID.h>


class Player;
namespace plotx {

struct PlayerPicker {
    PlayerPicker() = delete;

    static void sendTo(Player& player, std::function<void(Player& self, mce::UUID picked)> const& callback);
};

} // namespace plotx
