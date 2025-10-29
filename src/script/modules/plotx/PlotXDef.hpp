#pragma once
#include "qjspp/Binding.hpp"
#include "qjspp/Definitions.hpp"
#include "qjspp/Module.hpp"


namespace plotx::script::modules {


struct PlotXDef {
    PlotXDef() = delete;

    // === core ===
    static qjspp::ClassDefine const PlotHandleDef_;
    static qjspp::ClassDefine const PlotRegistryDef_;

    // === math ===
    static qjspp::ClassDefine const PlotAABBDef_;
    static qjspp::ClassDefine const PlotCoordDef_;
    static qjspp::ClassDefine const PlotRoadDef_;
    static qjspp::ClassDefine const PlotCrossDef_;

    static qjspp::ModuleDefine const& getModuleDef();
};


} // namespace plotx::script::modules
