#pragma once

#include "custom-types/shared/macros.hpp"
#include "System/Object.hpp"
#include "Zenject/ITickable.hpp"
#include "Zenject/IInitializable.hpp"

#include <functional>
#include <queue>
#include <thread>

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Utilities, MainThreadScheduler, System::Object, ::Zenject::IInitializable* ,::Zenject::ITickable*) {
    DECLARE_DEFAULT_CTOR();
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Tick, &::Zenject::ITickable::Tick);

    public:
        static void Schedule(std::function<void()> function);

        template<typename T, typename U>
        static void Schedule(T instance, void (U::*method)()) {
            Schedule(std::bind(method, instance));
        }

    private:
        static std::thread::id Thread;
        static std::queue<std::function<void()>> scheduled;
        static std::mutex scheduleLock;
};
