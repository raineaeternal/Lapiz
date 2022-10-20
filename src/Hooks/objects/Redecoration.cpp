#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"
#include "arrayutils.hpp"
/* I hate it here */

#include "GlobalNamespace/IntSO.hpp"
#include "GlobalNamespace/BoolSO.hpp"
#include "GlobalNamespace/FakeMirrorObjectsInstaller.hpp"
#include "GlobalNamespace/NoteDebrisPoolInstaller.hpp"
#include "GlobalNamespace/NoteDebris.hpp"
#include "GlobalNamespace/NoteDebris_Pool.hpp"
#include "GlobalNamespace/BeatmapObjectsInstaller.hpp"
#include "GlobalNamespace/EffectPoolsManualInstaller.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerInstaller.hpp"
#include "GlobalNamespace/MultiplayerLobbyInstaller.hpp"
#include "GlobalNamespace/MultiplayerPlayersManager.hpp"
#include "GlobalNamespace/MultiplayerPlayerLayout.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/GameNoteController.hpp"
#include "GlobalNamespace/GameNoteController_Pool.hpp"
#include "GlobalNamespace/BurstSliderGameNoteController.hpp"
#include "GlobalNamespace/BurstSliderGameNoteController_Pool.hpp"
#include "GlobalNamespace/BombNoteController.hpp"
#include "GlobalNamespace/BombNoteController_Pool.hpp"
#include "GlobalNamespace/ObstacleController.hpp"
#include "GlobalNamespace/ObstacleController_Pool.hpp"
#include "GlobalNamespace/SliderController.hpp"
#include "GlobalNamespace/SliderController_Pool.hpp"
#include "GlobalNamespace/SliderController_Pool_Short.hpp"
#include "GlobalNamespace/SliderController_Pool_Medium.hpp"
#include "GlobalNamespace/SliderController_Pool_Long.hpp"
#include "GlobalNamespace/NoteLineConnectionController.hpp"
#include "GlobalNamespace/NoteLineConnectionController_Pool.hpp"
#include "GlobalNamespace/BeatLine.hpp"
#include "GlobalNamespace/BeatLine_Pool.hpp"

#include "GlobalNamespace/FlyingTextEffect.hpp"
#include "GlobalNamespace/FlyingTextEffect_Pool.hpp"
#include "GlobalNamespace/FlyingScoreEffect.hpp"
#include "GlobalNamespace/FlyingScoreEffect_Pool.hpp"
#include "GlobalNamespace/FlyingSpriteEffect.hpp"
#include "GlobalNamespace/FlyingSpriteEffect_Pool.hpp"
#include "GlobalNamespace/BeatEffect.hpp"
#include "GlobalNamespace/BeatEffect_Pool.hpp"
#include "GlobalNamespace/NoteCutSoundEffect.hpp"
#include "GlobalNamespace/NoteCutSoundEffect_Pool.hpp"
#include "GlobalNamespace/BombCutSoundEffect.hpp"
#include "GlobalNamespace/BombCutSoundEffect_Pool.hpp"

#include "GlobalNamespace/MultiplayerConnectedPlayerGameNoteController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerGameNoteController_Pool.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerBombNoteController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerBombNoteController_Pool.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerObstacleController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerObstacleController_Pool.hpp"

#include "GlobalNamespace/PlayersSpecificSettingsAtGameStartModel.hpp"
#include "GlobalNamespace/IConnectedPlayer.hpp"
#include "GlobalNamespace/EmptyDifficultyBeatmap.hpp"
#include "GlobalNamespace/PracticeSettings.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/ColorManager.hpp"
#include "GlobalNamespace/MultiplayerPlayerStartState.hpp"
#include "GlobalNamespace/IConnectedPlayerBeatmapObjectEventManager.hpp"
#include "GlobalNamespace/PlayerSpecificSettingsNetSerializable.hpp"
#include "GlobalNamespace/ColorSchemeConverter.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerBeatmapObjectManager.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerBeatmapObjectManager_InitData.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerBeatmapObjectEventManager.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/IBeatmapObjectSpawner.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerSongTimeSyncController.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerSongTimeSyncController_InitData.hpp"
#include "GlobalNamespace/IBeatmapLevel.hpp"
#include "GlobalNamespace/IDifficultyBeatmapSet.hpp"
#include "GlobalNamespace/BeatmapCharacteristicSO.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/SaberManager_InitData.hpp"
#include "GlobalNamespace/SaberTypeExtensions.hpp"
#include "GlobalNamespace/SaberModelController.hpp"
#include "GlobalNamespace/SaberModelController_InitData.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarPlace.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarPlace_Pool.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarController.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarController_Factory.hpp"
#include "GlobalNamespace/LobbyAvatarInstaller.hpp"

