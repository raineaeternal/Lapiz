#pragma once

// #include "System/Reflection/MonoMethod.hpp"
// #include "System/Reflection/MonoMethodInfo.hpp"
#include "beatsaber-hook/shared/utils/typedefs.h"

#include "System/Attribute.hpp"
#include "System/Type.hpp"

namespace Lapiz::Zenject::Internal {
    class Attributes {
        public:
            // static void MonoField_GetCustomAttributes(ArrayW<::Il2CppObject*>& retval, System::Reflection::MonoField* self, System::Type* attributeType, bool inherit);
            // static void MonoMethod_GetCustomAttributes(ArrayW<::Il2CppObject*>& retval, System::Reflection::MonoMethod* self, System::Type* attributeType, bool inherit);
        private:
            static bool DerivesFromInjectAttributeBase(System::Type* type);
            static ArrayW<Il2CppObject*> InsertCustomAttribute(::ArrayW<Il2CppObject*> arr, Il2CppObject* attribute);
            static System::Attribute* GetInjectAttribute(System::Reflection::MemberInfo* member);
    };
}
