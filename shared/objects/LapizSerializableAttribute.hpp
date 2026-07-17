#pragma once

#include "../_config.h"
#include "System/SerializableAttribute.hpp"
#include "../AttributeRegistration.hpp"

namespace Lapiz::Objects {
    class LAPIZ_EXPORT SerializableAttribute : public Lapiz::Attributes::AttributeRegistration {
        public:
            SerializableAttribute() : Lapiz::Attributes::AttributeRegistration() {}
            ::System::Attribute* get_attribute() const override {
                if (!attribute) {
                    attribute = i2c::new_ctor<::System::SerializableAttribute*, true>();
                }
                return attribute;
            }
    };
}
