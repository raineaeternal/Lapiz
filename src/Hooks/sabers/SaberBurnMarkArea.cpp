#include "utilities/hooking.hpp"

#include "sabers/effects/SaberBurnMarkAreaLatch.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Graphics.hpp"
#include "UnityEngine/Random.hpp"
#include "UnityEngine/Camera.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Time.hpp"
#include "GlobalNamespace/Saber.hpp"
#include "GlobalNamespace/EssentialHelpers.hpp"

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_Start, &GlobalNamespace::SaberBurnMarkArea::Start, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_Start(self);
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkAreaLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkArea_Start_Postfix(self);
    }
}

// DOESN'T CALL ORIG ON PURPOSE
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkArea_LateUpdate, &GlobalNamespace::SaberBurnMarkArea::LateUpdate, void, GlobalNamespace::SaberBurnMarkArea* self) {
    if (self->sabers[0])
	{
        // use sabers size as per TwoToLength
        for (int i = 0; i < self->sabers.size(); i++)
        {
            UnityEngine::Vector3 zero{0, 0, 0};
            bool flag = self->sabers[i]->get_isActiveAndEnabled() && self->GetBurnMarkPos(self->sabers[i]->saberBladeBottomPos, self->sabers[i]->saberBladeTopPos, byref(zero));
            if (flag && self->prevBurnMarkPosValid[i]) {
                UnityEngine::Vector3 vector = zero - self->prevBurnMarkPos[i];
                float magnitude = vector.get_magnitude();
                float num = 0.01f;
                int num2 = (int)(magnitude / num);
                int num3 = (num2 > 0) ? num2 : 1;
                UnityEngine::Vector3 normalized = UnityEngine::Vector3(vector.z, 0.0f, -vector.x).get_normalized();
                int num4 = 0;
                while (num4 <= num3 && num4 < self->linePoints.size()) {
        			UnityEngine::Vector3 vector2 = self->prevBurnMarkPos[i] + vector * (float)num4 / (float)num3;
        			vector2 = vector2 + normalized * UnityEngine::Random::Range(-self->blackMarkLineRandomOffset, self->blackMarkLineRandomOffset);
                    self->linePoints[num4] = self->WorldToCameraBurnMarkPos(vector2);
                    num4++;
                }
                self->lineRenderers[i]->set_positionCount(num3 + 1);
                self->lineRenderers[i]->SetPositions(self->linePoints);
                self->lineRenderers[i]->set_enabled(true);
            } else {
                self->lineRenderers[i]->set_enabled(false);
            }
            self->prevBurnMarkPosValid[i] = flag;
            self->prevBurnMarkPos[i] = zero;
        }
        // turned into for loop as per DynamicUpdate
        for (auto line : self->lineRenderers) {
            if (line->get_enabled()) {
                self->camera->Render();
                break;
            }
        }
        self->camera->set_targetTexture(self->renderTextures[1]);
        self->renderer->get_sharedMaterial()->set_mainTexture(self->renderTextures[1]);
        self->fadeOutMaterial->set_mainTexture(self->renderTextures[0]);
        self->fadeOutMaterial->SetFloat(self->fadeOutStrengthShaderPropertyID, std::max(0.0f, 1.0f - UnityEngine::Time::get_deltaTime() * self->burnMarksFadeOutStrength));
        UnityEngine::Graphics::Blit(self->renderTextures[0], self->renderTextures[1], self->fadeOutMaterial);
        /*
        // Removed as per DynamicUpdate
        auto renderTexture = self->renderTextures[0];
        self->renderTextures[0] = self->renderTextures[1];
        self->renderTextures[1] = renderTexture;
        */
    
	}
    
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkAreaLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkArea_LateUpdate_Postfix(self);
    }
}

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_OnEnable, &GlobalNamespace::SaberBurnMarkArea::OnEnable, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_OnEnable(self);
    if (self->lineRenderers && self->lineRenderers.size() > 2)
        for (int i = 2; i < self->lineRenderers.size(); i++)
            self->lineRenderers[i]->get_gameObject()->SetActive(true);
}

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkArea_OnDisable, &GlobalNamespace::SaberBurnMarkArea::OnDisable, void, GlobalNamespace::SaberBurnMarkArea* self) {
    SaberBurnMarkArea_OnDisable(self);
    if (self->lineRenderers && self->lineRenderers.size() > 2)
        for (int i = 2; i < self->lineRenderers.size(); i++)
            self->lineRenderers[i]->get_gameObject()->SetActive(false);
}

// DOESN'T CALL ORIG ON PURPOSE
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkArea_OnDestroy, &GlobalNamespace::SaberBurnMarkArea::OnDestroy, void, GlobalNamespace::SaberBurnMarkArea* self) {
    if (self->camera && self->camera->m_CachedPtr.m_value) {
		UnityEngine::Object::Destroy(self->camera->get_gameObject());
	}
    // destroy all line renderers as per DynamicDestroy
	if (self->lineRenderers) {
        for (auto line : self->lineRenderers) {
            if (line && line->m_CachedPtr.m_value) {
                UnityEngine::Object::Destroy(line);
            }
        }
	}
	GlobalNamespace::EssentialHelpers::SafeDestroy(self->fadeOutMaterial);
	if (self->renderTextures) {
		for (auto renderTexture : self->renderTextures) {
			if (renderTexture && renderTexture->m_CachedPtr.m_value) {
				renderTexture->Release();
				GlobalNamespace::EssentialHelpers::SafeDestroy(renderTexture);
			}
		}
	}
}


