#pragma once

#include "custom-types/shared/macros.hpp"
#include "System/Object.hpp"

#include <functional>
#include <string>
#include <string_view>

// A Zenject-resolvable wrapper around an installed affinity hook.
// Bound into a DiContainer by AffinityHookBuilder::install, so dependents sharing that container's scope
// can resolve it (container->ResolveId<HookHandle*>(...)) without needing direct access to the builder.
DECLARE_CLASS_CODEGEN(Lapiz::Affinity, HookHandle, System::Object) {
    DECLARE_CTOR(ctor);

    public:
        std::string_view ModId() const { return _modId; }
        std::string_view HookName() const { return _hookName; }
        bool IsInstalled() const { return static_cast<bool>(_uninstall); }

        // Uninstalls the wrapped hook. Safe to call more than once; returns false if already uninstalled
        // or if the underlying uninstall failed.
        bool Uninstall() {
            if (!_uninstall) return false;
            bool ok = _uninstall();
            _uninstall = nullptr;
            return ok;
        }

        void Configure(std::string modId, std::string hookName, std::function<bool()> uninstall) {
            _modId = std::move(modId);
            _hookName = std::move(hookName);
            _uninstall = std::move(uninstall);
        }

    private:
        std::string _modId;
        std::string _hookName;
        std::function<bool()> _uninstall;
};
