#pragma once

#include "System/Action.hpp"
#include "System/Object.hpp"

#include "Zenject/SceneDecoratorContext.hpp"

namespace Lapiz::Zenject::Internal {
    class ZenjectDelegate {
        std::function<void(::Zenject::SceneDecoratorContext*, Il2CppObject* obj)> actionObj;
    public:
        template<typename T>
        requires(std::is_convertible_v<T, ::Zenject::SceneDecoratorContext*>)
        ZenjectDelegate* Wrap(std::function<void(T, Il2CppObject*)> callback) { 
            actionObj = [callback](::Zenject::SceneDecoratorContext* ctx, Il2CppObject* obj) {
                callback(reinterpret_cast<T>(ctx), obj);
            };

            return this;
        }
        
        template<typename T, typename U>
        requires(std::is_convertible_v<T, ::Zenject::SceneDecoratorContext*> && std::is_convertible_v<U, Il2CppObject*> && !std::is_same_v<U, Il2CppObject*>)
        ZenjectDelegate* Wrap(std::function<void(T, U)> callback) {
            
            actionObj = [callback](::Zenject::SceneDecoratorContext* ctx, Il2CppObject* obj) {
                callback(reinterpret_cast<T>(ctx), reinterpret_cast<U>(obj));
            };

            return this;
        }

        void Invoke(::Zenject::SceneDecoratorContext* ctx, Il2CppObject* obj) const {
            if (actionObj) {
                actionObj(ctx, obj);
            }
        }
    };
}