#include "GlobalNamespace/MultiplayerLocalActivePlayerFacade.hpp"
#include "GlobalNamespace/MultiplayerLocalActivePlayerFacade_Factory.hpp"
#include "GlobalNamespace/MultiplayerLocalInactivePlayerFacade.hpp"
#include "GlobalNamespace/MultiplayerLocalInactivePlayerFacade_Factory.hpp"
#include "GlobalNamespace/MultiplayerLocalPlayerInstaller.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerFacade.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerFacade_Factory.hpp"

#include "GlobalNamespace/FakeReflectionDynamicObjectsState.hpp"
#include "GlobalNamespace/MirroredBeatmapObjectManager.hpp"
#include "GlobalNamespace/MirroredBombNoteController.hpp"
#include "GlobalNamespace/MirroredBombNoteController_Pool.hpp"
#include "GlobalNamespace/MirroredObstacleController.hpp"
#include "GlobalNamespace/MirroredObstacleController_Pool.hpp"
#include "GlobalNamespace/MirroredGameNoteController.hpp"
#include "GlobalNamespace/MirroredGameNoteController_Pool.hpp"
#include "GlobalNamespace/MirroredSliderController.hpp"
#include "GlobalNamespace/MirroredSliderController_Pool.hpp"
#include "GlobalNamespace/MirrorRendererGraphicsSettingsPresets.hpp"
#include "GlobalNamespace/MirrorRendererGraphicsSettingsPresets_Preset.hpp"

#include "System/Collections/Generic/Dictionary_2.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/DiContainer_ProviderInfo.hpp"
#include "Zenject/MemoryPoolIdInitialSizeMaxSizeBinder_1.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/ConcreteIdBinderNonGeneric.hpp"
#include "Zenject/NameTransformScopeConcreteIdArgConditionCopyNonLazyBinder.hpp"
#include "Zenject/FactoryToChoiceIdBinder_2.hpp"
#include "Zenject/FactorySubContainerBinder_2.hpp"
#include "Zenject/FactoryToChoiceIdBinder_3.hpp"
#include "Zenject/FactorySubContainerBinder_3.hpp"
#include "Zenject/MemoryPoolIdInitialSizeMaxSizeBinder_1.hpp"

#include "sombrero/shared/linq_functional.hpp"

#include "objects/RedecoratorRegistration.hpp"
#include "objects/ObjectDiffuser.hpp"

using namespace GlobalNamespace;
using namespace UnityEngine;
using namespace Sombrero::Linq::Functional;
using namespace Lapiz::Objects;
using namespace Lapiz::ArrayUtils;

#define PREFAB_INITIALIZE(field_) (decltype(self->field_))PrefabInitializing(self->field_, container, #field_, type)
static UnityEngine::Object* PrefabInitializing(UnityEngine::Object* originalPrefab, ::Zenject::DiContainer* container, const char* fieldName, System::Type* mainType) {
    // get all the redecorator registrations that are installed
    auto resolved = container->get_AncestorContainers()[0]->TryResolve<ListWrapper<RedecoratorRegistration*>>();
    // if not found, just return the original prefab
    if (!resolved) {
        DEBUG("No redecorations found for contract {}", fieldName);
        return originalPrefab;
    }

    // filter for the ones that match
    auto registrations = resolved | Where([mainType, fieldName](RedecoratorRegistration* rr){
        return rr->get_containerType() == mainType && rr->get_contract() == fieldName;
    }) | ToArray();
    // if no matches, return the original prefab
    if (registrations.size() <= 0) {
        DEBUG("No redecorations found for contract {}", fieldName);
        return originalPrefab;
    }

    DEBUG("Redecorating contract {}", fieldName);
    // sort by priority, check if this is the right order! (asc / desc)
    std::stable_sort(registrations.begin(), registrations.end(), [](RedecoratorRegistration* a, RedecoratorRegistration* b) -> bool{
        return b->get_priority() < a->get_priority();
    });

    auto irgo = GameObject::New_ctor("Lapiz | InternalRedecorator");
    irgo->SetActive(false);
    Object::Instantiate(originalPrefab, irgo->get_transform());
    auto clone = irgo->GetComponentInChildren(registrations.First()->get_prefabType(), true);

    // apply all redecorations
    for (auto reg : registrations) {
        reg->Redecorate_internal(clone);
        if (!reg->get_chain()) break;
    }

    container->LazyInject(Lapiz::Objects::ObjectDiffuser::New_ctor(irgo));
    return clone;
}

