#pragma once

#include "IInstructor.hpp"
#include "UnityEngine/GameObject.hpp"
#include "Zenject/MonoInstaller.hpp"

namespace Lapiz::Zenject::Internal::Instructors {
    class InstructorManager;
    class MonoInstructor : public IInstructor {
        public:
            void Install(InstallSet* set, ContextBinding* binding) override {
                auto type = reinterpret_cast<System::Type*>(il2cpp_utils::GetSystemType(set->get_installerType()));
                auto installer = reinterpret_cast<::Zenject::MonoInstaller*>(binding->get_context()->get_gameObject()->AddComponent(type));
                if (installer)
                    binding->AddInstaller(installer);
            }
        private:
            MonoInstructor() = default;
            friend class InstructorManager;
    };
}
