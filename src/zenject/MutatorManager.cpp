#include "zenject/internal/Mutators/MutatorManager.hpp"

#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"
#include "System/Collections/Generic/List_1.hpp"
#include "System/String.hpp"
#include "Zenject/Context.hpp"
#include "Zenject/SceneDecoratorContext.hpp"
#include "Zenject/Context.hpp"

namespace Lapiz::Zenject::Internal::Mutators {
    void MutatorManager::Install(Internal::MutateSet* mutateSet, ::Zenject::Context* ctx, std::set<UnityEngine::MonoBehaviour*> iterlist) {
        ::Zenject::SceneDecoratorContext* sceneDecoratorContext = i2c::try_cast<::Zenject::SceneDecoratorContext*>(ctx);
        if (!sceneDecoratorContext || !sceneDecoratorContext->m_CachedPtr.m_value) {
            return;
        }

        if (mutateSet->get_locationContractName() != sceneDecoratorContext->_decoratedContractName ||
            System::String::IsNullOrEmpty(sceneDecoratorContext->_decoratedContractName) ||
            mutateSet->get_locationContractName().empty()) {
            return;
        }

        if (iterlist.size() == 0) {
            auto count = sceneDecoratorContext->_injectableMonoBehaviours->Count;
            for (auto i = 0; i < count; i++) {
                iterlist.insert(sceneDecoratorContext->_injectableMonoBehaviours->get_Item(i));
            }
        }

        UnityEngine::MonoBehaviour* toMutate = nullptr;
        for (auto il : iterlist) {
            if (il->klass == mutateSet->get_typeToMutate()) {
                toMutate = il;
                break;
            }
        }

        if (toMutate && toMutate->m_CachedPtr.m_value) {
            mutateSet->get_onMutate()->Invoke(sceneDecoratorContext, toMutate);
        } else {
            WARNING("Could not find {} in {}.", mutateSet->get_typeToMutate()->name, mutateSet->get_locationContractName());
        }
    };
}
