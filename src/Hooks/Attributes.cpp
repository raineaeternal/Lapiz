#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "Hooks/Attributes.hpp"
#include "Zenject/InjectAttributeBase.hpp"
#include "AttributeRegistration_internal.hpp"

// TODO: figure out where custom attributes are retreived, and inject our own
MAKE_AUTO_HOOK_MATCH(Attribute_GetCustomAttributes,
        static_cast<::ArrayW<::System::Attribute*> (*)(::System::Reflection::MemberInfo*, ::System::Type*, bool)>(&System::Attribute::GetCustomAttributes),
        ArrayW<::System::Attribute*>,
        System::Reflection::MemberInfo* element,
        System::Type* attributeType,
        bool inherit
    ) {
    auto retVal = Attribute_GetCustomAttributes(element, attributeType, inherit);

    if (auto v = il2cpp_utils::try_cast<System::Reflection::FieldInfo>(element); v.has_value()) {
        Lapiz::Zenject::Internal::Attributes::FieldInfo_GetCustomAttributes(retVal, *v, attributeType, inherit);
    } else if (auto v = il2cpp_utils::try_cast<System::Reflection::MethodInfo>(element); v.has_value()) {
        Lapiz::Zenject::Internal::Attributes::MethodInfo_GetCustomAttributes(retVal, *v, attributeType, inherit);
    }

    return retVal;
}

namespace Lapiz::Zenject::Internal {
    void Attributes::FieldInfo_GetCustomAttributes(ArrayW<::System::Attribute*>& retval, System::Reflection::FieldInfo* self, System::Type* attributeType, bool inherit) {
        if (!DerivesFromInjectAttributeBase(attributeType)) return;
        auto attribute = GetInjectAttribute(self);
        if (!attribute) return;
        retval = InsertCustomAttribute(retval, attribute);
    }

    void Attributes::MethodInfo_GetCustomAttributes(ArrayW<::System::Attribute*>& retval, System::Reflection::MethodInfo* self, System::Type* attributeType, bool inherit) {
        if (!DerivesFromInjectAttributeBase(attributeType)) return;
        auto attribute = GetInjectAttribute(self);
        if (!attribute) return;
        retval = InsertCustomAttribute(retval, attribute);
    }

    bool Attributes::DerivesFromInjectAttributeBase(System::Type* type) {
        auto klass = il2cpp_functions::class_from_system_type((Il2CppReflectionType*)type);
        static auto ancestor = classof(::Zenject::InjectAttributeBase*);
        return TypeUtil::hasAncestor(klass, ancestor);
    }

    ArrayW<System::Attribute*> Attributes::InsertCustomAttribute(::ArrayW<System::Attribute*> arr, System::Attribute* attribute) {
        auto newArr = ArrayW<System::Attribute*>(arr.size() + 1);
        memcpy(newArr.begin(), arr.begin(), arr.size() * sizeof(System::Attribute*));
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
