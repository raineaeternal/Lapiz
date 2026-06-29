#include "objects/RedecoratorRegistration.hpp"

DEFINE_TYPE(Lapiz::Objects, RedecoratorRegistration);

namespace Lapiz::Objects {
    void RedecoratorRegistration::ctor(StringW contract, System::Type* prefabType, System::Type* containerType, int priority, bool chain) {
        minfo = const_cast<void*>(static_cast<const void*>(i2c::find_method(klass, {"Redecorate", 1})));

        _contract = contract;
        _prefabType = prefabType;
        _containerType = containerType;
        _priority = priority;
        _chain = chain;
    }

    System::Object* RedecoratorRegistration::Redecorate_internal(System::Object* value) {
        if (minfo) return i2c::run_method<System::Object*>(this, (MethodInfo*) minfo, value);
        else return value;
    }

    bool RedecoratorRegistration::get_chain() { return _chain; }
    int RedecoratorRegistration::get_priority() { return _priority; }
    StringW RedecoratorRegistration::get_contract() { return _contract; }
    System::Type* RedecoratorRegistration::get_prefabType() { return _prefabType; }
    System::Type* RedecoratorRegistration::get_containerType() { return _containerType; }
}
