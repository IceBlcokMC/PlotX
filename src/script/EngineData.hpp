#pragma once
#include <cstdint>
#include <memory>
#include <string>


namespace plotx::script {

class ScriptMod;

using EngineID = uint64_t;

struct EngineData {
    EngineID                 id_;
    std::weak_ptr<ScriptMod> mod_;
    std::string              modName_;
};

} // namespace plotx::script