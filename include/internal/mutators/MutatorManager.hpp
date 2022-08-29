#pragma once

#include "./utilities/logger.hpp"

#include "../MutateSet.hpp"
#include "Zenject/Context.hpp"
#include "Zenject/SceneDecoratorContext.hpp"
#include "Zenject/SceneDecorator"
#include "UnityEngine/MonoBehaviour.hpp"

namespace Lapiz::Zenject::Internal::Mutators {
    class MutatorManager {
        public:
            void Install(Internal::MutateSet* mutateSet, ::Zenject::Context* ctx, std::set<UnityEngine::MonoBehaviour*> iterlist) {
                Assert->DerivesFromOrEqual<::Zenject::SceneDecoratorContext*>(ctx->GetType());
                ::Zenject::SceneDecoratorContext* sceneDecoratorContext = reinterpret_cast<::Zenject::SceneDecoratorContext*>(ctx);

                if (mutateSet->get_locationContractName() != sceneDecoratorContext->decoratedContractName ||
                Il2CppString::IsNullOrEmpty(sceneDecoratorContext->decoratedContractName) ||
                Il2CppString::IsNullOrWhiteSpace(mutateSet->get_locationContractName())) {
                    return;
                }

                if (iterlist.size() == 0) {
                    std::set<UnityEngine::MonoBehaviour*> injectableList;
                    injectableList.emplace();
                }

                template<typename T>
                void FirstOrDefault(T iterationItems) {
                    for (auto itr : iterationItems) {
                        itr->;
                    }
                }
                // TODO
                auto toMutate = FirstOrDefault<iterlist>([](auto il){
                    // il => il.GetType() == mutateSet.typeToMutate
                    il->klass == mutateSet->get_typeToMutate();
                });

                if (toMutate != nullptr) {
                    mutateSet->get_onMutate().actionObj
                }
                else {
                    WARN("Could not find {} in {}.", mutateSet->get_typeToMutate()->name,
                         mutateSet->get_locationContractName());
                }
            };
    };
}