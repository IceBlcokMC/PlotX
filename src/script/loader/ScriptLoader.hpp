#pragma once
#include <ll/api/mod/ModManager.h>


namespace plotx {
class PlotX;
}

namespace plotx::script {

class ScriptLoader final : public ll::mod::ModManager {
    PlotX& main_;

public:
    static constexpr std::string_view kModType = "plotx-script";

    explicit ScriptLoader(PlotX& entry);
    ~ScriptLoader() override;

protected:
    ll::Expected<> load(ll::mod::Manifest manifest) override;

    ll::Expected<> enable(std::string_view name) override;

    ll::Expected<> disable(std::string_view name) override;

    ll::Expected<> unload(std::string_view name) override;
};

} // namespace plotx::script
