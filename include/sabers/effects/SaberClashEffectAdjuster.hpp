#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

#include "LapizSaberClashChecker.hpp"
#include "sabers/SaberModelManager.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"

#include "Zenject/IInitializable.hpp"
#include "System/IDisposable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Sabers::Effects, SaberClashEffectAdjuster, Il2CppObject, std::vector<Il2CppClass*>({classof(::Zenject::IInitializable*), classof(::System::IDisposable*)}),
    DECLARE_PRIVATE_FIELD(GlobalNamespace::SaberClashEffect*, _saberClashEffect);
    DECLARE_PRIVATE_FIELD(UnityEngine::ParticleSystem*, _glowParticleSystem);
    DECLARE_PRIVATE_FIELD(UnityEngine::ParticleSystem*, _sparkleParticleSystem);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelManager*, _saberModelManager);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::Effects::LapizSaberClashChecker*, _saberClashChecker);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    DECLARE_CTOR(ctor, Lapiz::Sabers::SaberModelManager* saberModelManager, GlobalNamespace::SaberClashChecker* saberClashChecker);
    DECLARE_PRIVATE_METHOD(void, SaberClashChecker_NewSabersClashed, GlobalNamespace::Saber* saberA, GlobalNamespace::Saber* saberB);
    public:
        void SaberClashEffect_Start_Postfix(GlobalNamespace::SaberClashEffect* self);
        static SaberClashEffectAdjuster* get_instance();
    private:
        static SaberClashEffectAdjuster* instance;
)
