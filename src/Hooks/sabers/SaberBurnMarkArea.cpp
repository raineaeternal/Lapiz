#include "utilities/hooking.hpp"

#include "sabers/effects/SaberBurnMarkAreaLatch.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/Camera.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Vector3.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/EssentialHelpers.hpp"

static inline UnityEngine::Vector3 operator*(UnityEngine::Vector3 vec, float v) {
    return { vec.x * v, vec.y * v, vec.z * v };
}

static inline UnityEngine::Vector3 operator/(UnityEngine::Vector3 vec, float v) {
    return { vec.x / v, vec.y / v, vec.z / v };
}

static inline UnityEngine::Vector3 operator+(UnityEngine::Vector3 a, UnityEngine::Vector3 b) {
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

static inline UnityEngine::Vector3 operator-(UnityEngine::Vector3 a, UnityEngine::Vector3 b) {
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_Start, &GlobalNamespace::SaberBurnMarkArea::Start, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_Start(self);
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkAreaLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkArea_Start_Postfix(self);
    }
}

// DOESN'T CALL ORIG ON PURPOSE
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkArea_LateUpdate, &GlobalNamespace::SaberBurnMarkArea::LateUpdate, void, GlobalNamespace::SaberBurnMarkArea* self) {
    if (self->_sabers[0])
	{
        // use sabers size as per TwoToLength
        for (int i = 0; i < self->_sabers.size(); i++)
        {
            UnityEngine::Vector3 zero{0, 0, 0};
            bool flag = self->_sabers[i]->get_isActiveAndEnabled() && self->GetBurnMarkPos(self->_sabers[i]->saberBladeBottomPos, self->_sabers[i]->saberBladeTopPos, byref(zero));
            if (flag && self->_prevBurnMarkPosValid[i]) {
                UnityEngine::Vector3 vector = zero - self->_prevBurnMarkPos[i];
                float magnitude = vector.get_magnitude();
                float num = 0.01f;
                int num2 = (int)(magnitude / num);
                int num3 = (num2 > 0) ? num2 : 1;
                UnityEngine::Vector3 normalized = UnityEngine::Vector3(vector.z, 0.0f, -vector.x).get_normalized();
                int num4 = 0;
                while (num4 <= num3 && num4 < self->_linePoints.size()) {
        			UnityEngine::Vector3 vector2 = self->_prevBurnMarkPos[i] + vector * (float)num4 / (float)num3;
        			vector2 = vector2 + normalized * UnityEngine::Random::Range(-self->_blackMarkLineRandomOffset, self->_blackMarkLineRandomOffset);
                    self->_linePoints[num4] = self->WorldToCameraBurnMarkPos(vector2);
                    num4++;
                }
                self->_lineRenderers[i]->set_positionCount(num3 + 1);
                self->_lineRenderers[i]->SetPositions(self->_linePoints);
                self->_lineRenderers[i]->set_enabled(true);
            } else {
                self->_lineRenderers[i]->set_enabled(false);
            }
            self->_prevBurnMarkPosValid[i] = flag;
            self->_prevBurnMarkPos[i] = zero;
        }
        // turned into for loop as per DynamicUpdate
        for (auto line : self->_lineRenderers) {
            if (line->get_enabled()) {
                self->_camera->Render();
                break;
            }
        }
        self->_camera->set_targetTexture(self->_renderTextures[1]);
        self->_renderer->get_sharedMaterial()->set_mainTexture(self->_renderTextures[1]);
        self->_fadeOutMaterial->set_mainTexture(self->_renderTextures[0]);
        self->_fadeOutMaterial->SetFloat(self->_fadeOutStrengthShaderPropertyID, std::max(0.0f, 1.0f - UnityEngine::Time::get_deltaTime() * self->_burnMarksFadeOutStrength));
        UnityEngine::Graphics::Blit(self->_renderTextures[0], self->_renderTextures[1], self->_fadeOutMaterial);

	}

    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkAreaLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkArea_LateUpdate_Postfix(self);
    }
}

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_OnEnable, &GlobalNamespace::SaberBurnMarkArea::OnEnable, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_OnEnable(self);
    if (self->_lineRenderers && self->_lineRenderers.size() > 2)
        for (int i = 2; i < self->_lineRenderers.size(); i++)
            self->_lineRenderers[i]->get_gameObject()->SetActive(true);
}

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_OnDisable, &GlobalNamespace::SaberBurnMarkArea::OnDisable, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_OnDisable(self);
    if (self->_lineRenderers && self->_lineRenderers.size() > 2)
        for (int i = 2; i < self->_lineRenderers.size(); i++)
            self->_lineRenderers[i]->get_gameObject()->SetActive(false);
}

// DOESN'T CALL ORIG ON PURPOSE
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkArea_OnDestroy, &GlobalNamespace::SaberBurnMarkArea::OnDestroy, void, GlobalNamespace::SaberBurnMarkArea* self) {
    if (self->_camera && self->_camera->m_CachedPtr) {
		UnityEngine::Object::Destroy(self->_camera->get_gameObject());
	}
    // destroy all line renderers as per DynamicDestroy
	if (self->_lineRenderers) {
        for (auto line : self->_lineRenderers) {
            if (line && line->m_CachedPtr) {
                UnityEngine::Object::Destroy(line);
            }
        }
	}
	GlobalNamespace::EssentialHelpers::SafeDestroy(self->_fadeOutMaterial);
	if (self->_renderTextures) {
		for (auto renderTexture : self->_renderTextures) {
			if (renderTexture && renderTexture->m_CachedPtr) {
				renderTexture->Release();
				GlobalNamespace::EssentialHelpers::SafeDestroy(renderTexture);
			}
		}
	}
}
