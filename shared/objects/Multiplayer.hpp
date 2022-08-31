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
    using ConnectedPlayerDuelRegistration = ::Lapiz::Objects::Registration<"connectedPlayerDuelControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*>;
    using ConnectedPlayerRegistration = ::Lapiz::Objects::Registration<"connectedPlayerControllerPrefab", GlobalNamespace::MultiplayerConnectedPlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*>;
    using LobbyAvatarPlaceRegistration = ::Lapiz::Objects::Registration<"multiplayerAvatarPlacePrefab", GlobalNamespace::MultiplayerLobbyAvatarPlace*, GlobalNamespace::MultiplayerLobbyInstaller*>;
    using LobbyAvatarRegistration = ::Lapiz::Objects::Registration<"multiplayerLobbyAvatarControllerPrefab", GlobalNamespace::MultiplayerLobbyAvatarController*, GlobalNamespace::MultiplayerLobbyInstaller*>;
    using LocalActivePlayerDuelRegistration = ::Lapiz::Objects::Registration<"activeLocalPlayerDuelControllerPrefab", GlobalNamespace::MultiplayerLocalActivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*>;
    using LocalActivePlayerRegistration = ::Lapiz::Objects::Registration<"activeLocalPlayerControllerPrefab", GlobalNamespace::MultiplayerLocalActivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*>;
    using LocalInactivePlayerRegistration = ::Lapiz::Objects::Registration<"inactiveLocalPlayerControllerPrefab", GlobalNamespace::MultiplayerLocalInactivePlayerFacade*, GlobalNamespace::MultiplayerPlayersManager*>;
}

DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::ConnectedPlayerDuelRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::ConnectedPlayerRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::LobbyAvatarPlaceRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::LobbyAvatarRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::LocalActivePlayerDuelRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::LocalActivePlayerRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");
DEFINE_IL2CPP_ARG_TYPE(Lapiz::Objects::Multiplayer::LocalInactivePlayerRegistration*, "Lapiz::Objects", "TemplateRedecoratorRegistration");