#include "sabers/effects/SaberBurnMarkSparklesLatch.hpp"
#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "UnityEngine/Transform.hpp"

DEFINE_TYPE(Lapiz::Sabers::Effects, SaberBurnMarkSparklesLatch);

namespace Lapiz::Sabers::Effects {
    SaberBurnMarkSparklesLatch* SaberBurnMarkSparklesLatch::instance;
    SaberBurnMarkSparklesLatch* SaberBurnMarkSparklesLatch::get_instance() {
        return instance;
    }

    void SaberBurnMarkSparklesLatch::ctor(Lapiz::Sabers::SaberModelManager* saberModelManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory) {
        INVOKE_CTOR();
        _earlySabers = EarlySabers::New_ctor();
        _lapizSaberFactory = lapizSaberFactory;
        _saberModelManager = saberModelManager;

        _lapizSaberFactory->SaberCreated += {&SaberBurnMarkSparklesLatch::LapizSaberFactory_SaberCreated, this};
    }

    void SaberBurnMarkSparklesLatch::Dispose() {
        instance = nullptr;
        _lapizSaberFactory->SaberCreated -= {&SaberBurnMarkSparklesLatch::LapizSaberFactory_SaberCreated, this};
    }

    void SaberBurnMarkSparklesLatch::LapizSaberFactory_SaberCreated(Lapiz::Sabers::LapizSaber* lapizSaber) {
        if (!_saberBurnMarkSparkles || !_saberBurnMarkSparkles->m_CachedPtr.m_value)
            _earlySabers->Enqueue(lapizSaber);
        else
            AddSaber(lapizSaber->_saber);
    }

    void SaberBurnMarkSparklesLatch::AddSaber(GlobalNamespace::Saber* saber) {
        if (!_saberBurnMarkSparkles || !_saberBurnMarkSparkles->m_CachedPtr.m_value) return;

        _saberBurnMarkSparkles->sabers = TypeUtil::AppendArrayOrDefault(_saberBurnMarkSparkles->sabers, saber);
        _saberBurnMarkSparkles->prevBurnMarkPos = TypeUtil::AppendArrayOrDefault<UnityEngine::Vector3>(_saberBurnMarkSparkles->prevBurnMarkPos);
        _saberBurnMarkSparkles->prevBurnMarkPosValid = TypeUtil::AppendArrayOrDefault<bool>(_saberBurnMarkSparkles->prevBurnMarkPosValid);

        auto newPs = CreateNewBurnMarkParticles();
        _saberBurnMarkSparkles->burnMarksPS = TypeUtil::AppendArrayOrDefault(_saberBurnMarkSparkles->burnMarksPS, newPs);
        _saberBurnMarkSparkles->burnMarksEmissionModules = TypeUtil::AppendArrayOrDefault(_saberBurnMarkSparkles->burnMarksEmissionModules, newPs->get_emission());
    }

    UnityEngine::ParticleSystem* SaberBurnMarkSparklesLatch::CreateNewBurnMarkParticles() {
        static UnityEngine::Quaternion rotation = UnityEngine::Quaternion::Euler({-90.0f, 0.0f, 0.0f});
        auto ps = UnityEngine::Object::Instantiate(_saberBurnMarkSparkles->burnMarksPSPrefab, {0, 0, 0}, rotation, nullptr);
        ps->set_name(fmt::format("SiraUtil | {}", ps->get_name()));
        return ps;
    }

    void SaberBurnMarkSparklesLatch::SaberBurnMarkSparkles_Start_Postfix(GlobalNamespace::SaberBurnMarkSparkles* self) {
        _saberBurnMarkSparkles = self;
        auto iter = _earlySabers->GetEnumerator();
        while (iter.MoveNext()) {
            AddSaber(iter.get_Current()->_saber);
        }
        _earlySabers->Clear();
    }

    void SaberBurnMarkSparklesLatch::SaberBurnMarkSparkles_LateUpdate_Prefix(GlobalNamespace::SaberBurnMarkSparkles* self) {
        _activeSaberIndex = 0;
        _sisterLoopActive = true;
    }

    void SaberBurnMarkSparklesLatch::SaberBurnMarkSparkles_LateUpdate_Postfix(GlobalNamespace::SaberBurnMarkSparkles* self) {
        _activeSaberIndex = 0;
        _sisterLoopActive = false;
    }

    bool SaberBurnMarkSparklesLatch::ColorManager_ColorForSaberType_Prefix(UnityEngine::Color& result) {
        if (!_sisterLoopActive || (!_saberBurnMarkSparkles || !_saberBurnMarkSparkles->m_CachedPtr.m_value))
            return true;

        auto sabers = _saberBurnMarkSparkles->sabers;
        if (_activeSaberIndex >= sabers.size())
            return true;

        result = _saberModelManager->GetPhysicalSaberColor(sabers[_activeSaberIndex++]);
        result.a = 1.0f;
        return false;
    }
}