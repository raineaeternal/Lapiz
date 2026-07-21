#pragma once

#include "beatsaber-hook/shared/hooking.hpp"
#include "beatsaber-hook/shared/stringw.hpp"
#include "flamingo/shared/hook-data.hpp"
#include "flamingo/shared/hook-metadata.hpp"
#include "flamingo/shared/installer.hpp"

#include "HookHandle.hpp"
#include "System/String.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/IdScopeConcreteIdArgConditionCopyNonLazyBinder.hpp"
#include "Zenject/ScopeConcreteIdArgConditionCopyNonLazyBinder.hpp"
#include "scotland2/shared/loader.hpp"

#include <string>
#include <string_view>
#include <utility>

namespace affinity {

    namespace detail {
        // An affinity hook struct only needs name/addr/hook/trampoline.
        // Unlike i2c::detail::hook_struct, it has no static install_handle/install_priority:
        // both live at runtime in the builder, and the resulting Lapiz::Affinity::HookHandle instead.
        template <typename T>
        concept hook_struct =
            requires {
                { T::name() } -> std::same_as<char const*>;
                { T::trampoline() } -> std::same_as<typename T::func_t*>;
                { T::hook() } -> std::same_as<typename T::func_t>;
            } &&
            (
                requires {
                    { T::addr() } -> std::same_as<void*>;
                } ||
                requires {
                    { T::addr() } -> std::same_as<MethodInfo const*>;
                }
            );
    }
    struct AffinityHookInfo {
        Paper::LoggerContext logger_;
        modloader::ModInfo mod_;
        flamingo::HookInfo hook_info_;
    };

    /// @brief Fluently builds up install priority for an affinity hook, then installs it into a Zenject DiContainer.
    /// Priority is decided at install time (rather than compile time, as with MAKE_HOOK/HOOK_BEFORE/HOOK_AFTER).
    /// On a successful install, the resulting Lapiz::Affinity::HookHandle is bound into the container
    /// (BindInstance, WithId(mod.id:hook_name), AsCached), so dependents sharing that container's scope can
    /// resolve it later (container->ResolveId<Lapiz::Affinity::HookHandle*>(id)) without needing this builder.
    template <detail::hook_struct T, ::i2c::detail::is_logger L>
    class AffinityHookBuilder {
    public:
        AffinityHookBuilder(L logger, const modloader::ModInfo& mod, void* addr = nullptr)
            : logger_(std::move(logger)), mod_(mod), addr_(addr) {}

        /// @brief Requires this hook be installed before (called earlier than) every hook registered under mod_id.
        AffinityHookBuilder& before(std::string_view mod_id) {
            priority_.befores.emplace_back(std::string(mod_id));
            return *this;
        }

        /// @brief Requires this hook be installed after (called later than) every hook registered under mod_id.
        AffinityHookBuilder& after(std::string_view mod_id) {
            priority_.afters.emplace_back(std::string(mod_id));
            return *this;
        }

        /// @brief Marks this hook as the final hook, closest to the original function.
        AffinityHookBuilder& final() {
            priority_.is_final = true;
            return *this;
        }

        /// @brief Installs the hook, then binds the resulting Lapiz::Affinity::HookHandle into container,
        /// keyed by "mod.id:hook_name" so dependents in the same container scope can resolve it by that id.
        Lapiz::Affinity::HookHandle* install(::Zenject::DiContainer* container) {
            void* addr = addr_;
            if (!addr) {
                auto info_or_addr = T::addr();
                if constexpr (std::is_same_v<decltype(info_or_addr), void*>) {
                    addr = info_or_addr;
                } else if (info_or_addr) {
                    addr = reinterpret_cast<void*>(info_or_addr->methodPointer);
                } else {
                    MACRO_LOG(logger_, critical, "Attempting to install hook: {}, but method could not be found!", T::name());
                    SAFE_ABORT("Failure installing hook: {}", T::name());
                }
            }
            if (!addr) {
                MACRO_LOG(logger_, critical, "Attempting to install hook: {} to invalid destination!", T::name());
                SAFE_ABORT("Failure installing hook: {}", T::name());
            }
            auto flamingo_info = flamingo::HookInfo{
                reinterpret_cast<void *>(T::hook()),
                addr,
                reinterpret_cast<void **>(T::trampoline()),
                flamingo::HookNameMetadata{.name = T::name(),
                                           .namespaze = mod_.id},
                std::move(priority_),
            };
            auto affinityHook = AffinityHookInfo{.logger_ = logger_, .mod_ = mod_, .hook_info_ = std::move(flamingo_info)};
            auto* handle = ::Lapiz::Affinity::HookHandle::New_ctor();
            handle->Configure(mod_.id, T::name(), affinityHook);

            auto id = static_cast<System::String*>(::StringW(mod_.id + ":" + T::name()));
            container->BindInstance(handle)->WithId(static_cast<System::Object*>(id))->AsCached();
            return handle;
        }

    private:
        L logger_;
        modloader::ModInfo mod_;
        void* addr_;
        flamingo::HookPriority priority_{};
    };

    template <detail::hook_struct T, typename L>
        requires ::i2c::detail::is_logger<std::decay_t<L>>
    auto make_affinity_hook_builder(L&& logger, const modloader::ModInfo& mod, void* addr = nullptr) {
        return AffinityHookBuilder<T, std::decay_t<L>>(std::forward<L>(logger), mod, addr);
    }

}  // namespace affinity
