#include "utilities/hooking.hpp"

#include "sabers/effects/ObstacleSaberSparkleEffectManagerLatch.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "System/Action_1.hpp"

using namespace Lapiz::Sabers::Effects;

MAKE_AUTO_HOOK_MATCH(ObstacleSaberSparkleEffectManager_Start, &GlobalNamespace::ObstacleSaberSparkleEffectManager::Start, void, GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
    ObstacleSaberSparkleEffectManager_Start(self);
    auto instance = ObstacleSaberSparkleEffectManagerLatch::get_instance();
    if (instance) {
        instance->ObstacleSaberSparkleEffectManager_Start_Postfix(self);
    }
}

MAKE_AUTO_HOOK_ORIG_MATCH(ObstacleSaberSparkleEffectManager_Update, &GlobalNamespace::ObstacleSaberSparkleEffectManager::Update, void, GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
    auto instance = ObstacleSaberSparkleEffectManagerLatch::get_instance();
    if (instance) {
        instance->ObstacleSaberSparkleEffectManager_Update_Prefix(self);
    }
    
    self->wasSystemActive[0] = self->isSystemActive[0];
	self->wasSystemActive[1] = self->isSystemActive[1];
	self->isSystemActive[0] = false;
	self->isSystemActive[1] = false;

    int len = self->wasSystemActive.size();
	for (auto obstacleController : ListWrapper<GlobalNamespace::ObstacleController*>(self->beatmapObjectManager->get_activeObstacleControllers())) {
		UnityEngine::Bounds bounds = obstacleController->get_bounds();
		for (int i = 0; i < len; i++) {
			UnityEngine::Vector3 vector;
			auto saber = self->sabers[i];
			if (saber->get_isActiveAndEnabled() && self->GetBurnMarkPos(bounds, obstacleController->get_transform(), saber->saberBladeBottomPos, saber->saberBladeTopPos, byref(vector)))
			{
				self->isSystemActive[i] = true;
				self->burnMarkPositions[i] = vector;
				self->effects[i]->SetPositionAndRotation(vector, self->GetEffectRotation(vector, obstacleController->get_transform(), bounds));
				self->hapticFeedbackController->PlayHapticFeedback(saber->get_saberType() != GlobalNamespace::SaberType::SaberA ? UnityEngine::XR::XRNode::RightHand : UnityEngine::XR::XRNode::LeftHand, self->rumblePreset);
				if (!self->wasSystemActive[i])
				{
					self->effects[i]->StartEmission();
					if (self->sparkleEffectDidStartEvent) self->sparkleEffectDidStartEvent->Invoke(saber->get_saberType());
				}
			}
		}
	}
	for (int j = 0; j < len; j++) {
		if (!self->isSystemActive[j] && self->wasSystemActive[j]) {
			self->effects[j]->StopEmission();
			if (self->sparkleEffectDidEndEvent) self->sparkleEffectDidEndEvent->Invoke(self->sabers[j]->get_saberType());
		}
	}

    //ObstacleSaberSparkleEffectManager_Update(self);
}

MAKE_AUTO_HOOK_MATCH(ObstacleSaberSparkleEffectManager_OnDisable, &GlobalNamespace::ObstacleSaberSparkleEffectManager::OnDisable, void, GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
    ObstacleSaberSparkleEffectManager_OnDisable(self);
    if (self->isSystemActive.size() > 2) {
        for (int i = 2; self->isSystemActive.size(); i++) {
            self->isSystemActive[i] = false;
        }
    }
}

