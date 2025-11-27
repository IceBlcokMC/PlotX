#pragma once
#include "plotx/Global.hpp"

#include <memory>
#include <string_view>


namespace plotx {
class PlotHandle;
}
namespace ll::io {
class Logger;
}
namespace mce {
class UUID;
}

namespace plotx {

class PlotX;
class PlotCoord;

// 地皮注册表
class PlotRegistry final {
    struct Impl;
    std::unique_ptr<Impl> impl_;

    void _upgradeDatabase(ll::io::Logger& logger);
    void _loadAdmins(ll::io::Logger& logger);
    void _loadPlots(ll::io::Logger& logger);

public:
    PLOTX_DISALLOW_COPY_AND_MOVE(PlotRegistry);
    explicit PlotRegistry(PlotX& plotx);
    ~PlotRegistry();

    PXAPI bool isAdmin(mce::UUID const& uuid) const;
    PXAPI void addAdmin(mce::UUID const& uuid);
    PXAPI void removeAdmin(mce::UUID const& uuid);

    PXNDAPI bool hasPlot(int x, int z) const;
    PXNDAPI bool hasPlot(PlotCoord const& coord) const;

    PXNDAPI std::shared_ptr<PlotHandle> getPlot(int x, int z) const;
    PXNDAPI std::shared_ptr<PlotHandle> getPlot(PlotCoord const& coord) const;

    PXNDAPI bool addPlot(std::shared_ptr<PlotHandle> handle);

    PXNDAPI bool removePlot(int x, int z);
    PXNDAPI bool removePlot(PlotCoord const& coord);
    PXNDAPI bool removePlot(std::shared_ptr<PlotHandle> const& handle);

    /**
     * 新建地皮并注册 (脚本辅助)
     * @param coord 坐标
     * @param owner 所有者
     * @return 地皮句柄
     */
    PXNDAPI std::shared_ptr<PlotHandle> newPlot(PlotCoord const& coord, mce::UUID const& owner);

    /**
     * 新建地皮并注册 (脚本辅助)
     * @param x X坐标
     * @param z Z坐标
     * @param owner 所有者
     * @return 地皮句柄
     */
    PXNDAPI std::shared_ptr<PlotHandle> newPlot(int x, int z, mce::UUID const& owner);

public:
    static constexpr std::string_view VersionKey    = "_version_"; // 版本号
    static constexpr std::string_view AdminsKey     = "admins";    // 管理员
    static constexpr std::string_view PlotKeyPrefix = "plot_";     // 地皮
};


} // namespace plotx