#include "PermRegistry.hpp"
#include "PermKeys.hpp"
#include "PermMeta.hpp"
#include "ll/api/reflection/Serialization.h"
#include "nlohmann/json_fwd.hpp"
#include "plotx/PlotX.hpp"
#include "plotx/infra/Reflection.hpp"

#include <ll/api/io/FileUtils.h>

namespace plotx {

decltype(PermRegistry::perms) PermRegistry::perms{};

ll::Expected<> PermRegistry::registerImpl(HashedStringView key, PermMeta meta) {
    if (perms.contains(key)) {
        return ll::makeStringError(fmt::format("Perm already registered:{} ", key.getString()));
    }
    perms.emplace(key, std::move(meta));
    return {};
}

void PermRegistry::buildDefault() {
    // === 基础权限 ===
    registerPerm(perm_keys::allowDestroy, PermCategory::Core, false, false);
    registerPerm(perm_keys::allowPlace, PermCategory::Core, false, false);
    registerPerm(perm_keys::allowInteract, PermCategory::Core, false, false);

    // === 战斗权限 ===
    registerPerm(perm_keys::allowPlayerDamage, PermCategory::Combat, false, false);
    registerPerm(perm_keys::allowMonsterDamage, PermCategory::Combat, true, true);
    registerPerm(perm_keys::allowPassiveDamage, PermCategory::Combat, false, false);
    registerPerm(perm_keys::allowSpecialDamage, PermCategory::Combat, false, false);
    registerPerm(perm_keys::allowCustomSpecialDamage, PermCategory::Combat, false, false);

    // === 物品权限 ===
    registerPerm(perm_keys::allowPickupItem, PermCategory::Item, false, false);
    registerPerm(perm_keys::allowDropItem, PermCategory::Item, true, true);
    registerPerm(perm_keys::allowProjectileCreate, PermCategory::Item, false, false);

    // === 实体权限 ===
    registerPerm(perm_keys::allowRideEntity, PermCategory::Entity, false, false);
    registerPerm(perm_keys::allowInteractEntity, PermCategory::Entity, false, false);
    registerPerm(perm_keys::allowActorDestroy, PermCategory::Entity, false, false);

    // === 工具权限 ===
    registerPerm(perm_keys::useTools, PermCategory::Tools, false, false);
    registerPerm(perm_keys::useBucket, PermCategory::Tools, false, false);
    registerPerm(perm_keys::allowFishingRodAndHook, PermCategory::Tools, false, false);

    // === 功能方块权限 ===
    registerPerm(perm_keys::useFurnaces, PermCategory::Functional, false, false);
    registerPerm(perm_keys::useCraftingBlocks, PermCategory::Functional, false, false);
    registerPerm(perm_keys::useStorageBlocks, PermCategory::Functional, false, false);
    registerPerm(perm_keys::useRedstoneBlocks, PermCategory::Functional, false, false);
    registerPerm(perm_keys::useUtilityBlocks, PermCategory::Functional, false, false);

    // === 装饰交互权限 ===
    registerPerm(perm_keys::useDecorative, PermCategory::Decorative, false, false);
    registerPerm(perm_keys::useMovement, PermCategory::Decorative, false, false);
    registerPerm(perm_keys::editSigns, PermCategory::Decorative, false, false);
    registerPerm(perm_keys::editFlowerPot, PermCategory::Decorative, false, false);

    // === 特殊权限 ===
    registerPerm(perm_keys::useBed, PermCategory::Special, false, false);
    registerPerm(perm_keys::useCake, PermCategory::Special, false, false);
    registerPerm(perm_keys::placeVehicles, PermCategory::Special, false, false);
    registerPerm(perm_keys::allowAttackDragonEgg, PermCategory::Special, false, false);

    // === 环境权限 ===
    registerPerm(perm_keys::allowFireSpread, PermCategory::Environment, true);
    registerPerm(perm_keys::allowFarmDecay, PermCategory::Environment, true);
    registerPerm(perm_keys::allowPistonPushOnBoundary, PermCategory::Environment, true);
    registerPerm(perm_keys::allowRedstoneUpdate, PermCategory::Environment, true);
    registerPerm(perm_keys::allowExplode, PermCategory::Environment, false);
    registerPerm(perm_keys::allowBlockFall, PermCategory::Environment, false);
    registerPerm(perm_keys::allowWitherDestroy, PermCategory::Environment, false);
    registerPerm(perm_keys::allowLiquidFlow, PermCategory::Environment, true);
    registerPerm(perm_keys::allowSculkBlockGrowth, PermCategory::Environment, true);
    registerPerm(perm_keys::allowMonsterSpawn, PermCategory::Environment, true);
    registerPerm(perm_keys::allowAnimalSpawn, PermCategory::Environment, true);
    registerPerm(perm_keys::allowEndermanLeaveBlock, PermCategory::Environment, false);
}
ll::Expected<> PermRegistry::loadOverrides(PlotX& mod) {
    auto path = mod.getSelf().getConfigDir() / "PermOverrides.json";
    if (!std::filesystem::exists(path)) {
        auto json = reflection::struct2json(perms).value().dump(2);
        ll::file_utils::writeFile(path, json);
        return {};
    }
    auto rawJson = ll::file_utils::readFile(path);
    if (!rawJson) {
        return ll::makeStringError("Failed to read PermOverrides.json");
    }
    try {
        auto json = nlohmann::json::parse(*rawJson);
        reflection::json2structDiffPatch(perms, json);
        return ensureOverrides();
    } catch (nlohmann::json::exception const& exception) {
        return ll::makeStringError(exception.what());
    }
}
ll::Expected<> PermRegistry::ensureOverrides() {
    for (auto& [key, meta] : perms) {
        auto& valueSet = meta.defValue;
        switch (meta.scope) {
        case PermMeta::Scope::Global:
            if (valueSet.guest || valueSet.member) {
                return ll::makeStringError(
                    fmt::format("Global scope permission '{}' cannot have 'member' or 'guest' value", key.getString())
                );
            }
            break;
        case PermMeta::Scope::Role:
            if (valueSet.global) {
                return ll::makeStringError(
                    fmt::format("Role scope permission '{}' cannot have 'global' value", key.getString())
                );
            }
            break;
        }
    }
    return {};
}
ll::Expected<> PermRegistry::registerPerm(HashedStringView key, PermCategory cat, bool defMember, bool defGuest) {
    assert(cat != PermCategory::Environment);
    return registerImpl(key, PermMeta::make(cat, defMember, defGuest));
}
ll::Expected<> PermRegistry::registerPerm(HashedStringView key, PermCategory cat, bool defVal) {
    assert(cat == PermCategory::Environment);
    return registerImpl(key, PermMeta::make(cat, defVal));
}
optional_ref<PermMeta> PermRegistry::getMeta(HashedStringView key) {
    auto iter = perms.find(key);
    if (iter == perms.end()) {
        return {};
    }
    return {iter->second};
}
bool PermRegistry::getEnvDefault(HashedStringView key) {
    return getMeta(key).and_then(
                           [](PermMeta& meta) -> std::optional<bool> { return meta.defValue.global; }
    ).value_or(false);
}
bool PermRegistry::getRoleDefault(HashedStringView key, bool isMember) {
    return getMeta(key)
        .and_then([&isMember](PermMeta& meta) { return isMember ? meta.defValue.member : meta.defValue.guest; })
        .value_or(false);
}

} // namespace plotx