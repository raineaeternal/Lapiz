#pragma once

#include "IInstructor.hpp"

#include "MonoInstructor.hpp"
#include "ParameterizedInstructor.hpp"
#include "TypedInstructor.hpp"

#include "UnityEngine/Component.hpp"
#include "Zenject/MonoInstallerBase.hpp"

namespace Lapiz::Zenject {
    class ZenjectManager;
    namespace Internal::Instructors {
        class InstructorManager {
            public:
                IInstructor* InstructorForSet(InstallSet* set) {
                    auto installerType = set->get_installerType();

                    if (!hasAncestor<UnityEngine::Component*>(installerType) && set->get_parameters()) return _parameterizedInstructor;
                    if (hasAncestor<::Zenject::MonoInstallerBase*>(installerType)) return _monoInstructor;
                    if (hasAncestor<UnityEngine::Component*>(installerType)) return _typedInstructor;

                    return nullptr;
                }
            private:
                friend class ::Lapiz::Zenject::ZenjectManager;
                InstructorManager() {
                    _monoInstructor = new MonoInstructor();
                    _parameterizedInstructor = new ParameterizedInstructor();
                    _typedInstructor = new TypedInstructor();
                }

                template<typename T>
                requires(std::is_convertible_v<T, Il2CppObject*>)
                static bool hasAncestor(const Il2CppClass* instance) {
                    return hasAncestor(instance, classof(T));
                }

                static bool hasAncestor(const Il2CppClass* instance, const Il2CppClass* ancestor) {
                    if (!instance) return false;
                    if (instance == ancestor) return true;
                    return hasAncestor(instance->parent, ancestor);
                }

                IInstructor* _monoInstructor;
                IInstructor* _typedInstructor;
                IInstructor* _parameterizedInstructor;
        };
    }
}