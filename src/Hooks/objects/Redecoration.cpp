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

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Object.hpp"

#include "Zenject/DiContainer.hpp"
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

#define PREFAB_INITIALIZE(field_) PrefabInitializing(self->field_, container, #field_, type)
static UnityEngine::Object* PrefabInitializing(UnityEngine::Object* originalPrefab, ::Zenject::DiContainer* container, const char* fieldName, System::Type* mainType) {
    // get all the redecorator registrations that are installed
    auto resolved = container->get_AncestorContainers()[0]->TryResolve<ListWrapper<RedecoratorRegistration*>>();
    // if not found, just return the original prefab
    if (!resolved) return originalPrefab;

    // filter for the ones that match
    auto registrations = resolved | Where([mainType, fieldName](RedecoratorRegistration* rr){
        return rr->get_containerType() == mainType && rr->get_contract() == fieldName;
    }) | ToArray();
    // if no matches, return the original prefab
    if (registrations.size() <= 0) return originalPrefab;

    // sort by priority, check if this is the right order! (asc / desc)
    std::stable_sort(registrations.begin(), registrations.end(), [](RedecoratorRegistration* a, RedecoratorRegistration* b) -> bool{
        return a->get_priority() < b->get_priority();
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

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(BeatmapObjectsInstaller_InstallBindings, &BeatmapObjectsInstaller::InstallBindings, void, BeatmapObjectsInstaller* self) {
	bool proMode = self->sceneSetupData->gameplayModifiers->get_proMode();
    auto container = self->get_Container();
    
    auto Normal = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::Normal);
    auto BurstSliderHead = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderHead);
    auto BurstSliderElement = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElement);
    auto BurstSliderElementFill = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElementFill);

    auto type = self->GetType();
    if (proMode) container->BindMemoryPool<GameNoteController*, GameNoteController::Pool*>()->WithId(Normal)->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(proModeNotePrefab));
    else container->BindMemoryPool<GameNoteController*, GameNoteController::Pool*>()->WithId(Normal)->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(normalBasicNotePrefab));
	container->BindMemoryPool<GameNoteController*, GameNoteController::Pool*>()->WithId(BurstSliderHead)->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderHeadNotePrefab));
	container->BindMemoryPool<BurstSliderGameNoteController*, BurstSliderGameNoteController::Pool*>()->WithId(BurstSliderElement)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderNotePrefab));
	container->BindMemoryPool<BurstSliderGameNoteController*, BurstSliderGameNoteController::Pool*>()->WithId(BurstSliderElementFill)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderFillPrefab));
	container->BindMemoryPool<BombNoteController*, BombNoteController::Pool*>()->WithInitialSize(35)->FromComponentInNewPrefab(PREFAB_INITIALIZE(bombNotePrefab));
	container->BindMemoryPool<ObstacleController*, ObstacleController::Pool*>()->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(obstaclePrefab));
	container->BindMemoryPool<SliderController*, SliderController::Pool::Short*>()->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(sliderShortPrefab));
	container->BindMemoryPool<SliderController*, SliderController::Pool::Medium*>()->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(sliderMediumPrefab));
	container->BindMemoryPool<SliderController*, SliderController::Pool::Long*>()->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(sliderLongPrefab));
	container->Bind<SliderController::Pool*>()->AsSingle();
	container->BindMemoryPool<NoteLineConnectionController*, NoteLineConnectionController::Pool*>()->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(noteLineConnectionControllerPrefab));
	container->BindMemoryPool<BeatLine*, BeatLine::Pool*>()->WithInitialSize(16)->FromComponentInNewPrefab(PREFAB_INITIALIZE(beatLinePrefab));
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(EffectPoolsManualInstaller_ManualInstallBindings, &EffectPoolsManualInstaller::ManualInstallBindings, void, EffectPoolsManualInstaller* self, ::Zenject::DiContainer* container, bool shortBeatEffect) {
    auto type = self->GetType();
	container->BindMemoryPool<FlyingTextEffect*, FlyingTextEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(flyingTextEffectPrefab));
	container->BindMemoryPool<FlyingScoreEffect*, FlyingScoreEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(flyingScoreEffectPrefab));
	container->BindMemoryPool<FlyingSpriteEffect*, FlyingSpriteEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(flyingSpriteEffectPrefab));
    if (shortBeatEffect) container->BindMemoryPool<BeatEffect*, BeatEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(shortBeatEffectPrefab));
    else container->BindMemoryPool<BeatEffect*, BeatEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(beatEffectPrefab));
	container->BindMemoryPool<NoteCutSoundEffect*, NoteCutSoundEffect::Pool*>()->WithInitialSize(80)->FromComponentInNewPrefab(PREFAB_INITIALIZE(noteCutSoundEffectPrefab));
	container->BindMemoryPool<BombCutSoundEffect*, BombCutSoundEffect::Pool*>()->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(bombCutSoundEffectPrefab));
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerConnectedPlayerInstaller_InstallBindings, &MultiplayerConnectedPlayerInstaller::InstallBindings, void, MultiplayerConnectedPlayerInstaller* self) {
    auto container = self->get_Container();
    auto type = self->GetType();
    
    auto playerSpecificSettingsForUserId = self->playersSpecificSettingsAtGameStartModel->GetPlayerSpecificSettingsForUserId(self->connectedPlayer->get_userId());

    auto difficultyBeatmap = self->sceneSetupData ? self->sceneSetupData->difficultyBeatmap : EmptyDifficultyBeatmap::New_ctor()->i_IDifficultyBeatmap();
    auto level = difficultyBeatmap->get_level();
    auto practiceSettings = self->sceneSetupData->practiceSettings;
    auto gameplayModifiers = self->sceneSetupData->gameplayModifiers;
    float songSpeedMul = gameplayModifiers->get_songSpeedMul();
    float startSongTime = 0.0f;
    if (practiceSettings)
    {
        startSongTime = (practiceSettings->startInAdvanceAndClearNotes ? std::max(0.0f, practiceSettings->startSongTime - 1.0f) : practiceSettings->startSongTime);
        songSpeedMul = practiceSettings->songSpeedMul;
    }
    container->Bind<ColorScheme*>()->FromInstance(ColorSchemeConverter::FromNetSerializable(playerSpecificSettingsForUserId->colorScheme))->AsSingle();
    container->Bind<ColorManager*>()->AsSingle();
    container->Bind<MultiplayerPlayerStartState>()->FromInstance(self->localPlayerStartState)->AsSingle();
    container->BindInstance<IConnectedPlayer*>(self->connectedPlayer);
    container->Bind<IConnectedPlayerBeatmapObjectEventManager*>()->FromComponentInNewPrefab(PREFAB_INITIALIZE(connectedPlayerBeatmapObjectEventManagerPrefab))->AsSingle();
    container->Bind(TypeArray<BeatmapObjectManager*, IBeatmapObjectSpawner*, System::IDisposable*>())->To(TypeArray<MultiplayerConnectedPlayerBeatmapObjectManager*>())->AsSingle();
    container->Bind<MultiplayerConnectedPlayerBeatmapObjectManager::InitData*>()->FromInstance(MultiplayerConnectedPlayerBeatmapObjectManager::InitData::New_ctor(gameplayModifiers->disappearingArrows, gameplayModifiers->ghostNotes, gameplayModifiers->get_notesUniformScale()))->AsSingle();
    container->Bind(TypeArray<IAudioTimeSource*, MultiplayerConnectedPlayerSongTimeSyncController*>())->FromComponentInNewPrefab(PREFAB_INITIALIZE(connectedPlayerAudioTimeSyncControllerPrefab))->AsSingle();
    container->Bind<MultiplayerConnectedPlayerSongTimeSyncController::InitData*>()->FromInstance(MultiplayerConnectedPlayerSongTimeSyncController::InitData::New_ctor(startSongTime, level->i_IPreviewBeatmapLevel()->get_songTimeOffset(), songSpeedMul))->AsSingle();
    bool oneSaberMode = difficultyBeatmap->get_parentDifficultyBeatmapSet() && difficultyBeatmap->get_parentDifficultyBeatmapSet()->get_beatmapCharacteristic()->get_numberOfColors() == 1;
    container->Bind<SaberManager::InitData*>()->FromInstance(SaberManager::InitData::New_ctor(oneSaberMode, SaberTypeExtensions::MainSaber(playerSpecificSettingsForUserId->leftHanded)))->AsSingle();
    container->Bind<SaberModelController::InitData*>()->FromInstance(SaberModelController::InitData::New_ctor({1.0f, 1.0f, 1.0f, self->sceneSetupData->playerSpecificSettings->saberTrailIntensity}))->AsSingle();

    auto Normal = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::Normal);
    auto BurstSliderHead = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderHead);
    auto BurstSliderElement = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElement);
    auto BurstSliderElementFill = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElementFill);

    container->BindMemoryPool<MultiplayerConnectedPlayerGameNoteController*, MultiplayerConnectedPlayerGameNoteController::Pool*>()->WithId(Normal)->WithInitialSize(50)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerGameNoteControllerPrefab));
    container->BindMemoryPool<MultiplayerConnectedPlayerGameNoteController*, MultiplayerConnectedPlayerGameNoteController::Pool*>()->WithId(BurstSliderHead)->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerBurstSliderHeadGameNoteControllerPrefab));
    container->BindMemoryPool<MultiplayerConnectedPlayerGameNoteController*, MultiplayerConnectedPlayerGameNoteController::Pool*>()->WithId(BurstSliderElement)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerBurstSliderGameNoteControllerPrefab));
    container->BindMemoryPool<MultiplayerConnectedPlayerGameNoteController*, MultiplayerConnectedPlayerGameNoteController::Pool*>()->WithId(BurstSliderElementFill)->WithInitialSize(20)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerBurstSliderFillControllerPrefab));
    container->BindMemoryPool<MultiplayerConnectedPlayerBombNoteController*, MultiplayerConnectedPlayerBombNoteController::Pool*>()->WithInitialSize(6)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerBombNoteControllerPrefab));
    container->BindMemoryPool<MultiplayerConnectedPlayerObstacleController*, MultiplayerConnectedPlayerObstacleController::Pool*>()->WithInitialSize(4)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerObstacleControllerPrefab));
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerLobbyInstaller_InstallBindings, &MultiplayerLobbyInstaller::InstallBindings, void, MultiplayerLobbyInstaller* self) {
	auto container = self->get_Container();
    auto type = self->GetType();
    container->BindMemoryPool<MultiplayerLobbyAvatarPlace*, MultiplayerLobbyAvatarPlace::Pool*>()->WithInitialSize(4)->FromComponentInNewPrefab(PREFAB_INITIALIZE(multiplayerAvatarPlacePrefab));
    container->BindFactory<IConnectedPlayer*, MultiplayerLobbyAvatarController*, MultiplayerLobbyAvatarController::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(LobbyAvatarInstaller*), PREFAB_INITIALIZE(multiplayerLobbyAvatarControllerPrefab));
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(MultiplayerPlayersManager_BindPlayerFactories, &MultiplayerPlayersManager::BindPlayerFactories, void, MultiplayerPlayersManager* self, ::MultiplayerPlayerLayout layout) {
    auto container = self->container;
    auto type = self->GetType();
    container->BindFactory<MultiplayerPlayerStartState, MultiplayerLocalInactivePlayerFacade*, MultiplayerLocalInactivePlayerFacade::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(MultiplayerLocalPlayerInstaller*), PREFAB_INITIALIZE(inactiveLocalPlayerControllerPrefab));
    if (layout == MultiplayerPlayerLayout::Duel) {
        container->BindFactory<MultiplayerPlayerStartState, MultiplayerLocalActivePlayerFacade*, MultiplayerLocalActivePlayerFacade::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(MultiplayerLocalPlayerInstaller*), PREFAB_INITIALIZE(activeLocalPlayerDuelControllerPrefab));
        container->BindFactory<IConnectedPlayer*, MultiplayerPlayerStartState, MultiplayerConnectedPlayerFacade*, MultiplayerConnectedPlayerFacade::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(MultiplayerConnectedPlayerInstaller*), PREFAB_INITIALIZE(connectedPlayerDuelControllerPrefab));
    } else {
        container->BindFactory<MultiplayerPlayerStartState, MultiplayerLocalActivePlayerFacade*, MultiplayerLocalActivePlayerFacade::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(MultiplayerLocalPlayerInstaller*), PREFAB_INITIALIZE(activeLocalPlayerControllerPrefab));
        container->BindFactory<IConnectedPlayer*, MultiplayerPlayerStartState, MultiplayerConnectedPlayerFacade*, MultiplayerConnectedPlayerFacade::Factory*>()->FromSubContainerResolve()->ByNewContextPrefab(csTypeOf(MultiplayerConnectedPlayerInstaller*), PREFAB_INITIALIZE(connectedPlayerControllerPrefab));
    }
    self->activeLocalPlayerFactory = container->Resolve<MultiplayerLocalActivePlayerFacade::Factory*>();
    self->inactiveLocalPlayerFactory = container->Resolve<MultiplayerLocalInactivePlayerFacade::Factory*>();
    self->connectedPlayerFactory = container->Resolve<MultiplayerConnectedPlayerFacade::Factory*>();
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(NoteDebrisPoolInstaller_InstallBindings, &NoteDebrisPoolInstaller::InstallBindings, void, NoteDebrisPoolInstaller* self) {
	auto container = self->get_Container();
    auto type = self->GetType();

    bool hd = self->noteDebrisHDConditionVariable->get_value();
    auto Normal = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::Normal);
    auto BurstSliderHead = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderHead);
    auto BurstSliderElement = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElement);

    if (hd) {
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(Normal)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(normalNoteDebrisHDPrefab));
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(BurstSliderHead)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderHeadNoteDebrisHDPrefab));
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(BurstSliderElement)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderElementNoteHDPrefab));
    } else {
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(Normal)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(normalNoteDebrisLWPrefab));
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(BurstSliderHead)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderHeadNoteDebrisLWPrefab));
        container->BindMemoryPool<NoteDebris*, NoteDebris::Pool*>()->WithId(BurstSliderElement)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(burstSliderElementNoteLWPrefab));
    }
}

