#pragma once
#include <functional>
#include <optional>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Concepts.hpp"

namespace plotx {


class NodeTree {
public:
    using NodePair = std::pair<int, int>;

    struct Node {
        int    x, z;          // 坐标
        double distance{0.0}; // 距离

        Node() = delete;
        explicit Node(int x, int z);
        explicit Node(NodePair p);
        explicit Node(int x, int z, double distance);

        template <concepts::HasXZ T = Node>
        explicit Node(T const& cl) {
            this->x = cl.x;
            this->z = cl.z;
        }

        operator NodePair() const;

        constexpr bool operator<(Node const& other) const {
            return distance > other.distance; // 优先按距离排序
        }
    };
    struct PairHash {
        std::size_t operator()(NodePair const& p) const {
            return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
        }
    };

    // member
    std::unordered_set<NodePair, PairHash> nodes; // 节点集合

    // method
    bool contains(NodePair const& p) const;
    bool contains(int x, int z) const;

    void insert(NodePair const& p);
    void insert(int x, int z);

    void remove(NodePair const& p);
    void remove(int x, int z);

    void clear();

    // 查找距离 root 最近的未标记节点
    std::optional<Node> findNearestUnmarkedNodeFromRoot(NodePair root = {0, 0});
};


} // namespace plotx
