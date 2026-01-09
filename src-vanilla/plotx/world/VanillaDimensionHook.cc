#include "VanillaDimensionHook.h"
#include "plotx/world/generator/PlotGenerator.hpp"

#include "minecraft/FixedBiomeSource.h"

#include "ll/api/memory/Hook.h"

#include "mc/world/level/Level.h"
#include "mc/world/level/dimension/NetherDimension.h"
#include "mc/world/level/dimension/OverworldDimension.h"
#include "mc/world/level/dimension/end/TheEndDimension.h"
#include "mc/world/level/levelgen/WorldGenerator.h"
#include "mc/world/level/levelgen/structure/registry/StructureSetRegistry.h"
#include "mc/world/level/storage/LevelData.h"

#include <atomic>
#include <memory>
#include <stdexcept>

namespace plotx {

namespace detail {


#define HOOK_MACRO(DIMENSION)                                                                                          \
    LL_TYPE_INSTANCE_HOOK(                                                                                             \
        DIMENSION##Hook,                                                                                               \
        ll::memory::HookPriority::Normal,                                                                              \
        DIMENSION,                                                                                                     \
        &DIMENSION::$createGenerator,                                                                                  \
        std::unique_ptr<WorldGenerator>,                                                                               \
        br::worldgen::StructureSetRegistry const& /* structureSetRegistry */                                           \
    )


HOOK_MACRO(OverworldDimension) {
    mSeaLevel = -61;
    auto gen =
        std::make_unique<plotx::world::PlotGenerator>(*this, mLevel.getSeed(), mLevel.getLevelData().mFlatWorldOptions);

    return std::move(gen);
}

// HOOK_MACRO(NetherDimension) {}

// HOOK_MACRO(TheEndDimension) {}

#undef HOOK_MACRO

} // namespace detail

static std::atomic_bool                                   hooked{false};
static std::atomic<VanillaDimensionHook::TargetDimension> target{};

bool VanillaDimensionHook::isHooked() { return hooked; }

VanillaDimensionHook::TargetDimension VanillaDimensionHook::getTarget() { return target; }

void VanillaDimensionHook::hook(TargetDimension target) {
    if (hooked) {
        throw std::logic_error{"VanillaDimensionHook is already hooked"};
    }
    hooked        = true;
    plotx::target = target;
    switch (target) {
    case Overworld:
        detail::OverworldDimensionHook::hook();
        break;
    case Nether:
    case TheEnd:
        hooked = false;
        throw std::logic_error{"Nether and The End dimensions are not supported yet"};
        break;
    }
}

void VanillaDimensionHook::unhook() {
    if (!hooked) {
        throw std::logic_error{"VanillaDimensionHook is not hooked"};
    }
    hooked = false;
    switch (target) {
    case Overworld:
        detail::OverworldDimensionHook::unhook();
        break;
    case Nether:
    case TheEnd:
        throw std::logic_error{"Nether and The End dimensions are not supported yet"};
        break;
    }
}


} // namespace plotx