MAKE_AUTO_HOOK_ORIG_MATCH(BeatmapObjectsInstaller_InstallBindings, &BeatmapObjectsInstaller::InstallBindings, void, BeatmapObjectsInstaller* self) {
	DEBUG("Redecoration BeatmapObjectsInstaller_InstallBindings");
    bool proMode = self->sceneSetupData->gameplayModifiers->get_proMode();
    auto type = self->GetType();
    auto container = self->get_Container();

    // save orig
    auto orig_proModeNotePrefab = self->proModeNotePrefab;
    auto orig_normalBasicNotePrefab = self->normalBasicNotePrefab;
    auto orig_burstSliderHeadNotePrefab = self->burstSliderHeadNotePrefab;
    auto orig_burstSliderNotePrefab = self->burstSliderNotePrefab;
    auto orig_burstSliderFillPrefab = self->burstSliderFillPrefab;
    auto orig_bombNotePrefab = self->bombNotePrefab;
    auto orig_obstaclePrefab = self->obstaclePrefab;
    auto orig_sliderShortPrefab = self->sliderShortPrefab;
    auto orig_sliderMediumPrefab = self->sliderMediumPrefab;
    auto orig_sliderLongPrefab = self->sliderLongPrefab;
    auto orig_noteLineConnectionControllerPrefab = self->noteLineConnectionControllerPrefab;
    auto orig_beatLinePrefab = self->beatLinePrefab;

    // edit prefabs
    if (proMode) self->proModeNotePrefab = PREFAB_INITIALIZE(proModeNotePrefab);
    else self->normalBasicNotePrefab = PREFAB_INITIALIZE(normalBasicNotePrefab);
    self->burstSliderHeadNotePrefab = PREFAB_INITIALIZE(burstSliderHeadNotePrefab);
    self->burstSliderNotePrefab = PREFAB_INITIALIZE(burstSliderNotePrefab);
    self->burstSliderFillPrefab = PREFAB_INITIALIZE(burstSliderFillPrefab);
    self->bombNotePrefab = PREFAB_INITIALIZE(bombNotePrefab);
    self->obstaclePrefab = PREFAB_INITIALIZE(obstaclePrefab);
    self->sliderShortPrefab = PREFAB_INITIALIZE(sliderShortPrefab);
    self->sliderMediumPrefab = PREFAB_INITIALIZE(sliderMediumPrefab);
    self->sliderLongPrefab = PREFAB_INITIALIZE(sliderLongPrefab);
    self->noteLineConnectionControllerPrefab = PREFAB_INITIALIZE(noteLineConnectionControllerPrefab);
    self->beatLinePrefab = PREFAB_INITIALIZE(beatLinePrefab);

    // run method
    BeatmapObjectsInstaller_InstallBindings(self);

    // restore fields
    if (proMode) self->proModeNotePrefab = orig_proModeNotePrefab;
    else self->normalBasicNotePrefab = orig_normalBasicNotePrefab;
    self->burstSliderHeadNotePrefab = orig_burstSliderHeadNotePrefab;
    self->burstSliderNotePrefab = orig_burstSliderNotePrefab;
    self->burstSliderFillPrefab = orig_burstSliderFillPrefab;
    self->bombNotePrefab = orig_bombNotePrefab;
    self->obstaclePrefab = orig_obstaclePrefab;
    self->sliderShortPrefab = orig_sliderShortPrefab;
    self->sliderMediumPrefab = orig_sliderMediumPrefab;
    self->sliderLongPrefab = orig_sliderLongPrefab;
    self->noteLineConnectionControllerPrefab = orig_noteLineConnectionControllerPrefab;
    self->beatLinePrefab = orig_beatLinePrefab;
}

