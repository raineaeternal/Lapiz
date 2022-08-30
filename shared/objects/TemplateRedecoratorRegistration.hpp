#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

#include "RedecoratorRegistration.hpp"

DECLARE_CLASS_CUSTOM(Lapiz::Objects, TemplateRedecoratorRegistration, RedecoratorRegistration,
    DECLARE_INSTANCE_METHOD(Il2CppObject*, Redecorate, Il2CppObject* value);
    DECLARE_CTOR(ctor, StringW contract, System::Type* prefabType, System::Type* containerType, int priority, bool chain);

    template<typename TPrefabType, typename TParentType>
    TemplateRedecoratorRegistration* Make(std::string_view contract, std::function<TPrefabType(TPrefabType)> redecorateCall, int priority = 0, bool chain = true) {
        auto res = TemplateRedecoratorRegistration::New_ctor(contract, csTypeOf(TPrefabType), csTypeOf(TParentType), priority, chain);
        _redecorateCall = [redecorateCall](Il2CppObject* value) -> Il2CppObject* {
            return redecorateCall(reinterpret_cast<TPrefabType>(value));
        };
        return res;
    }

    private:
        std::function<Il2CppObject*(Il2CppObject*)> _redecorateCall;
)