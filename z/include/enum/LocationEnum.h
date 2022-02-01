#pragma once

namespace z {
    enum class Location {
        None = 0,
        App = 1,
        Menu = 2
        StandardPlayer = 4,
        CampaignPlayer = 8,
        Multi = 16,
        Player = StandardPlayer | CampaignPlayer | Multi,
        Tutorial = 32,
        GameCore = 64,
        MultiplayerCore = 128,
        Singleplayer = StandardPlayer | CampaignPlayer | Tutorial,
        ConnectedPlayer = 256
    };

    inline Location operator|(Location a, Location b)
    {return static_cast<Location>(static_cast<int>(a) | static_cast<int>(b));}

    inline Location operator&(Location a, Location b)
    {return static_cast<Location>(static_cast<int>(a) & static_cast<int>(b));}

    inline bool HasFlag(Location location, Location flag) {
        return (location & flag) == flag;
    }

    static std::unordered_set<Il2CppClass*> getInstallerForLocation(Location location) {
        using namespace GlobalNamespace;

        std::unordered_set<Il2CppClass*> installerTypes;

        if (HasFlag(location, Location::App))
            installerTypes.emplace(classof(PCAppInit*));
        if (HasFlag(location, Location::Menu))
            installerTypes.emplace(classof(MainSettingsMenuViewControllersInstaller*));
        if (HasFlag(location, Location::StandardPlayer))
            installerTypes.emplace(classof(StandardGameplayInstaller*));
        if (HasFlag(location, Location::CampaignPlayer))
            installerTypes.emplace(classof(MissionGameplayInstaller*));
        if (HasFlag(location, Location::MultiPlayer))
            installerTypes.emplace(classof(MultiplayerLocalPlayerInstaller*));
        if (HasFlag(location, Location::Tutorial))
            installerTypes.emplace(classof(TutorialInstaller*));
        if (HasFlag(location, Location::GameCore))
            installerTypes.emplace(classof(GameCoreSceneSetup*));
        if (HasFlag(location, Location::MultiplayerCore))
            installerTypes.emplace(classof(MultiplayerCoreInstaller*));
        if (HasFlag(location, Location::ConnectedPlayer))
            installerTypes.emplace(classof(MultiplayerConnectedPlayerInstaller*));

        return installerTypes;
}
