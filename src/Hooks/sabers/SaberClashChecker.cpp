#include "utilities/hooking.hpp"

#include "sabers/effects/LapizSaberClashChecker.hpp"
#include "GlobalNamespace/SaberClashChecker.hpp"
#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/TutorialInstaller.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/BindStatement.hpp"

MAKE_AUTO_HOOK_ORIG_MATCH(SaberClashChecker_AreSabersClashing, &GlobalNamespace::SaberClashChecker::AreSabersClashing, bool, GlobalNamespace::SaberClashChecker* self, ByRef<::UnityEngine::Vector3> clashingPoint) {
    static auto lapizCheckerKlass = classof(Lapiz::Sabers::Effects::LapizSaberClashChecker*);
    // if this object is of our own klass, so we can override the method call
    if (self->klass == lapizCheckerKlass) {
        auto customChecker = reinterpret_cast<Lapiz::Sabers::Effects::LapizSaberClashChecker*>(self);
        bool result = false;
        if (!customChecker->SaberClashChecker_AreSabersClashing_override(clashingPoint.heldRef, result)) 
            result = SaberClashChecker_AreSabersClashing(self, clashingPoint);
        return result;
    } else {
        return SaberClashChecker_AreSabersClashing(self, clashingPoint);
    }
}

// TODO: test this scuffed hook which replaces the base game saberclash checker with ours
template<>
struct ::il2cpp_utils::il2cpp_type_check::MetadataGetter<static_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>* (::Zenject::DiContainer::*)(::Zenject::BindStatement*)>(&Zenject::DiContainer::Bind)> {
    static const MethodInfo* get() {
        static auto* contractTypes = &il2cpp_functions::array_class_get(::il2cpp_utils::GetClassFromName("Zenject", "BindStatement"), 1)->byval_arg;
        static auto* genericParam = classof(::GlobalNamespace::SaberClashChecker*);
        return ::il2cpp_utils::FindMethod(classof(Zenject::DiContainer*), "Bind", std::vector<Il2CppClass*>{genericParam}, ::std::vector<const Il2CppType*>{contractTypes});
    }
};

MAKE_AUTO_HOOK_ORIG_MATCH(DiContainer_Bind, static_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>* (::Zenject::DiContainer::*)(::Zenject::BindStatement*)>(&Zenject::DiContainer::Bind), ::Zenject::ConcreteIdBinderGeneric_1<GlobalNamespace::SaberClashChecker*>*, ::Zenject::DiContainer* self, ::Zenject::BindStatement* bindStatement) {
    return reinterpret_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>*>(self->Bind<Lapiz::Sabers::Effects::LapizSaberClashChecker*>(bindStatement));
}
