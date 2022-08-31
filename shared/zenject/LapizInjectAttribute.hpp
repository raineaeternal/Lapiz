#pragma once

#include "beatsaber-hook/shared/utils/typedefs.h"
#include "Zenject/InjectAttribute.hpp"
#include "../AttributeRegistration.hpp"

namespace Lapiz::Zenject {
    class InjectAttribute : public Lapiz::Attributes::AttributeRegistration {
        public:
            InjectAttribute() : Lapiz::Attributes::AttributeRegistration() {}
            virtual const char* get_id() const = 0;
            virtual bool optional() const = 0;

            ::System::Attribute* get_attribute() const override {
                if (!attribute) {
                    auto zenjectAttribute = ::Zenject::InjectAttribute::New_ctor<il2cpp_utils::CreationType::Manual>();
                    zenjectAttribute->set_Optional(optional());
                    if (get_id()) {
                        zenjectAttribute->set_Id(StringW(get_id()));
                    }
                    attribute = zenjectAttribute;
                }
                return attribute;
            }
    };
}