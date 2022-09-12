#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

#include "LapizSaberClashChecker.hpp"
#include "sabers/SaberModelManager.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"

#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

#define SaberClashEffectAdjuster_INTERFACES {classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}

___DECLARE_TYPE_WRAPPER_INHERITANCE(Lapiz::Sabers::Effects, SaberClashEffectAdjuster, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "Lapiz::Sabers::Effects", SaberClashEffectAdjuster_INTERFACES, 0, nullptr,
    DECLARE_PRIVATE_FIELD(GlobalNamespace::SaberClashEffect*, _saberClashEffect);
    DECLARE_PRIVATE_FIELD(UnityEngine::ParticleSystem*, _glowParticleSystem);
    DECLARE_PRIVATE_FIELD(UnityEngine::ParticleSystem*, _sparkleParticleSystem);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelManager*, _saberModelManager);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::Effects::LapizSaberClashChecker*, _saberClashChecker);
    
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    DECLARE_CTOR(ctor, Lapiz::Sabers::SaberModelManager* saberModelManager, GlobalNamespace::SaberClashChecker* saberClashChecker);
    DECLARE_PRIVATE_METHOD(void, SaberClashChecker_NewSabersClashed, GlobalNamespace::Saber* saberA, GlobalNamespace::Saber* saberB);
    public:
        void SaberClashEffect_Start_Postfix(GlobalNamespace::SaberClashEffect* self);
        static SaberClashEffectAdjuster* get_instance();
    private:
        static SaberClashEffectAdjuster* instance;
)