#pragma once
#include <optional>

namespace plotx {

enum class PermCategory {
    Core,       // 核心
    Combat,     // 战斗
    Item,       // 物品
    Entity,     // 实体
    Tools,      // 工具
    Functional, // 功能方块
    Decorative, // 装饰
    Special,    // 特殊
    Environment // 环境
};

struct PermMeta {
    enum class Scope { Global, Role };
    struct ValueEntry {
        std::optional<bool> global; // Scope::Global
        std::optional<bool> member; // Scope::Role
        std::optional<bool> guest;  // Scope::Role

        inline constexpr bool operator==(const ValueEntry& rhs) const = default;
    };

    Scope        scope{Scope::Global}; // 范围
    PermCategory category;             // UI分类
    ValueEntry     defValue;                // 默认值

    // 角色权限 (Role Scope)
    static inline PermMeta make(PermCategory cat, bool defMember, bool defGuest) {
        return PermMeta{
            Scope::Role,
            cat,
            {std::nullopt, defMember, defGuest}
        };
    }
    // 环境标志 (Global Scope)
    static inline PermMeta make(PermCategory cat, bool defVal) {
        return PermMeta{
            Scope::Global,
            cat,
            {defVal, std::nullopt, std::nullopt}
        };
    }
};

} // namespace plotx