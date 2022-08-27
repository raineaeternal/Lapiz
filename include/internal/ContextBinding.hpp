#pragma once

#include "Zenject/Context.hpp"

namespace Lapiz::Zenject::Internal {
    struct ContextBinding {
            // TODO:
            auto get_installerType() const { return _installerType; }
            auto get_context() const { return context; }
        private:
            ::Zenject::Context* context;
            Il2CppClass* _installerType;
    };
}