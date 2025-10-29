#include "PlotXDef.hpp"
#include "qjspp/Module.hpp"


namespace plotx::script::modules {


qjspp::ModuleDefine const& PlotXDef::getModuleDef() {
    static auto def = qjspp::defineModule("@plotx")
                          .addClass(PlotAABBDef_)
                          .addClass(PlotCoordDef_)
                          .addClass(PlotRoadDef_)
                          .addClass(PlotCrossDef_)
                          .build();
    return def;
}


} // namespace plotx::script::modules