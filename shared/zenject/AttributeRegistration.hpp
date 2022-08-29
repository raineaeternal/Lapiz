#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "Zenject/InjectAttribute.hpp"

namespace Lapiz::Zenject::Attributes {
    class AttributeRegistration;

    /// @brief PreRegister an attribute registration for use with zenject
    /// @param registration the registration to register
    void PreRegister(const AttributeRegistration* registration);

    /// @brief register any current pre registered attribute registrations
    void AutoRegister();

    class AttributeRegistration {
        public:
            AttributeRegistration() { PreRegister(this); }
            virtual Il2CppClass* get_declaringType() const = 0;
            virtual const char* get_name() const = 0;
            virtual const char* get_id() const { return nullptr; }
            virtual bool isMethod() const { return false; }
            virtual bool isField() const { return false; }
            virtual bool optional() const { return false; }
            virtual ::Zenject::InjectAttribute* get_attribute() const;
        private:
            mutable ::Zenject::InjectAttribute* attribute;
    };
}