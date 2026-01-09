#pragma once
#include "ll/api/Expected.h"

namespace plotx::world {


struct GeneratorInitializer {
    GeneratorInitializer() = default;
    ll::Expected<> operator()();
};


} // namespace plotx::world