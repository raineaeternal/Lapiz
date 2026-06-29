#pragma once

#include "../_config.h"
#include "Zenject/InjectAttribute.hpp"
#include "../AttributeRegistration.hpp"

namespace Lapiz::Zenject {
    class LAPIZ_EXPORT InjectAttribute : public Lapiz::Attributes::AttributeRegistration {
        public:
            InjectAttribute() : Lapiz::Attributes::AttributeRegistration() {}
            virtual const char* get_id() const = 0;
            virtual bool optional() const = 0;

            ::System::Attribute* get_attribute() const override {
                if (!attribute) {
                    auto zenjectAttribute = i2c::new_ctor<::Zenject::InjectAttribute*, true>();
                    zenjectAttribute->set_Optional(optional());
                    if (get_id()) {
                        auto id = StringW(get_id());
                        zenjectAttribute->set_Id(static_cast<System::Object*>(id.convert()));
                    }
                    attribute = zenjectAttribute;
                }
                return attribute;
            }
    };
}
