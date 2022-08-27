#pragma once

#include "IInstallFilter.hpp"

namespace Lapiz::Zenject::Internal::Filters {
    class MultiTypedInstallFilter : public IInstallFilter {
        public:
            MultiTypedInstallFilter(const std::unordered_set<Il2CppClass*>& installerTypes) : _installerTypes(installerTypes) {}
            bool ShouldInstall(ContextBinding* binding) const override {
                auto itr = std::find(_installerTypes.begin(), _installerTypes.end(), binding->get_installerType());
                return itr != _installerTypes.end();
            }
        private:
            const std::unordered_set<Il2CppClass*> _installerTypes;
    };
}