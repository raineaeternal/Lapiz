#pragma once
#include "Zenject/Context.hpp"

#include "zenject/internal/ContextBinding.hpp"
#include "Zenject/Context.hpp"
#include "Zenject/InstallerBase.hpp"
#include "Zenject/ScriptableObjectInstaller.hpp"
#include "Zenject/MonoInstaller.hpp"
#include "System/Type.hpp"

namespace Lapiz::Zenject::Internal {
    class ContextDecorator {
        public:
            static void Context_InstallInstallers_Prefix(::Zenject::Context* self, ListWrapper<::Zenject::InstallerBase*> normalInstallers, ListWrapper<::System::Type*> normalInstallerTypes, ListWrapper<::Zenject::ScriptableObjectInstaller*> scriptableObjectInstallers, ListWrapper<::Zenject::MonoInstaller*> installers, ListWrapper<::Zenject::MonoInstaller*> installerPrefabs);
            static UnorderedEventCallback<::Zenject::Context*, ContextBindingSet> contextInstalling;
        private:
            static std::set<::Zenject::Context*> recentlyInstalledDecorators;
    };
}