MAKE_AUTO_HOOK_ORIG_MATCH(EffectPoolsManualInstaller_ManualInstallBindings, &EffectPoolsManualInstaller::ManualInstallBindings, void, EffectPoolsManualInstaller* self, ::Zenject::DiContainer* container, bool shortBeatEffect) {
    DEBUG("Redecoration EffectPoolsManualInstaller_ManualInstallBindings");
    auto type = self->GetType();

    // save orig
    auto orig_flyingTextEffectPrefab = self->flyingTextEffectPrefab;
    auto orig_flyingScoreEffectPrefab = self->flyingScoreEffectPrefab;
    auto orig_flyingSpriteEffectPrefab = self->flyingSpriteEffectPrefab;
    auto orig_shortBeatEffectPrefab = self->shortBeatEffectPrefab;
    auto orig_beatEffectPrefab = self->beatEffectPrefab;
    auto orig_noteCutSoundEffectPrefab = self->noteCutSoundEffectPrefab;
    auto orig_bombCutSoundEffectPrefab = self->bombCutSoundEffectPrefab;

    // edit prefabs
    self->flyingTextEffectPrefab = PREFAB_INITIALIZE(flyingTextEffectPrefab);
    self->flyingScoreEffectPrefab = PREFAB_INITIALIZE(flyingScoreEffectPrefab);
    self->flyingSpriteEffectPrefab = PREFAB_INITIALIZE(flyingSpriteEffectPrefab);
    if (shortBeatEffect) self->shortBeatEffectPrefab = PREFAB_INITIALIZE(shortBeatEffectPrefab);
    else self->beatEffectPrefab = PREFAB_INITIALIZE(beatEffectPrefab);
    self->noteCutSoundEffectPrefab = PREFAB_INITIALIZE(noteCutSoundEffectPrefab);
    self->bombCutSoundEffectPrefab = PREFAB_INITIALIZE(bombCutSoundEffectPrefab);

    // run method
    EffectPoolsManualInstaller_ManualInstallBindings(self, container, shortBeatEffect);

    // restore fields
    self->flyingTextEffectPrefab = orig_flyingTextEffectPrefab;
    self->flyingScoreEffectPrefab = orig_flyingScoreEffectPrefab;
    self->flyingSpriteEffectPrefab = orig_flyingSpriteEffectPrefab;
    if (shortBeatEffect) self->shortBeatEffectPrefab = orig_shortBeatEffectPrefab;
    else self->beatEffectPrefab = orig_beatEffectPrefab;
    self->noteCutSoundEffectPrefab = orig_noteCutSoundEffectPrefab;
    self->bombCutSoundEffectPrefab = orig_bombCutSoundEffectPrefab;
}

MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerConnectedPlayerInstaller_InstallBindings, &MultiplayerConnectedPlayerInstaller::InstallBindings, void, MultiplayerConnectedPlayerInstaller* self) {
    DEBUG("Redecoration MultiplayerConnectedPlayerInstaller_InstallBindings");
    auto container = self->get_Container();
    auto type = self->GetType();

    // save orig
    auto orig_connectedPlayerBeatmapObjectEventManagerPrefab = self->connectedPlayerBeatmapObjectEventManagerPrefab;
    auto orig_connectedPlayerAudioTimeSyncControllerPrefab = self->connectedPlayerAudioTimeSyncControllerPrefab;
    auto orig_multiplayerGameNoteControllerPrefab = self->multiplayerGameNoteControllerPrefab;
    auto orig_multiplayerBurstSliderHeadGameNoteControllerPrefab = self->multiplayerBurstSliderHeadGameNoteControllerPrefab;
    auto orig_multiplayerBurstSliderGameNoteControllerPrefab = self->multiplayerBurstSliderGameNoteControllerPrefab;
    auto orig_multiplayerBurstSliderFillControllerPrefab = self->multiplayerBurstSliderFillControllerPrefab;
    auto orig_multiplayerBombNoteControllerPrefab = self->multiplayerBombNoteControllerPrefab;
    auto orig_multiplayerObstacleControllerPrefab = self->multiplayerObstacleControllerPrefab;

    // edit prefabs
    self->connectedPlayerBeatmapObjectEventManagerPrefab = PREFAB_INITIALIZE(connectedPlayerBeatmapObjectEventManagerPrefab);
    self->connectedPlayerAudioTimeSyncControllerPrefab = PREFAB_INITIALIZE(connectedPlayerAudioTimeSyncControllerPrefab);
    self->multiplayerGameNoteControllerPrefab = PREFAB_INITIALIZE(multiplayerGameNoteControllerPrefab);
    self->multiplayerBurstSliderHeadGameNoteControllerPrefab = PREFAB_INITIALIZE(multiplayerBurstSliderHeadGameNoteControllerPrefab);
    self->multiplayerBurstSliderGameNoteControllerPrefab = PREFAB_INITIALIZE(multiplayerBurstSliderGameNoteControllerPrefab);
    self->multiplayerBurstSliderFillControllerPrefab = PREFAB_INITIALIZE(multiplayerBurstSliderFillControllerPrefab);
    self->multiplayerBombNoteControllerPrefab = PREFAB_INITIALIZE(multiplayerBombNoteControllerPrefab);
    self->multiplayerObstacleControllerPrefab = PREFAB_INITIALIZE(multiplayerObstacleControllerPrefab);

    // run method
    MultiplayerConnectedPlayerInstaller_InstallBindings(self);

    // restore fields
    self->connectedPlayerBeatmapObjectEventManagerPrefab = orig_connectedPlayerBeatmapObjectEventManagerPrefab;
    self->connectedPlayerAudioTimeSyncControllerPrefab = orig_connectedPlayerAudioTimeSyncControllerPrefab;
    self->multiplayerGameNoteControllerPrefab = orig_multiplayerGameNoteControllerPrefab;
    self->multiplayerBurstSliderHeadGameNoteControllerPrefab = orig_multiplayerBurstSliderHeadGameNoteControllerPrefab;
    self->multiplayerBurstSliderGameNoteControllerPrefab = orig_multiplayerBurstSliderGameNoteControllerPrefab;
    self->multiplayerBurstSliderFillControllerPrefab = orig_multiplayerBurstSliderFillControllerPrefab;
    self->multiplayerBombNoteControllerPrefab = orig_multiplayerBombNoteControllerPrefab;
    self->multiplayerObstacleControllerPrefab = orig_multiplayerObstacleControllerPrefab;
}

MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerLobbyInstaller_InstallBindings, &MultiplayerLobbyInstaller::InstallBindings, void, MultiplayerLobbyInstaller* self) {
	DEBUG("Redecoration MultiplayerLobbyInstaller_InstallBindings");
    auto container = self->get_Container();
    auto type = self->GetType();

    // save orig
    auto orig_multiplayerAvatarPlacePrefab = self->multiplayerAvatarPlacePrefab;
    auto orig_multiplayerLobbyAvatarControllerPrefab = self->multiplayerLobbyAvatarControllerPrefab;

    // edit prefabs
    self->multiplayerAvatarPlacePrefab = PREFAB_INITIALIZE(multiplayerAvatarPlacePrefab);
    self->multiplayerLobbyAvatarControllerPrefab = PREFAB_INITIALIZE(multiplayerLobbyAvatarControllerPrefab);

    // run method
    MultiplayerLobbyInstaller_InstallBindings(self);

    // restore fields
    self->multiplayerAvatarPlacePrefab = orig_multiplayerAvatarPlacePrefab;
    self->multiplayerLobbyAvatarControllerPrefab = orig_multiplayerLobbyAvatarControllerPrefab;
}

MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerPlayersManager_BindPlayerFactories, &MultiplayerPlayersManager::BindPlayerFactories, void, MultiplayerPlayersManager* self, ::MultiplayerPlayerLayout layout) {
    DEBUG("Redecoration MultiplayerPlayersManager_BindPlayerFactories");
    auto container = self->container;
    auto type = self->GetType();

    // save orig
    auto orig_inactiveLocalPlayerControllerPrefab = self->inactiveLocalPlayerControllerPrefab;
    auto orig_activeLocalPlayerDuelControllerPrefab = self->activeLocalPlayerDuelControllerPrefab;
    auto orig_connectedPlayerDuelControllerPrefab = self->connectedPlayerDuelControllerPrefab;
    auto orig_activeLocalPlayerControllerPrefab = self->activeLocalPlayerControllerPrefab;
    auto orig_connectedPlayerControllerPrefab = self->connectedPlayerControllerPrefab;

    // edit prefabs
    self->inactiveLocalPlayerControllerPrefab = PREFAB_INITIALIZE(inactiveLocalPlayerControllerPrefab);
    if (layout == MultiplayerPlayerLayout::Duel) {
        self->activeLocalPlayerDuelControllerPrefab = PREFAB_INITIALIZE(activeLocalPlayerDuelControllerPrefab);
        self->connectedPlayerDuelControllerPrefab = PREFAB_INITIALIZE(connectedPlayerDuelControllerPrefab);
    } else {
        self->activeLocalPlayerControllerPrefab = PREFAB_INITIALIZE(activeLocalPlayerControllerPrefab);
        self->connectedPlayerControllerPrefab = PREFAB_INITIALIZE(connectedPlayerControllerPrefab);
    }

    // run method
    MultiplayerPlayersManager_BindPlayerFactories(self, layout);

    // restore fields
    self->inactiveLocalPlayerControllerPrefab = orig_inactiveLocalPlayerControllerPrefab;
    if (layout == MultiplayerPlayerLayout::Duel) {
        self->activeLocalPlayerDuelControllerPrefab = orig_activeLocalPlayerDuelControllerPrefab;
        self->connectedPlayerDuelControllerPrefab = orig_connectedPlayerDuelControllerPrefab;
    } else {
        self->activeLocalPlayerControllerPrefab = orig_activeLocalPlayerControllerPrefab;
        self->connectedPlayerControllerPrefab = orig_connectedPlayerControllerPrefab;
    }
}

MAKE_AUTO_HOOK_ORIG_MATCH(NoteDebrisPoolInstaller_InstallBindings, &NoteDebrisPoolInstaller::InstallBindings, void, NoteDebrisPoolInstaller* self) {
	DEBUG("Redecoration NoteDebrisPoolInstaller_InstallBindings");
    auto container = self->get_Container();
    auto type = self->GetType();
    bool hd = self->noteDebrisHDConditionVariable->get_value();

    // save orig
    auto orig_normalNoteDebrisHDPrefab = self->normalNoteDebrisHDPrefab;
    auto orig_burstSliderHeadNoteDebrisHDPrefab = self->burstSliderHeadNoteDebrisHDPrefab;
    auto orig_burstSliderElementNoteHDPrefab = self->burstSliderElementNoteHDPrefab;
    auto orig_normalNoteDebrisLWPrefab = self->normalNoteDebrisLWPrefab;
    auto orig_burstSliderHeadNoteDebrisLWPrefab = self->burstSliderHeadNoteDebrisLWPrefab;
    auto orig_burstSliderElementNoteLWPrefab = self->burstSliderElementNoteLWPrefab;

    // edit prefabs
    if (hd) {
        self->normalNoteDebrisHDPrefab = PREFAB_INITIALIZE(normalNoteDebrisHDPrefab);
        self->burstSliderHeadNoteDebrisHDPrefab = PREFAB_INITIALIZE(burstSliderHeadNoteDebrisHDPrefab);
        self->burstSliderElementNoteHDPrefab = PREFAB_INITIALIZE(burstSliderElementNoteHDPrefab);
    } else {
        self->normalNoteDebrisLWPrefab = PREFAB_INITIALIZE(normalNoteDebrisLWPrefab);
        self->burstSliderHeadNoteDebrisLWPrefab = PREFAB_INITIALIZE(burstSliderHeadNoteDebrisLWPrefab);
        self->burstSliderElementNoteLWPrefab = PREFAB_INITIALIZE(burstSliderElementNoteLWPrefab);
    }

    // run method
    NoteDebrisPoolInstaller_InstallBindings(self);

    // restore fields
    if (hd) {
        self->normalNoteDebrisHDPrefab = orig_normalNoteDebrisHDPrefab;
        self->burstSliderHeadNoteDebrisHDPrefab = orig_burstSliderHeadNoteDebrisHDPrefab;
        self->burstSliderElementNoteHDPrefab = orig_burstSliderElementNoteHDPrefab;
    } else {
        self->normalNoteDebrisLWPrefab = orig_normalNoteDebrisLWPrefab;
        self->burstSliderHeadNoteDebrisLWPrefab = orig_burstSliderHeadNoteDebrisLWPrefab;
        self->burstSliderElementNoteLWPrefab = orig_burstSliderElementNoteLWPrefab;
    }
}

