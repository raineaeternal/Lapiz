#pragma once

#include "custom-types/shared/macros.hpp"
#include "Zenject/ITickable.hpp"

#include <functional>
#include <queue>

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Utilities, MainThreadScheduler, Il2CppObject, classof(::Zenject::ITickable*),
    DECLARE_DEFAULT_CTOR();
    DECLARE_OVERRIDE_METHOD(void, Tick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::ITickable::Tick>::get());

    public:
        static void Schedule(std::function<void()> function);

        template<typename T, typename U>
        static void Schedule(T instance, void (U::*method)()) {
            Schedule(std::bind(method, instance));
        }

    private:
        static std::queue<std::function<void()>> scheduled;
        static std::mutex scheduleLock;
);