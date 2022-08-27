#pragma once

#include "filters/IInstallFilter.hpp"
#include "System/Type.hpp"

namespace Lapiz::Zenject::Internal {

    class InstallSet {
        public:
            InstallSet(Il2CppClass* installerType, Filters::IInstallFilter* filter, ArrayW<Il2CppObject*> parameters) : _installerType(installerType), _filter(filter), _parameters(parameters) {}
        private:
            const Il2CppClass* _installerType;
            const Filters::IInstallFilter* _filter;
            const ArrayW<Il2CppObject*> _parameters;
    };
}
