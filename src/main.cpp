#include "main.hpp"
#include "utilities/hooking.hpp"
#include "utilities/logging.hpp"

#include "zenject/Zenjector.hpp"
#include "Location.hpp"

#include "utilities/logging.hpp"

static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
    INFO(MOD_ID " v" VERSION " completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();

    INFO("Installing Zenject bindings and hooks..");

    Hooks::InstallHooks(getLogger());
}
