#include "sabers/effects/SaberBurnMarkAreaLatch.hpp"
#include "utilities/logging.hpp"
#include "utilities/typeutil.hpp"

#include "UnityEngine/HideFlags.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Transform.hpp"

DEFINE_TYPE(Lapiz::Sabers::Effects, SaberBurnMarkAreaLatch);

namespace Lapiz::Sabers::Effects {
    SaberBurnMarkAreaLatch* SaberBurnMarkAreaLatch::instance;
    SaberBurnMarkAreaLatch* SaberBurnMarkAreaLatch::get_instance() {
        return instance;
    }

    void SaberBurnMarkAreaLatch::ctor(Lapiz::Sabers::SaberModelManager* saberModelManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory) {
        instance = this;
        _earlySabers = EarlySabers::New_ctor();
        _lineFactoryIncrement = 2;
        _lapizSaberFactory = lapizSaberFactory;
        _saberModelManager = saberModelManager;
        _lapizSaberFactory->SaberCreated += {&SaberBurnMarkAreaLatch::LapizSaberFactory_SaberCreated, this};
        _saberModelManager->ColorUpdated += {&SaberBurnMarkAreaLatch::ColorUpdated, this};
        _lapizSaberFactory->ColorUpdated += {&SaberBurnMarkAreaLatch::ColorUpdated, this};
    }
    
    void SaberBurnMarkAreaLatch::Dispose() {
        instance = nullptr;
        _lapizSaberFactory->SaberCreated -= {&SaberBurnMarkAreaLatch::LapizSaberFactory_SaberCreated, this};
        _saberModelManager->ColorUpdated -= {&SaberBurnMarkAreaLatch::ColorUpdated, this};
        _lapizSaberFactory->ColorUpdated -= {&SaberBurnMarkAreaLatch::ColorUpdated, this};
    }

    void SaberBurnMarkAreaLatch::LapizSaberFactory_SaberCreated(Lapiz::Sabers::LapizSaber* lapizSaber) {
        if (!_saberBurnMarkArea || !_saberBurnMarkArea->m_CachedPtr.m_value)
            _earlySabers->Enqueue(lapizSaber);
        else
            AddSaber(lapizSaber->_saber);
    }

    void SaberBurnMarkAreaLatch::ColorUpdated(GlobalNamespace::Saber* saber, UnityEngine::Color color) {
        if (!_saberBurnMarkArea || !_saberBurnMarkArea->m_CachedPtr.m_value) return;

        int index = _saberBurnMarkArea->sabers.IndexOf(saber);
        
        if (index == -1)
            return;
        float h, s, _;
        color.a = 1.0f;
        UnityEngine::Color::RGBToHSV(color, byref(h), byref(s), byref(_));
        color = UnityEngine::Color::HSVToRGB(h, s, 1.0f);

        auto line = _saberBurnMarkArea->lineRenderers[index];
        line->set_startColor(color);
        line->set_endColor(color);
    }

    void SaberBurnMarkAreaLatch::AddSaber(GlobalNamespace::Saber* saber) {
        if (!_saberBurnMarkArea || !_saberBurnMarkArea->m_CachedPtr.m_value) return;

        _saberBurnMarkArea->sabers = TypeUtil::AppendArrayOrDefault(_saberBurnMarkArea->sabers, saber);
        _saberBurnMarkArea->prevBurnMarkPos = TypeUtil::AppendArrayOrDefault<UnityEngine::Vector3>(_saberBurnMarkArea->prevBurnMarkPos);
        _saberBurnMarkArea->prevBurnMarkPosValid = TypeUtil::AppendArrayOrDefault<bool>(_saberBurnMarkArea->prevBurnMarkPosValid);

        _saberBurnMarkArea->lineRenderers = TypeUtil::AppendArrayOrDefault(_saberBurnMarkArea->lineRenderers, CreateNewLineRenderer(_saberModelManager->GetPhysicalSaberColor(saber)));
    }

    UnityEngine::LineRenderer* SaberBurnMarkAreaLatch::CreateNewLineRenderer(UnityEngine::Color initialColor) {
        static auto identity = UnityEngine::Quaternion::get_identity();
        auto newLine = UnityEngine::Object::Instantiate(_saberBurnMarkArea->saberBurnMarkLinePrefab, {0, 0, 0}, identity, nullptr);
        newLine->set_name(fmt::format("Lapiz | {}", newLine->get_name()));
        newLine->set_startColor(initialColor);
        newLine->set_endColor(initialColor);
        newLine->set_positionCount(2);
        return newLine;
    }

    UnityEngine::RenderTexture* SaberBurnMarkAreaLatch::CreateNewRenderTexture() {
        auto renderTexture = UnityEngine::RenderTexture::New_ctor(_saberBurnMarkArea->textureWidth, _saberBurnMarkArea->textureHeight, 0, UnityEngine::RenderTextureFormat::_get_ARGB32(), UnityEngine::RenderTextureReadWrite::_get_Default());
        renderTexture->set_name(fmt::format("Lapiz | SaberBurnMarkArea Texture {}", _lineFactoryIncrement++));
        renderTexture->set_hideFlags(UnityEngine::HideFlags::DontSave);
        return renderTexture;
    }

    void SaberBurnMarkAreaLatch::SaberBurnMarkArea_Start_Postfix(GlobalNamespace::SaberBurnMarkArea* self) {
        _saberBurnMarkArea = self;
        auto iter = _earlySabers->GetEnumerator();
        while (iter.MoveNext()) {
            AddSaber(iter.get_Current()->_saber);
        }
        _earlySabers->Clear();
    }

    void SaberBurnMarkAreaLatch::SaberBurnMarkArea_LateUpdate_Postfix(GlobalNamespace::SaberBurnMarkArea* self) {
        auto& rt = self->renderTextures;
        auto lastTexture = rt[rt.size() - 1];
        for (int i = rt.size() - 1; i > 0; i--)
        {
            rt[i] = rt[i - 1];
        }
        rt[0] = lastTexture;
    }
}