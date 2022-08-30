#include "sabers/effects/ObstacleSaberSparkleEffectManagerLatch.hpp"
#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "UnityEngine/Transform.hpp"

DEFINE_TYPE(Lapiz::Sabers::Effects, ObstacleSaberSparkleEffectManagerLatch);

namespace Lapiz::Sabers::Effects {
    ObstacleSaberSparkleEffectManagerLatch* ObstacleSaberSparkleEffectManagerLatch::instance;
    ObstacleSaberSparkleEffectManagerLatch* ObstacleSaberSparkleEffectManagerLatch::get_instance() {
        return instance;
    }

    void ObstacleSaberSparkleEffectManagerLatch::ctor(GlobalNamespace::ColorManager* colorManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory) {
        instance = this;
        _earlySabers = EarlySabers::New_ctor();
        _colorManager = colorManager;
        _lapizSaberFactory = lapizSaberFactory;
        _lapizSaberFactory->SaberCreated += {&ObstacleSaberSparkleEffectManagerLatch::LapizSaberFactory_SaberCreated, this};
    }

    void ObstacleSaberSparkleEffectManagerLatch::Dispose() {
        instance = nullptr;
        _lapizSaberFactory->SaberCreated -= {&ObstacleSaberSparkleEffectManagerLatch::LapizSaberFactory_SaberCreated, this};
    }

    void ObstacleSaberSparkleEffectManagerLatch::LapizSaberFactory_SaberCreated(Lapiz::Sabers::LapizSaber* lapizSaber) {
        if (!_obstacleSaberSparkleEffectManager || !_obstacleSaberSparkleEffectManager->m_CachedPtr.m_value) {
            _earlySabers->Enqueue(lapizSaber);
        } else {
            AddSaber(lapizSaber->_saber);
        }
    }

    void ObstacleSaberSparkleEffectManagerLatch::AddSaber(GlobalNamespace::Saber* saber) {
        if (!_obstacleSaberSparkleEffectManager || !_obstacleSaberSparkleEffectManager->m_CachedPtr.m_value) return;
        
        _obstacleSaberSparkleEffectManager->sabers = TypeUtil::AppendArrayOrDefault(_obstacleSaberSparkleEffectManager->sabers, saber);
        _obstacleSaberSparkleEffectManager->isSystemActive = TypeUtil::AppendArrayOrDefault<bool>(_obstacleSaberSparkleEffectManager->isSystemActive);
        _obstacleSaberSparkleEffectManager->wasSystemActive = TypeUtil::AppendArrayOrDefault<bool>(_obstacleSaberSparkleEffectManager->wasSystemActive);
        _obstacleSaberSparkleEffectManager->burnMarkPositions = TypeUtil::AppendArrayOrDefault<UnityEngine::Vector3>(_obstacleSaberSparkleEffectManager->burnMarkPositions);

        auto effect = CreateNewObstacleSaberSparkleEffect();
        _obstacleSaberSparkleEffectManager->effectsTransforms = TypeUtil::AppendArrayOrDefault(_obstacleSaberSparkleEffectManager->effectsTransforms, effect->get_transform());
        _obstacleSaberSparkleEffectManager->effects = TypeUtil::AppendArrayOrDefault(_obstacleSaberSparkleEffectManager->effects, effect);

    }

    GlobalNamespace::ObstacleSaberSparkleEffect* ObstacleSaberSparkleEffectManagerLatch::CreateNewObstacleSaberSparkleEffect() {
        auto obstacleSaberSparkleEffect = UnityEngine::Object::Instantiate(_obstacleSaberSparkleEffectManager->obstacleSaberSparkleEffectPrefab);
        obstacleSaberSparkleEffect->set_name(fmt::format("Lapiz | {}", obstacleSaberSparkleEffect->get_name()));
        obstacleSaberSparkleEffect->set_color(_colorManager->GetObstacleEffectColor());
        return obstacleSaberSparkleEffect;
    }

    void ObstacleSaberSparkleEffectManagerLatch::ObstacleSaberSparkleEffectManager_Start_Postfix(GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
        _obstacleSaberSparkleEffectManager = self;
        auto iter = _earlySabers->GetEnumerator();
        while(iter.MoveNext()) {
            AddSaber(iter.get_Current()->_saber);
        }
        _earlySabers->Clear();
    }

    void ObstacleSaberSparkleEffectManagerLatch::ObstacleSaberSparkleEffectManager_Update_Prefix(GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
        int isSize = self->isSystemActive.size();
        int wasSize = self->wasSystemActive.size();
        if (isSize > 2 && wasSize > 2 && isSize == wasSize) {
            for (int i = 2; i < isSize; i++) {
                self->wasSystemActive[i] = self->isSystemActive[i];
                self->isSystemActive[i] = false;
            }
        }
    }
}