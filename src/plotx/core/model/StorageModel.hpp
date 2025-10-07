#pragma once
#include "plotx/Global.hpp"
#include <cstdint>
#include <string>
#include <vector>


namespace plotx {


using CommentID = uint32_t;
struct CommentModel {
    CommentID   id_{};      // 评论id
    std::string author_{};  // 评论者
    std::string content_{}; // 评论内容
    std::string time_{};    // 评论时间
};

struct Vec2Model {
    int x{}, z{};
};

struct AABBModel {
    Vec2Model min, max;
};

struct RoadModel {
    Vec2Model position_{};     // 道路坐标
    bool      isTransverse_{}; // 道路方向(true: 横, false: 纵)
};

struct MultiPlotModel {
    int                    counter_{};      // 合并计数器
    AABBModel              currentAABB_{};  // 当前合并的地皮范围
    std::vector<Vec2Model> mergedPlots_{};  // 合并的地皮
    std::vector<Vec2Model> includeCross_{}; // 包含的十字路口
    std::vector<RoadModel> includeRoads_{}; // 包含的道路
};

constexpr int PlotModelVersion = 20;
struct PlotModel {
    int                       version{PlotModelVersion};
    Vec2Model                 position_{};  // 地皮坐标
    std::string               owner_{};     // 地皮主人
    std::string               name_{};      // 地皮名称
    bool                      isSale_{};    // 是否正在出售
    int                       price_{};     // 出售价格
    std::vector<std::string>  members_{};   // 地皮成员
    std::vector<CommentModel> comments_{};  // 评论
    bool                      isMerged_{};  // 是否是合并的地皮
    MultiPlotModel            multiPlot_{}; // 合并的地皮信息
};

STATIC_ASSERT_AGGREGATE(CommentModel);
STATIC_ASSERT_AGGREGATE(Vec2Model);
STATIC_ASSERT_AGGREGATE(AABBModel);
STATIC_ASSERT_AGGREGATE(RoadModel);
STATIC_ASSERT_AGGREGATE(MultiPlotModel);
STATIC_ASSERT_AGGREGATE(PlotModel);


} // namespace plotx