/// Does not call orig! 
/// FIXME: On game update, check if this method still matches!
MAKE_AUTO_HOOK_ORIG_MATCH(FakeMirrorObjectsInstaller_InstallBindings, &FakeMirrorObjectsInstaller::InstallBindings, void, FakeMirrorObjectsInstaller* self) {
	auto container = self->get_Container();
    auto type = self->GetType();

    auto Normal = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::Normal);
    auto BurstSliderHead = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderHead);
    auto BurstSliderElement = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElement);
    auto BurstSliderElementFill = il2cpp_functions::value_box(classof(NoteData::GameplayType), (void*)&NoteData::GameplayType::BurstSliderElementFill);

    if (self->mirrorGraphicsSettings->get_value() >= self->mirrorRendererGraphicsSettingsPresets->presets.size())
    {
        self->mirrorGraphicsSettings->set_value(self->mirrorRendererGraphicsSettingsPresets->presets.size() - 1);
    }
    bool flag = self->mirrorRendererGraphicsSettingsPresets->presets[self->mirrorGraphicsSettings->get_value()]->mirrorType == MirrorRendererGraphicsSettingsPresets::Preset::MirrorType::FakeMirror;
    bool flag2 = false;
    for (auto c : ListWrapper<Zenject::BindingId>{container->get_AllContracts()}) {
        if (csTypeOf(BeatmapObjectManager*)->IsAssignableFrom(c.get_Type())) {
            flag2 = true;
            break;
        }
    }
    if (!flag || !flag2)
    {
        container->Bind<FakeReflectionDynamicObjectsState>()->FromInstance(FakeReflectionDynamicObjectsState::Disabled)->AsSingle();
        return;
    }
    container->Bind<FakeReflectionDynamicObjectsState>()->FromInstance(FakeReflectionDynamicObjectsState::Enabled)->AsSingle();
    container->BindMemoryPool<MirroredGameNoteController*, MirroredGameNoteController::Pool*>()->WithId(Normal)->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredGameNoteControllerPrefab));
    container->BindMemoryPool<MirroredGameNoteController*, MirroredGameNoteController::Pool*>()->WithId(BurstSliderHead)->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredBurstSliderHeadGameNoteControllerPrefab));
    container->BindMemoryPool<MirroredGameNoteController*, MirroredGameNoteController::Pool*>()->WithId(BurstSliderElement)->WithInitialSize(40)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredBurstSliderGameNoteControllerPrefab));
    container->BindMemoryPool<MirroredGameNoteController*, MirroredGameNoteController::Pool*>()->WithId(BurstSliderElementFill)->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredBurstSliderFillControllerPrefab));
    container->BindMemoryPool<MirroredBombNoteController*, MirroredBombNoteController::Pool*>()->WithInitialSize(35)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredBombNoteControllerPrefab));
    container->BindMemoryPool<MirroredObstacleController*, MirroredObstacleController::Pool*>()->WithInitialSize(25)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredObstacleControllerPrefab));
    container->BindMemoryPool<MirroredSliderController*, MirroredSliderController::Pool*>()->WithInitialSize(10)->FromComponentInNewPrefab(PREFAB_INITIALIZE(mirroredSliderControllerPrefab));
    container->Bind<MirroredBeatmapObjectManager*>()->To<MirroredBeatmapObjectManager*>()->AsSingle()->NonLazy();
}