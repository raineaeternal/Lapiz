#include "objects/RedecoratorRegistration.hpp"

DEFINE_TYPE(Lapiz::Objects, RedecoratorRegistration);

namespace Lapiz::Objects {
    void RedecoratorRegistration::ctor(StringW contract, System::Type* prefabType, System::Type* containerType, int priority, bool chain) {
        minfo = (void*)il2cpp_utils::FindMethodUnsafe(this, "Redecorate", 1);

        _contract = contract;
        _prefabType = prefabType;
        _containerType = containerType;
        _priority = priority;
        _chain = chain;
    }

    Il2CppObject* RedecoratorRegistration::Redecorate_internal(Il2CppObject* value) {
        if (minfo) return il2cpp_utils::RunMethod(this, (MethodInfo*)minfo, value).value_or(value);
        else return value;
    }
}