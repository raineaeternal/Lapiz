#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "System/SerializableAttribute.hpp"
#include "../AttributeRegistration.hpp"

namespace Lapiz::Objects {
    class SerializableAttribute : public Lapiz::Attributes::AttributeRegistration {
        public:
            SerializableAttribute() : Lapiz::Attributes::AttributeRegistration() {}
            ::System::Attribute* get_attribute() const override {
                if (!attribute) {
                    attribute = ::System::SerializableAttribute::New_ctor<il2cpp_utils::CreationType::Manual>();
                }
                return attribute;
            }
    };
}