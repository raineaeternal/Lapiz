#include "zenject/AttributeRegistration_internal.hpp"

#include <queue>

namespace Lapiz::Zenject::Attributes {
    static std::queue<const AttributeRegistration*> pending;
    static std::mutex registering;

    static std::unordered_map<Il2CppClass*, std::set<const AttributeRegistration*>> registrations;

    void PreRegister(const AttributeRegistration* registration) {
        registering.lock();
        pending.push(registration);
        registering.unlock();
    }

    void AutoRegister() {
        registering.lock();
        while (!pending.empty()) {
            auto registration = pending.front();
            pending.pop();

            auto klass = registration->get_declaringType();
            auto klassItr = registrations.find(klass);
            if (klassItr != registrations.end()) {
                klassItr->second.emplace(registration);
            } else {
                registrations.emplace(klass, std::set<const AttributeRegistration*>{}).first->second.emplace(registration);
            }
        }
        registering.unlock();
    }

    const AttributeRegistration* Get(Il2CppClass* klass, StringW name) {
        auto klassItr = registrations.find(klass);
        if (klassItr != registrations.end()) {
            auto& set = klassItr->second;
            auto regItr = std::find_if(set.begin(), set.end(), [name](auto reg){ return reg->get_name() == name; });
            if (regItr != set.end()) {
                return *regItr;
            }
        }

        return nullptr;
    }

    ::Zenject::InjectAttribute* AttributeRegistration::get_attribute() const {
        if (!attribute) {
            attribute = ::Zenject::InjectAttribute::New_ctor<il2cpp_utils::CreationType::Manual>();
            attribute->set_Optional(optional());
            if (get_id()) {
                attribute->set_Id(StringW(get_id()));
            }
        }
        return attribute;
    }
}