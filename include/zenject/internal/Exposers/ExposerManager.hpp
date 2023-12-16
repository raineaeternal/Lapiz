#pragma once

#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "../ExposeSet.hpp"
#include "Zenject/Context.hpp"
#include "Zenject/SceneDecoratorContext.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderNonGeneric.hpp"
#include "UnityEngine/MonoBehaviour.hpp"


namespace Lapiz::Zenject::Internal::Exposers {
    class ExposerManager {
        public:
            void Install(Internal::ExposeSet* exposeSet, ::Zenject::Context* ctx, std::set<UnityEngine::MonoBehaviour*> iterlist) {
                ::Zenject::SceneDecoratorContext* sceneDecoratorContext = il2cpp_utils::try_cast<::Zenject::SceneDecoratorContext>(ctx).value_or(nullptr);
                if (!sceneDecoratorContext || !sceneDecoratorContext->m_CachedPtr) {
                    return;
                }

                if (exposeSet->get_locationContractName() != sceneDecoratorContext->_decoratedContractName ||
                    Il2CppString::IsNullOrEmpty(sceneDecoratorContext->_decoratedContractName) ||
                    exposeSet->get_locationContractName().empty()) {
                    return;
                }

                if (iterlist.size() == 0) {
                    ListW<UnityEngine::MonoBehaviour*> injectables(sceneDecoratorContext->_injectableMonoBehaviours);
                    iterlist.insert(injectables.begin(), injectables.end());
                }

                UnityEngine::MonoBehaviour* toExpose = nullptr;
                for (auto il : iterlist) {
                    if (il->klass == exposeSet->get_typeToExpose()) {
                        toExpose = il;
                        break;
                    }
                }

                if (toExpose && toExpose->m_CachedPtr) {
                    auto t = il2cpp_utils::GetSystemType(exposeSet->get_typeToExpose());
                    sceneDecoratorContext->get_Container()->Bind(t)->FromInstance(toExpose)->AsSingle();
                }
                else {
                    WARNING("Could not find {} in {}.", exposeSet->get_typeToExpose()->name, exposeSet->get_locationContractName());
                }
            };
    };
}
