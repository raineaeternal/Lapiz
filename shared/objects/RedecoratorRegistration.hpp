#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

DECLARE_CLASS_CODEGEN(Lapiz::Objects, RedecoratorRegistration, Il2CppObject,
    DECLARE_PRIVATE_FIELD(bool, _chain);
    DECLARE_PRIVATE_FIELD(int, _priority);
    DECLARE_PRIVATE_FIELD(StringW, _contract);

    DECLARE_PRIVATE_FIELD(System::Type*, _prefabType);
    DECLARE_PRIVATE_FIELD(System::Type*, _containerType);
    DECLARE_PRIVATE_FIELD(void*, minfo);

    DECLARE_INSTANCE_METHOD(bool, get_chain);
    DECLARE_INSTANCE_METHOD(int, get_priority);
    DECLARE_INSTANCE_METHOD(StringW, get_contract);

    DECLARE_INSTANCE_METHOD(System::Type*, get_prefabType);
    DECLARE_INSTANCE_METHOD(System::Type*, get_containerType);

    DECLARE_INSTANCE_METHOD(Il2CppObject*, Redecorate_internal, Il2CppObject* value);
    DECLARE_CTOR(ctor, StringW contract, System::Type* prefabType, System::Type* containerType, int priority, bool chain);

)
