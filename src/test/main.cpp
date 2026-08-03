#include "_config.h"
#include "tests.hpp"
#include "utilities/logging.hpp"

#include "scotland2/shared/modloader.h"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

std::vector<std::function<void()>> tests = {};

// Called at the early stages of game loading
LAPIZ_EXPORT_FUNC void setup(CModInfo* info) {
    info->id = MOD_ID;
    info->version = VERSION;
    info->version_long = 0;

    INFO(MOD_ID " tests v" VERSION " completed setup!");
}

// Called once the game (and Lapiz) has finished loading - runs every registered TEST()
LAPIZ_EXPORT_FUNC void late_load() {
    INFO("Beginning tests...");
    for (auto const& test : tests) {
        try {
            test();
        } catch (std::exception const& e) {
            ERROR("Exception in test: {}", e.what());
        } catch (...) {
            ERROR("Unknown exception in test");
        }
    }
    INFO("Finished tests!");
}
