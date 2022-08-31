#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "System/Attribute.hpp"

namespace Lapiz::Attributes {
    class AttributeRegistration;

    /// @brief PreRegister an attribute registration
    /// @param registration the registration to register
    void PreRegister(const AttributeRegistration* registration);

    /// @brief register any current pre registered attribute registrations
    void AutoRegister();

    class AttributeRegistration {
        public:
            AttributeRegistration() { PreRegister(this); }
            virtual Il2CppClass* get_declaringType() const = 0;
            virtual const char* get_name() const = 0;
            virtual ::System::Attribute* get_attribute() const = 0;
            virtual bool isMethod() const { return false; }
            virtual bool isField() const { return false; }
        protected:
            mutable ::System::Attribute* attribute;
    };
}