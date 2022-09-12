#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"

#include "sabers/effects/SaberBurnMarkSparklesLatch.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/ParticleSystem.hpp"
#include "UnityEngine/ParticleSystem_EmitParams.hpp"

MAKE_AUTO_HOOK_MATCH(SaberBurnMarkSparkles_Start, &GlobalNamespace::SaberBurnMarkSparkles::Start, void, GlobalNamespace::SaberBurnMarkSparkles* self) {
    SaberBurnMarkSparkles_Start(self);
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkSparklesLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkSparkles_Start_Postfix(self);
    }
}

void SaberBurnMarkSparkles_LateUpdate_Replacement(GlobalNamespace::SaberBurnMarkSparkles* self);

MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkSparkles_LateUpdate, &GlobalNamespace::SaberBurnMarkSparkles::LateUpdate, void, GlobalNamespace::SaberBurnMarkSparkles* self) {
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkSparklesLatch::get_instance();
    if (instance) {
        instance->SaberBurnMarkSparkles_LateUpdate_Prefix(self);
        SaberBurnMarkSparkles_LateUpdate_Replacement(self);
        instance->SaberBurnMarkSparkles_LateUpdate_Postfix(self);
    } else {
        SaberBurnMarkSparkles_LateUpdate_Replacement(self);
    }
}

void SaberBurnMarkSparkles_LateUpdate_Replacement(GlobalNamespace::SaberBurnMarkSparkles* self) {
	for (int i = 0; i < self->sabers.size(); i++) {
        auto saber = self->sabers[i];
		UnityEngine::Vector3 vector{0.0f, 0.0f, 0.0f};
		bool flag = saber->get_isActiveAndEnabled() && self->GetBurnMarkPos(saber->saberBladeBottomPos, saber->saberBladeTopPos, byref(vector));
		
        if (flag) {
			self->burnMarksPS[i]->get_transform()->set_localPosition(vector);
		} else if (!self->prevBurnMarkPosValid[i]) {
            self->burnMarksPS[i]->Clear();
        }
        if (!self->prevBurnMarkPosValid[i]) 
            self->burnMarksEmissionModules[i].set_enabled(flag);
        UnityEngine::Color32 col;
        auto saberColor = self->colorManager->ColorForSaberType(saber->get_saberType());
        col.r = col.r * 255;
        col.g = col.g * 255;
        col.b = col.b * 255;
        col.a = col.a * 255;
		self->sparklesEmitParams.set_startColor(col);
		if (flag && self->prevBurnMarkPosValid[i]) {
			auto a = vector - self->prevBurnMarkPos[i];
			float magnitude = a.get_magnitude();
			float num = 0.05f;
			int num2 = (int)(magnitude / num);
			int num3 = (num2 > 0) ? num2 : 1;
			for (int j = 0; j <= num2; j++) {
				self->sparklesEmitParams.set_position(self->prevBurnMarkPos[i] + a * (float)j / (float)num3);
				self->sparklesPS->Emit(self->sparklesEmitParams, 1);
			}
		}
		self->prevBurnMarkPosValid[i] = flag;
		self->prevBurnMarkPos[i] = vector;
	}
}

MAKE_AUTO_HOOK_ORIG_MATCH(ColorManager_ColorForSaberType, &GlobalNamespace::ColorManager::ColorForSaberType, UnityEngine::Color, GlobalNamespace::ColorManager* self, GlobalNamespace::SaberType type) {
    auto instance = Lapiz::Sabers::Effects::SaberBurnMarkSparklesLatch::get_instance();
    UnityEngine::Color color;
    if (!instance || instance->ColorManager_ColorForSaberType_Prefix(color)) {
        color = ColorManager_ColorForSaberType(self, type);
    }
    return color;
}

// DOES NOT CALL ORIG
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkSparkles_OnEnable, &GlobalNamespace::SaberBurnMarkSparkles::OnEnable, void, GlobalNamespace::SaberBurnMarkSparkles* self) {
	if (!self->burnMarksPS) return;
    for (auto ps : self->burnMarksPS) {
        if (ps && ps->m_CachedPtr.m_value) {
            ps->get_gameObject()->SetActive(true);
        }
	}
}

// DOES NOT CALL ORIG
MAKE_AUTO_HOOK_ORIG_MATCH(SaberBurnMarkSparkles_OnDisable, &GlobalNamespace::SaberBurnMarkSparkles::OnDisable, void, GlobalNamespace::SaberBurnMarkSparkles* self) {
	if (!self->burnMarksPS) return;
    for (auto ps : self->burnMarksPS) {
        if (ps && ps->m_CachedPtr.m_value) {
            ps->get_gameObject()->SetActive(false);
        }
	}
}
