#pragma once
#include "ll/api/event/Emitter.h"
#include "ll/api/event/EmitterBase.h"

#define IMPL_EVENT_EMITTER(EventName)                                                                                  \
    static std::unique_ptr<ll::event::EmitterBase> emitterFactory##EventName();                                        \
    class EventName##Emitter : public ll::event::Emitter<emitterFactory##EventName, EventName> {};                     \
    static std::unique_ptr<ll::event::EmitterBase> emitterFactory##EventName() {                                       \
        return std::make_unique<EventName##Emitter>();                                                                 \
    }