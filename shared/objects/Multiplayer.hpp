#pragma once

#include "RegistrationHelper.hpp"

#include "GlobalNamespace/MultiplayerConnectedPlayerFacade.hpp"
#include "GlobalNamespace/MultiplayerPlayersManager.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarPlace.hpp"
#include "GlobalNamespace/MultiplayerLobbyInstaller.hpp"
#include "GlobalNamespace/MultiplayerLobbyAvatarController.hpp"
#include "GlobalNamespace/MultiplayerLocalActivePlayerFacade.hpp"
#include "GlobalNamespace/MultiplayerLocalInactivePlayerFacade.hpp"

namespace Lapiz::Objects::Multiplayer {
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(ConnectedPlayerDuelRegistration, "connectedPlayerDuelControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(ConnectedPlayerRegistration, "connectedPlayerControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LobbyAvatarPlaceRegistration, "multiplayerAvatarPlacePrefab", GlobalNamespace::MultiplayerLobbyAvatarPlace*, GlobalNamespace::MultiplayerLobbyInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LobbyAvatarRegistration, "multiplayerLobbyAvatarControllerPrefab", GlobalNamespace::MultiplayerLobbyAvatarController*, GlobalNamespace::MultiplayerLobbyInstaller*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LocalActivePlayerDuelRegistration, "activeLocalPlayerDuelControllerPrefab", GlobalNamespace::MultiplayerLocalActivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LocalActivePlayerRegistration, "activeLocalPlayerControllerPrefab", GlobalNamespace::MultiplayerLocalActivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*);
    LAPIZ_REDECORATION_REGISTRATION_HELPER_DEFINITION(LocalInactivePlayerRegistration, "inactiveLocalPlayerControllerPrefab", GlobalNamespace::MultiplayerLocalInactivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*);
}