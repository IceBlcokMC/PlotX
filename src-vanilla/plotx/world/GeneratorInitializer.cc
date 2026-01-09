#include "plotx/world/GeneratorInitializer.hpp"
#include "VanillaDimensionHook.h"

#include "ll/api/Expected.h"


namespace plotx::world {


ll::Expected<> GeneratorInitializer::operator()() {
    VanillaDimensionHook::hook(VanillaDimensionHook::Overworld);
    return {};
}


} // namespace plotx::world