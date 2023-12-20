#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"

#include "System/IDisposable.hpp"
#include "sabers/LapizSaberFactory.hpp"

#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/ObstacleSaberSparkleEffectManager.hpp"
#include "GlobalNamespace/ObstacleSaberSparkleEffect.hpp"

#include "System/Collections/Generic/Queue_1.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Sabers::Effects, ObstacleSaberSparkleEffectManagerLatch, System::Object, classof(System::IDisposable*),
    DECLARE_PRIVATE_FIELD(GlobalNamespace::ColorManager*, _colorManager);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaberFactory*, _lapizSaberFactory);
    using EarlySabers = System::Collections::Generic::Queue_1<Lapiz::Sabers::LapizSaber*>;
    DECLARE_PRIVATE_FIELD(EarlySabers*, _earlySabers);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::ObstacleSaberSparkleEffectManager*, _obstacleSaberSparkleEffectManager);
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    DECLARE_INSTANCE_METHOD(void, LapizSaberFactory_SaberCreated, Lapiz::Sabers::LapizSaber* lapizSaber);
    DECLARE_PRIVATE_METHOD(void, AddSaber, GlobalNamespace::Saber* saber);
    DECLARE_PRIVATE_METHOD(GlobalNamespace::ObstacleSaberSparkleEffect*, CreateNewObstacleSaberSparkleEffect);

    DECLARE_CTOR(ctor, GlobalNamespace::ColorManager* colorManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory);
    public:
        void ObstacleSaberSparkleEffectManager_Start_Postfix(GlobalNamespace::ObstacleSaberSparkleEffectManager* self);
        void ObstacleSaberSparkleEffectManager_Update_Prefix(GlobalNamespace::ObstacleSaberSparkleEffectManager* self);
        static ObstacleSaberSparkleEffectManagerLatch* get_instance();
    private:
        static ObstacleSaberSparkleEffectManagerLatch* instance;
)
