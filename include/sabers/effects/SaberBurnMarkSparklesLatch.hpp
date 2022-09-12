#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

#include "System/IDisposable.hpp"
#include "sabers/LapizSaberFactory.hpp"
#include "sabers/SaberModelManager.hpp"

#include "GlobalNamespace/SaberBurnMarkSparkles.hpp"

#include "System/Collections/Generic/Queue_1.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Sabers::Effects, SaberBurnMarkSparklesLatch, Il2CppObject, classof(System::IDisposable*),
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaberFactory*, _lapizSaberFactory);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::SaberModelManager*, _saberModelManager);
    using EarlySabers = System::Collections::Generic::Queue_1<Lapiz::Sabers::LapizSaber*>;
    DECLARE_PRIVATE_FIELD(EarlySabers*, _earlySabers);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::SaberBurnMarkSparkles*, _saberBurnMarkSparkles);
    DECLARE_PRIVATE_FIELD(bool, _sisterLoopActive);
    DECLARE_PRIVATE_FIELD(int, _activeSaberIndex);

    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    DECLARE_INSTANCE_METHOD(void, LapizSaberFactory_SaberCreated, Lapiz::Sabers::LapizSaber* lapizSaber);
    DECLARE_PRIVATE_METHOD(void, AddSaber, GlobalNamespace::Saber* saber);
    DECLARE_PRIVATE_METHOD(UnityEngine::ParticleSystem*, CreateNewBurnMarkParticles);

    DECLARE_CTOR(ctor, Lapiz::Sabers::SaberModelManager* saberModelManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory);
    public:
        void SaberBurnMarkSparkles_Start_Postfix(GlobalNamespace::SaberBurnMarkSparkles* self);
        void SaberBurnMarkSparkles_LateUpdate_Prefix(GlobalNamespace::SaberBurnMarkSparkles* self);
        void SaberBurnMarkSparkles_LateUpdate_Postfix(GlobalNamespace::SaberBurnMarkSparkles* self);
        bool ColorManager_ColorForSaberType_Prefix(UnityEngine::Color& result);
        static SaberBurnMarkSparklesLatch* get_instance();
    private:
        static SaberBurnMarkSparklesLatch* instance;
)