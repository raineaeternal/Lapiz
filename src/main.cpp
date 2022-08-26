#include "main.hpp"
#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"

#include "zenject/Zenjector.hpp"
#include "enum/LocationEnum.hpp"

#include "CustomType.hpp"

#include "utilities/logging.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;
    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    if (!Paper::Logger::IsInited()) {
        Paper::Logger::Init("/sdcard/Android/data/com.beatgames.beatsaber/files/logs");
    }

    Paper::Logger::fmtLog<Paper::LogLevel::INF>("Logger initialized..");
    Paper::Logger::fmtLog<Paper::LogLevel::INF>("Installing Zenject bindings and hooks..");

    Hooks::InstallHooks(getLogger());
}
