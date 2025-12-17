#pragma once
#include "PermMeta.hpp"
#include "plotx/infra/HashedStringView.hpp"

#include "nlohmann/json.hpp"

#include <unordered_map>

namespace plotx {

/**
 * 稀疏存储容器
 */
class PermStorage {
    std::unordered_map<HashedString, PermMeta::ValueEntry, HashedStringHasher, HashedStringEqual> data;

public:
    optional_ref<const PermMeta::ValueEntry> get(HashedStringView key) const;

    enum class SetTarget { Global, Member, Guest };
    void set(HashedStringView key, bool value, SetTarget target);

    bool resolve(HashedStringView key, SetTarget target) const;

    nlohmann::json toJson() const;
    void           fromJson(nlohmann::json const& j);
};

} // namespace plotx