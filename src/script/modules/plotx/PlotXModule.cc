#include "PlotXModule.hpp"
#include "qjspp/bind/meta/ModuleDefine.hpp"
#include "qjspp/types/Boolean.hpp"
#include "qjspp/types/Value.hpp"

#include <qjspp/bind/builder/ModuleDefineBuilder.hpp>


namespace plotx::script::modules {


qjspp::bind::meta::ModuleDefine const& PlotXModule::getModuleDef() {
    static auto def = qjspp::bind::defineModule("@plotx")
                          .addClass(ScriptPlotHandle)
                          .addClass(ScriptPlotRegistry)
                          .addClass(ScriptPlotAABB)
                          .addClass(ScriptPlotCoord)
                          .exportConstant(
                              "isMoreDimension",
                              []() -> qjspp::Value {
#ifdef PLOTX_OVERWORLD
                                  return qjspp::Boolean{false};
#else
                                  return qjspp::Boolean{true};
#endif
                              }
                          )
                          .build();
    return def;
}


} // namespace plotx::script::modules