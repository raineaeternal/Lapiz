#include "main.hpp"
#include "include/utilities/HookingUtility.hpp"

#include "include/zenject/Zenjector.hpp"
#include "include/enum/LocationEnum.hpp"

#include "include/Installer.hpp"
#inlucde "CustomType.hpp"

#include "paper/shared/logger.hpp"
#include "paper/shared/log_level.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Completed setup!");
}

using namespace Lapiz::Zenject;
using namespace Tests;

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    if (!Paper::Logger::IsInited()) {
        Paper::Logger::Init("/sdcard/Android/data/com.beatgames.beatsaber/files/logs");
    }

    Paper::Logger::fmtLog<Paper::LogLevel::INF>("Logger initialized..");
    Paper::Logger::fmtLog<Paper::LogLevel::INF>("Installing Zenject bindings and hooks..");

    Zenjector::Install(Location::App, [](void* container) {
        container;
    });
    Zenjector::Install(Location::GameCore, [](auto container) {
        container;
    });
    Zenjector::Install<MyMenuInstaller, CustomType>(Location::None);

    Lapiz::HookingUtility::InstallHooks(getLogger());
}
