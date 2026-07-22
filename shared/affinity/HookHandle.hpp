#pragma once

#include "flamingo/shared/hook-data.hpp"
#include "flamingo/shared/hook-metadata.hpp"
#include "flamingo/shared/installer.hpp"

#include "custom-types/shared/macros.hpp"
#include "System/Object.hpp"

#include "Zenject/DiContainer.hpp"

#include "beatsaber-hook/shared/safeptr.hpp"
#include "objects/RedecoratorRegistration.hpp"

#include <functional>
#include <string>
#include <string_view>

namespace Lapiz::Affinity {

    struct AffinityInjectedParameter {
      Il2CppType *type;
      safe_ptr<Il2CppObject*>* value;
    };

    struct AffinityHookInfo {
        Paper::LoggerContext logger_;
        modloader::ModInfo mod_;
        flamingo::HookInfo hook_info_;
        std::optional<AffinityInjectedParameter> injected_parameter_;
    };
}

// A Zenject-resolvable wrapper around an installed affinity hook.
// Bound into a DiContainer by AffinityHookBuilder::install, so dependents sharing that container's scope
// can resolve it (container->ResolveId<HookHandle*>(...)) without needing direct access to the builder.
// TODO: Implement IInitializable and IDisposable so that the hook is automatically uninstalled when the container is disposed.
DECLARE_CLASS_CODEGEN(Lapiz::Affinity, HookHandle, System::Object) {
    DECLARE_CTOR(ctor);

    // Can we somehow instead have this be Il2CppObject* and with the type known before this HookHandle is registered,
    // store this instead of the container so Zenject makes it part of the
    // dependency graph?
    // DECLARE_INJECT_FIELD(System::Object*, objToInject);
    // 
    // 
    DECLARE_INJECT_FIELD(::Zenject::DiContainer*, container);
    // DECLARE_INSTANCE_FIELD(Zenject::DiContainer*, container);
    
    public:
        modloader::ModInfo const& ModId() const { return _modId; }
        std::string_view HookName() const { return _hookName; }
        bool IsInstalled() const { return _flamingoHandle.has_value(); }



        void Configure(modloader::ModInfo const& modId, std::string hookName, AffinityHookInfo hookHandle) {
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
            MACRO_LOG(_affinityHookInfo.logger_, info, "Hook: {} installed with flamingo!",
                      _hookName);

            if (this->_affinityHookInfo.injected_parameter_.has_value()) {
              auto injected_param =
                  this->_affinityHookInfo.injected_parameter_.value();
                System::Type* injected_type = reinterpret_cast<System::Type*>(injected_param.type); 
                // TODO: Is this correct? what about System::Type::GetTypeFromHandle(injected_param.type);
                *injected_param.value = container->Resolve(injected_type);
            }

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
            if (this->_affinityHookInfo.injected_parameter_.has_value()) {
              auto injected_param =
                  this->_affinityHookInfo.injected_parameter_.value();
                // cleanup safe_ptr on uninstall
                injected_param.value->clear();
            }

            return true;
        }

    private:
        modloader::ModInfo _modId;
        std::string _hookName;
        AffinityHookInfo _affinityHookInfo;
        std::optional<flamingo::HookHandle> _flamingoHandle;
};
