#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "Hooks/Attributes.hpp"
#include "Zenject/InjectAttributeBase.hpp"
#include "AttributeRegistration_internal.hpp"
// TODO: figure out where custom attributes are retreived, and inject our own
// MAKE_AUTO_HOOK_MATCH(MonoField_GetCustomAttributes,
//         static_cast<::ArrayW<::Il2CppObject*> (System::Reflection::MonoField::*)(::System::Type*, bool)>(&System::Reflection::MonoField::GetCustomAttributes),
//         ArrayW<::Il2CppObject*>,
//         System::Reflection::MonoField* self,
//         System::Type* attributeType,
//         bool inherit
//     ) {
//     auto retVal = MonoField_GetCustomAttributes(self, attributeType, inherit);
//     Lapiz::Zenject::Internal::Attributes::MonoField_GetCustomAttributes(retVal, self, attributeType, inherit);
//     return retVal;
// }

// MAKE_AUTO_HOOK_MATCH(MonoMethod_GetCustomAttributes,
//         static_cast<::ArrayW<::Il2CppObject*> (System::Reflection::MonoMethod::*)(::System::Type*, bool)>(&System::Reflection::MonoMethod::GetCustomAttributes),
//         ArrayW<::Il2CppObject*>,
//         System::Reflection::MonoMethod* self,
//         System::Type* attributeType,
//         bool inherit
//     ) {
//     auto retVal = MonoMethod_GetCustomAttributes(self, attributeType, inherit);
//     Lapiz::Zenject::Internal::Attributes::MonoMethod_GetCustomAttributes(retVal, self, attributeType, inherit);
//     return retVal;
// }

namespace Lapiz::Zenject::Internal {
    // void Attributes::MonoField_GetCustomAttributes(ArrayW<::Il2CppObject*>& retval, System::Reflection::MonoField* self, System::Type* attributeType, bool inherit) {
    //     if (!DerivesFromInjectAttributeBase(attributeType)) return;
    //     auto attribute = GetInjectAttribute(self);
    //     if (!attribute) return;
    //     retval = InsertCustomAttribute(retval, attribute);
    // }

    // void Attributes::MonoMethod_GetCustomAttributes(ArrayW<::Il2CppObject*>& retval, System::Reflection::MonoMethod* self, System::Type* attributeType, bool inherit) {
    //     if (!DerivesFromInjectAttributeBase(attributeType)) return;
    //     auto attribute = GetInjectAttribute(self);
    //     if (!attribute) return;
    //     retval = InsertCustomAttribute(retval, attribute);
    // }

    bool Attributes::DerivesFromInjectAttributeBase(System::Type* type) {
        auto klass = il2cpp_functions::class_from_system_type((Il2CppReflectionType*)type);
        static auto ancestor = classof(::Zenject::InjectAttributeBase*);
        return TypeUtil::hasAncestor(klass, ancestor);
    }

    ArrayW<Il2CppObject*> Attributes::InsertCustomAttribute(::ArrayW<Il2CppObject*> arr, Il2CppObject* attribute) {
        auto newArr = ArrayW<Il2CppObject*>(arr.size() + 1);
        memcpy(newArr.begin(), arr.begin(), arr.size() * sizeof(Il2CppObject*));
        newArr[arr.size()] = attribute;
        return newArr;
    }

    System::Attribute* Attributes::GetInjectAttribute(System::Reflection::MemberInfo* member) {
        if (!member) return nullptr;
        // declaring type is the type of the class that has this member
        auto declaringType = member->get_DeclaringType();
        if (!declaringType) return nullptr;
        auto declaringClass = il2cpp_functions::class_from_system_type((Il2CppReflectionType*)declaringType);

        auto attrReg = Lapiz::Attributes::Get(declaringClass, member->get_Name());
        return attrReg ? attrReg->get_attribute() : nullptr;
    }
}
