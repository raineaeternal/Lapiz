#pragma once

#include "System/Action.hpp"
#include "System/Object.hpp"

#include "Zenject/SceneDecoratorContext.hpp"

namespace Lapiz::Zenject::Internal {
    class ZenjectDelegate {
    public:
        std::function<void(::Zenject::SceneDecoratorContext*)> actionObj;

        template<typename T, typename U>
        ZenjectDelegate Wrap(std::function<void(T, U)> callback) {
            actionObj = [callback](::Zenject::SceneDecoratorContext* ctx, Il2CppObject* obj) {
                callback(reinterpret_cast<T>(ctx), reinterpret_cast<U>(obj));
            };
        }
    };
}