MAKE_AUTO_HOOK_ORIG_MATCH(FakeMirrorObjectsInstaller_InstallBindings, &FakeMirrorObjectsInstaller::InstallBindings, void, FakeMirrorObjectsInstaller* self) {
	DEBUG("Redecoration FakeMirrorObjectsInstaller_InstallBindings");
    auto container = self->get_Container();
    auto type = self->GetType();

    // save orig
    auto orig_mirroredGameNoteControllerPrefab = self->mirroredGameNoteControllerPrefab;
    auto orig_mirroredBurstSliderHeadGameNoteControllerPrefab = self->mirroredBurstSliderHeadGameNoteControllerPrefab;
    auto orig_mirroredBurstSliderGameNoteControllerPrefab = self->mirroredBurstSliderGameNoteControllerPrefab;
    auto orig_mirroredBurstSliderFillControllerPrefab = self->mirroredBurstSliderFillControllerPrefab;
    auto orig_mirroredBombNoteControllerPrefab = self->mirroredBombNoteControllerPrefab;
    auto orig_mirroredObstacleControllerPrefab = self->mirroredObstacleControllerPrefab;
    auto orig_mirroredSliderControllerPrefab = self->mirroredSliderControllerPrefab;

    // edit prefabs
    self->mirroredGameNoteControllerPrefab = PREFAB_INITIALIZE(mirroredGameNoteControllerPrefab);
    self->mirroredBurstSliderHeadGameNoteControllerPrefab = PREFAB_INITIALIZE(mirroredBurstSliderHeadGameNoteControllerPrefab);
    self->mirroredBurstSliderGameNoteControllerPrefab = PREFAB_INITIALIZE(mirroredBurstSliderGameNoteControllerPrefab);
    self->mirroredBurstSliderFillControllerPrefab = PREFAB_INITIALIZE(mirroredBurstSliderFillControllerPrefab);
    self->mirroredBombNoteControllerPrefab = PREFAB_INITIALIZE(mirroredBombNoteControllerPrefab);
    self->mirroredObstacleControllerPrefab = PREFAB_INITIALIZE(mirroredObstacleControllerPrefab);
    self->mirroredSliderControllerPrefab = PREFAB_INITIALIZE(mirroredSliderControllerPrefab);

    // run method
    FakeMirrorObjectsInstaller_InstallBindings(self);

    // restore fields
    self->mirroredGameNoteControllerPrefab = orig_mirroredGameNoteControllerPrefab;
    self->mirroredBurstSliderHeadGameNoteControllerPrefab = orig_mirroredBurstSliderHeadGameNoteControllerPrefab;
    self->mirroredBurstSliderGameNoteControllerPrefab = orig_mirroredBurstSliderGameNoteControllerPrefab;
    self->mirroredBurstSliderFillControllerPrefab = orig_mirroredBurstSliderFillControllerPrefab;
    self->mirroredBombNoteControllerPrefab = orig_mirroredBombNoteControllerPrefab;
    self->mirroredObstacleControllerPrefab = orig_mirroredObstacleControllerPrefab;
    self->mirroredSliderControllerPrefab = orig_mirroredSliderControllerPrefab;
}