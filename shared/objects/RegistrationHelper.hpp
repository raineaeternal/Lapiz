#pragma once

#include "TemplateRedecoratorRegistration.hpp"

namespace Lapiz::Objects {
    namespace {
        template<size_t sz>
        struct StringLiteral {
            constexpr StringLiteral(const char (&str)[sz]) : v(str) {};
            constexpr operator std::string_view() const { return {v, sz}; };
            const char v[sz];
        };
    }

    template<const StringLiteral str, typename TPrefab, typename TParent>
    struct Registration {
        Registration(std::function<TPrefab(TPrefab)> redecorateCall, int priority = 0, bool chain = true) {
            v = ::Lapiz::Objects::TemplateRedecoratorRegistration::Make<TPrefab, TParent>(str, redecorateCall, priority, chain);
        }

        explicit Registration(void* v) : v(v) {};
        explicit operator void*() const { return v; };

        operator TemplateRedecoratorRegistration* () const {
            return v;   
        }
        private:
            TemplateRedecoratorRegistration* v;
    };
}