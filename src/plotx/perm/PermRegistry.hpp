#pragma once
#include "PermMeta.hpp"
#include "plotx/infra/HashedStringView.hpp"

#include <ll/api/Expected.h>

namespace plotx {
class PlotX;
struct PermMeta;
enum class PermCategory;
} // namespace plotx

namespace plotx {

class PermRegistry {
    static std::unordered_map<HashedString, PermMeta, HashedStringHasher, HashedStringEqual> perms;

    static ll::Expected<> registerImpl(HashedStringView key, PermMeta meta);

public:
    PermRegistry() = delete;

    // mod internal use
    static void           buildDefault();
    static ll::Expected<> loadOverrides(PlotX& mod);
    static ll::Expected<> ensureOverrides();

    // 角色权限
    static ll::Expected<> registerPerm(HashedStringView key, PermCategory cat, bool defMember, bool defGuest);
    // 环境权限
    static ll::Expected<> registerPerm(HashedStringView key, PermCategory cat, bool defVal);

    static optional_ref<PermMeta> getMeta(HashedStringView key);

    static bool getEnvDefault(HashedStringView key);
    static bool getRoleDefault(HashedStringView key, bool isMember);
};

} // namespace plotx
