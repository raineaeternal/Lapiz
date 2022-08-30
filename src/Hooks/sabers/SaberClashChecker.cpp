#include "utilities/hooking.hpp"

#include "sabers/effects/LapizSaberClashChecker.hpp"
#include "GlobalNamespace/SaberClashChecker.hpp"
#include "UnityEngine/Vector3.hpp"

#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "GlobalNamespace/TutorialInstaller.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/BindStatement.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

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

MAKE_AUTO_HOOK_MATCH(GameplayCoreInstaller_InstallBindings, &GlobalNamespace::GameplayCoreInstaller::InstallBindings, void, GlobalNamespace::GameplayCoreInstaller* self) {
    GameplayCoreInstaller_InstallBindings(self);
    auto container = self->get_Container();
    container->Unbind<GlobalNamespace::SaberClashChecker*>();
    auto typeArr = ArrayW<System::Type*>(1);
    static auto klass = classof(Lapiz::Sabers::Effects::LapizSaberClashChecker*);
    typeArr[0] = il2cpp_utils::GetSystemType(klass);
    container->Bind<GlobalNamespace::SaberClashChecker*>()->To(typeArr)->AsSingle();
}

MAKE_AUTO_HOOK_MATCH(TutorialInstaller_InstallBindings, &GlobalNamespace::TutorialInstaller::InstallBindings, void, GlobalNamespace::TutorialInstaller* self) {
    TutorialInstaller_InstallBindings(self);
    auto container = self->get_Container();
    container->Unbind<GlobalNamespace::SaberClashChecker*>();
    auto typeArr = ArrayW<System::Type*>(1);
    static auto klass = classof(Lapiz::Sabers::Effects::LapizSaberClashChecker*);
    typeArr[0] = il2cpp_utils::GetSystemType(klass);
    container->Bind<GlobalNamespace::SaberClashChecker*>()->To(typeArr)->AsSingle();
}

/*
// TODO: test this scuffed hook which replaces the base game saberclash checker with ours
template<>
struct ::il2cpp_utils::il2cpp_type_check::MetadataGetter<static_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>* (::Zenject::DiContainer::*)(::Zenject::BindStatement*)>(&Zenject::DiContainer::Bind)> {
    static const MethodInfo* get() {
        static auto* contractType = &il2cpp_utils::GetClassFromName("Zenject", "BindStatement")->byval_arg;
        static auto* genericParam = classof(::GlobalNamespace::SaberClashChecker*);
        static auto* baseMinfo = ::il2cpp_utils::FindMethod(classof(Zenject::DiContainer*), "Bind", std::vector<Il2CppClass*>{genericParam}, ::std::vector<const Il2CppType*>{contractType});
        return il2cpp_utils::MakeGenericMethod(baseMinfo, std::vector<Il2CppClass*>{genericParam});
    }
};

struct Hook_DiContainer_Bind                                                                                                                            
{                                                                                                                                              
    using funcType = ::Zenject::ConcreteIdBinderGeneric_1<GlobalNamespace::SaberClashChecker*>* (*)(::Zenject::DiContainer* self, ::Zenject::BindStatement* bindStatement, const MethodInfo* minfo);                                                                                                  
    static_assert(std::is_same_v<funcType, ::Hooking::InternalMethodCheck<decltype(static_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>* (::Zenject::DiContainer::*)(::Zenject::BindStatement*)>(&Zenject::DiContainer::Bind))>::funcType>, "Hook method signature does not match!");
    constexpr static const char* name() { return "DiContainer_Bind"; }                                                                                     
    static const MethodInfo* getInfo() { return ::il2cpp_utils::il2cpp_type_check::MetadataGetter<static_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>* (::Zenject::DiContainer::*)(::Zenject::BindStatement*)>(&Zenject::DiContainer::Bind)>::get(); }                              
    static funcType* trampoline() { return &DiContainer_Bind; }                                                                                           
    static inline ::Zenject::ConcreteIdBinderGeneric_1<GlobalNamespace::SaberClashChecker*>* (*DiContainer_Bind)(::Zenject::DiContainer* self, ::Zenject::BindStatement* bindStatement) = nullptr;                                                                                      
    static funcType hook() { return hook_DiContainer_Bind; }                                                                                            
    static ::Zenject::ConcreteIdBinderGeneric_1<GlobalNamespace::SaberClashChecker*>* hook_DiContainer_Bind(::Zenject::DiContainer* self, ::Zenject::BindStatement* bindStatement, const MethodInfo* minfo);                                                                                                   
};                                                                                                                                             
AUTO_INSTALL_ORIG(DiContainer_Bind)                                                                                                                       
::Zenject::ConcreteIdBinderGeneric_1<GlobalNamespace::SaberClashChecker*>* Hook_DiContainer_Bind::hook_DiContainer_Bind(::Zenject::DiContainer* self, ::Zenject::BindStatement* bindStatement, const MethodInfo* minfo) {
    return reinterpret_cast<::Zenject::ConcreteIdBinderGeneric_1<::GlobalNamespace::SaberClashChecker*>*>(self->Bind<Lapiz::Sabers::Effects::LapizSaberClashChecker*>(bindStatement));
}
*/