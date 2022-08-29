#pragma once

#include "filters/IInstallFilter.hpp"
#include "System/Type.hpp"

namespace Lapiz::Zenject::Internal {

    class InstallSet {
        public:
            InstallSet(Il2CppClass* installerType, Filters::IInstallFilter* filter, ArrayW<Il2CppObject*> parameters) : _installerType(installerType), _filter(filter), _parameters(parameters) {}

            auto get_installerType() const { return _installerType; }
            auto get_filter() const { return _filter; }
            auto get_parameters() const { return _parameters; }

        private:
            const Il2CppClass* _installerType;
            const Filters::IInstallFilter* _filter;
            const ArrayW<Il2CppObject*> _parameters;
    };
}
