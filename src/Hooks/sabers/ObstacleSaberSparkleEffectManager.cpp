#include "utilities/hooking.hpp"

#include "sabers/effects/ObstacleSaberSparkleEffectManagerLatch.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/HapticFeedbackManager.hpp"
#include "GlobalNamespace/SaberType.hpp"
#include "UnityEngine/XR/XRNode.hpp"
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

    self->_wasSystemActive[0] = self->_isSystemActive[0];
	self->_wasSystemActive[1] = self->_isSystemActive[1];
	self->_isSystemActive[0] = false;
	self->_isSystemActive[1] = false;

    int len = self->_wasSystemActive.size();
	for (auto obstacleController : ListW<GlobalNamespace::ObstacleController*>(self->_beatmapObjectManager->get_activeObstacleControllers())) {
		UnityEngine::Bounds bounds = obstacleController->get_bounds();
		for (int i = 0; i < len; i++) {
			UnityEngine::Vector3 vector;
			auto saber = self->_sabers[i];
			if (saber->get_isActiveAndEnabled() && self->GetBurnMarkPos(bounds, obstacleController->get_transform(), saber->saberBladeBottomPos, saber->saberBladeTopPos, byref(vector)))
			{
				self->_isSystemActive[i] = true;
				self->_burnMarkPositions[i] = vector;
				self->_effects[i]->SetPositionAndRotation(vector, self->GetEffectRotation(vector, obstacleController->get_transform(), bounds));
				self->_hapticFeedbackManager->PlayHapticFeedback(saber->get_saberType() != GlobalNamespace::SaberType::SaberA ? UnityEngine::XR::XRNode::RightHand : UnityEngine::XR::XRNode::LeftHand, self->_rumblePreset);
				if (!self->_wasSystemActive[i])
				{
					self->_effects[i]->StartEmission();
					if (self->sparkleEffectDidStartEvent) self->sparkleEffectDidStartEvent->Invoke(saber->get_saberType());
				}
			}
		}
	}
	for (int j = 0; j < len; j++) {
		if (!self->_isSystemActive[j] && self->_wasSystemActive[j]) {
			self->_effects[j]->StopEmission();
			if (self->sparkleEffectDidEndEvent) self->sparkleEffectDidEndEvent->Invoke(self->_sabers[j]->get_saberType());
		}
	}

    //ObstacleSaberSparkleEffectManager_Update(self);
}

MAKE_AUTO_HOOK_MATCH(ObstacleSaberSparkleEffectManager_OnDisable, &GlobalNamespace::ObstacleSaberSparkleEffectManager::OnDisable, void, GlobalNamespace::ObstacleSaberSparkleEffectManager* self) {
    ObstacleSaberSparkleEffectManager_OnDisable(self);
    if (self->_isSystemActive.size() > 2) {
        for (int i = 2; i < self->_isSystemActive.size(); i++) {
            self->_isSystemActive[i] = false;
        }
    }
}
