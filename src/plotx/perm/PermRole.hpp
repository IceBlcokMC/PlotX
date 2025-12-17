#pragma once

namespace plotx {

enum class PermRole {
    Admin  = 0, // 全局管理员
    Owner  = 1, // 地皮主人
    Member = 2, // 地皮成员
    Gust   = 3  // 游客
};

}