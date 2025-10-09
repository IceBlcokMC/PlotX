#include "script/modules/Helper.hpp"
#include "script/modules/minecraft/defs.hpp"


namespace plotx::script::api::inline minecraft {

qjspp::ClassDefine const UUIDDef_ = qjspp::defineClass<mce::UUID>("UUID")
                                        .constructor<std::string const&>()
                                        .instanceMethod("asString", &mce::UUID::asString)
                                        .function("canParse", &mce::UUID::canParse)
                                        .function("fromString", &mce::UUID::fromString)
                                        .build();


}
