#pragma once

#include "./affinity.hpp"
#include "custom-types/shared/macros.hpp"
#include "System/Object.hpp"

#include <functional>
#include <string>
#include <string_view>

// A Zenject-resolvable wrapper around an installed affinity hook.
// Bound into a DiContainer by AffinityHookBuilder::install, so dependents sharing that container's scope
// can resolve it (container->ResolveId<HookHandle*>(...)) without needing direct access to the builder.
// TODO: Implement IInitializable and IDisposable so that the hook is automatically uninstalled when the container is disposed.
DECLARE_CLASS_CODEGEN(Lapiz::Affinity, HookHandle, System::Object) {
    DECLARE_CTOR(ctor);

    public:
        modloader::ModInfo const& ModId() const { return _modId; }
        std::string_view HookName() const { return _hookName; }
        bool IsInstalled() const { return static_cast<bool>(_uninstall); }



        void Configure(modloader::ModInfo const& modId, std::string hookName, affinity::AffinityHookInfo hookHandle) {
            _modId = std::move(modId);
            _hookName = std::move(hookName);
            _affinityHookInfo = std::move(hookHandle);
        }

        void Install() {
            // copy
            flamingo::HookInfo hook_info = this->_affinityHookInfo.hook_info_;
            auto install_result = flamingo::Install(std::move(hook_info));
            
            if (!install_result.has_value()) {
                MACRO_LOG(logger_, critical, "Failed to install hook: {} with flamingo: {}", T::name(), install_result.error());
                SAFE_ABORT("Failure installing hook: {}", T::name());
            }
            MACRO_LOG(logger_, info, "Hook: {} installed with flamingo!", T::name());

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
                MACRO_LOG(logger_, error, "Failed to uninstall hook: {} with flamingo due to {}", _hookName, uninstall_result.error());
                return false;
            }
            
            return true;
        }

    private:
        modloader::ModInfo _modId;
        std::string _hookName;
        affinity::AffinityHookInfo _affinityHookInfo;
        std::optional<flamingo::HookHandle> _flamingoHandle;
};
