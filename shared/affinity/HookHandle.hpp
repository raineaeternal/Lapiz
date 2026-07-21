#pragma once

#include "beatsaber-hook/shared/hooking.hpp"
#include "flamingo/shared/hook-data.hpp"
#include "flamingo/shared/hook-metadata.hpp"
#include "flamingo/shared/installer.hpp"

#include "custom-types/shared/macros.hpp"
#include "System/Object.hpp"
#include "paper2_scotland2/shared/logger.hpp"
#include "scotland2/shared/loader.hpp"

#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#include <functional>
#include <optional>
#include <string>
#include <string_view>

namespace Lapiz::Affinity {
    struct AffinityHookInfo {
        Paper::LoggerContext logger_;
        modloader::ModInfo mod_;
        flamingo::HookInfo hook_info_;
    };
}

// A Zenject-resolvable wrapper around an installed affinity hook.
// Bound into a DiContainer by AffinityHookBuilder::install, so dependents sharing that container's scope
// can resolve it (container->ResolveId<HookHandle*>(...)) without needing direct access to the builder.
// Implements IInitializable/IDisposable so the hook installs when Zenject resolves this instance as a
// container root, and uninstalls automatically when the owning container is disposed.
DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Affinity, HookHandle, System::Object, ::Zenject::IInitializable*, ::System::IDisposable*) {
    DECLARE_CTOR(ctor);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &System::IDisposable::Dispose);

    public:
        modloader::ModInfo const& ModId() const { return _modId; }
        std::string_view HookName() const { return _hookName; }
        bool IsInstalled() const { return _flamingoHandle.has_value(); }

        void Configure(modloader::ModInfo const& modId, std::string hookName, Lapiz::Affinity::AffinityHookInfo hookHandle) {
            _modId = std::move(modId);
            _hookName = std::move(hookName);
            _affinityHookInfo = std::move(hookHandle);
        }

        void Install() {
            // copy
            flamingo::HookInfo hook_info = this->_affinityHookInfo.hook_info_;
            auto install_result = flamingo::Install(std::move(hook_info));
            
            if (!install_result.has_value()) {
                MACRO_LOG(_affinityHookInfo.logger_, critical, "Failed to install hook: {} with flamingo: {}", _hookName, install_result.error());
                SAFE_ABORT("Failure installing hook: {}", _hookName);
            }
            MACRO_LOG(_affinityHookInfo.logger_, info, "Hook: {} installed with flamingo!", _hookName);

            _flamingoHandle = install_result.value().returned_handle;
        }

        // Uninstalls the wrapped hook. Safe to call more than once; returns false if already uninstalled
        // or if the underlying uninstall failed.
        bool Uninstall() {
            if (!_flamingoHandle.has_value()) {
                return false;
            }
          
            auto uninstall_result = flamingo::Uninstall(_flamingoHandle.value());
            _flamingoHandle.reset();
            if (!uninstall_result.has_value()) {
                MACRO_LOG(_affinityHookInfo.logger_, error, "Failed to uninstall hook: {} with flamingo due to {}", _hookName, uninstall_result.error());
                return false;
            }
            
            return true;
        }

    private:
        modloader::ModInfo _modId;
        std::string _hookName;
        Lapiz::Affinity::AffinityHookInfo _affinityHookInfo;
        std::optional<flamingo::HookHandle> _flamingoHandle;
};
