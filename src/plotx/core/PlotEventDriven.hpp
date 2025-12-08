#pragma once
#include "ll/api/coro/InterruptableSleep.h"
#include "ll/api/event/ListenerBase.h"
#include "mc/deps/core/math/Vec3.h"
#include "mc/platform/UUID.h"
#include "mc/world/actor/player/Player.h"
#include <unordered_map>
#include <vector>


namespace plotx {

class PlotCoord;

/**
 * @brief 事件驱动
 * @note 驱动地皮的进出事件
 */
class PlotEventDriven {
    struct Impl;
    std::unique_ptr<Impl> impl;

public:
    PlotEventDriven();
    ~PlotEventDriven();

    void tick() const;
    void updateTip(Player* player, Vec3 const& pos, PlotCoord const& coord) const;
};


} // namespace plotx