#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"

#include "GlobalNamespace/PCAppInit.hpp"
#include "GlobalNamespace/MainSettingsMenuViewControllersInstaller.hpp"
#include "GlobalNamespace/StandardGameplayInstaller.hpp"
#include "GlobalNamespace/MissionGameplayInstaller.hpp"
#include "GlobalNamespace/MultiplayerLocalActivePlayerInstaller.hpp"
#include "GlobalNamespace/TutorialInstaller.hpp"
#include "GlobalNamespace/GameCoreSceneSetup.hpp"
#include "GlobalNamespace/MultiplayerCoreInstaller.hpp"
#include "GlobalNamespace/MultiplayerConnectedPlayerInstaller.hpp"
#include "GlobalNamespace/MultiplayerLocalPlayerInstaller.hpp"
#include "GlobalNamespace/MultiplayerLocalInactivePlayerInstaller.hpp"

MAKE_AUTO_HOOK_MATCH(PCAppInit_InstallBindings, &GlobalNamespace::PCAppInit::InstallBindings, void, GlobalNamespace::PCAppInit* self) {
    PCAppInit_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MainSettingsMenuViewControllersInstaller_InstallBindings, &GlobalNamespace::MainSettingsMenuViewControllersInstaller::InstallBindings, void, GlobalNamespace::MainSettingsMenuViewControllersInstaller* self) {
    MainSettingsMenuViewControllersInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(StandardGameplayInstaller_InstallBindings, &GlobalNamespace::StandardGameplayInstaller::InstallBindings, void, GlobalNamespace::StandardGameplayInstaller* self) {
    StandardGameplayInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MissionGameplayInstaller_InstallBindings, &GlobalNamespace::MissionGameplayInstaller::InstallBindings, void, GlobalNamespace::MissionGameplayInstaller* self) {
    MissionGameplayInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MultiplayerLocalActivePlayerInstaller_InstallBindings, &GlobalNamespace::MultiplayerLocalActivePlayerInstaller::InstallBindings, void, GlobalNamespace::MultiplayerLocalActivePlayerInstaller* self) {
    MultiplayerLocalActivePlayerInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(TutorialInstaller_InstallBindings, &GlobalNamespace::TutorialInstaller::InstallBindings, void, GlobalNamespace::TutorialInstaller* self) {
    TutorialInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(GameCoreSceneSetup_InstallBindings, &GlobalNamespace::GameCoreSceneSetup::InstallBindings, void, GlobalNamespace::GameCoreSceneSetup* self) {
    GameCoreSceneSetup_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MultiplayerCoreInstaller_InstallBindings, &GlobalNamespace::MultiplayerCoreInstaller::InstallBindings, void, GlobalNamespace::MultiplayerCoreInstaller* self) {
    MultiplayerCoreInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MultiplayerConnectedPlayerInstaller_InstallBindings, &GlobalNamespace::MultiplayerConnectedPlayerInstaller::InstallBindings, void, GlobalNamespace::MultiplayerConnectedPlayerInstaller* self) {
    MultiplayerConnectedPlayerInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MultiplayerLocalPlayerInstaller_InstallBindings, &GlobalNamespace::MultiplayerLocalPlayerInstaller::InstallBindings, void, GlobalNamespace::MultiplayerLocalPlayerInstaller* self) {
    MultiplayerLocalPlayerInstaller_InstallBindings(self);
}

MAKE_AUTO_HOOK_MATCH(MultiplayerLocalInactivePlayerInstaller_InstallBindings, &GlobalNamespace::MultiplayerLocalInactivePlayerInstaller::InstallBindings, void, GlobalNamespace::MultiplayerLocalInactivePlayerInstaller* self) {
    MultiplayerLocalInactivePlayerInstaller_InstallBindings(self);
}
