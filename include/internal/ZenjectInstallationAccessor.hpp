#pragma once

#include "Zenject/MonoInstaller.hpp"
#include "Zenject/InstallerBase.hpp"
#include "System/Type.hpp"

namespace Lapiz::Zenject::Internal {
    class ZenjectInstallationAccessor {
        public:
            ZenjectInstallationAccessor(ListWrapper<::Zenject::InstallerBase*> normalInstallers, ListWrapper<System::Type*> normalInstallerTypes, ListWrapper<::Zenject::MonoInstaller*> installers) 
            : _installers(installers), _normalInstallers(normalInstallers), _normalInstallerTypes(normalInstallerTypes) {};
        
            auto get_installers() const { return _installers; }
            auto get_normalInstallers() const { return _normalInstallers; }
            auto get_normalInstallerTypes() const { return _normalInstallerTypes; }
        
        private:
            ListWrapper<::Zenject::MonoInstaller*> _installers;
            ListWrapper<::Zenject::InstallerBase*> _normalInstallers;
            ListWrapper<System::Type*> _normalInstallerTypes;
    };
}