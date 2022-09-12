#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"
#include "UnityEngine/Object.hpp"

DECLARE_CLASS_CODEGEN(Lapiz::Objects, ObjectDiffuser, Il2CppObject,
    DECLARE_PRIVATE_FIELD(UnityEngine::Object*, _object);
    DECLARE_INJECT_METHOD(void, Resolved);
    DECLARE_CTOR(ctor, UnityEngine::Object* obj);
)
