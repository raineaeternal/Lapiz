#include "tests.hpp"

#include "beatsaber-hook/shared/hooking.hpp"

#include "GlobalNamespace/GameCoreSceneSetup.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"

#include "affinity/HookHandle.hpp"
#include "affinity/hooking.hpp"
#include "utilities/logging.hpp"

#include "zenject/Zenjector.hpp"
#include "zenject/Location.hpp"
#include "scotland2/shared/modloader.h"

// Location::GameCore hook without an injected parameter: fires once the GameCore scene's
// own Zenject bindings are torn down.
MAKE_AFFINITY_HOOK(gamecore_no_inject_test,
                   (i2c::metadata_getter<&GlobalNamespace::GameCoreSceneSetup::OnDestroy>::method_info()), void,
                   GlobalNamespace::GameCoreSceneSetup* self) {
    INFO("gamecore_no_inject_test hook fired, self -> {}", fmt::ptr(self));
    gamecore_no_inject_test(self);
}

// Location::GameCore hook with an injected parameter: resolves the GameplayCoreSceneSetupData
// (guaranteed available at GameCore scope, see Lapiz::Zenject::Location::GameCore) whenever
// GameCore's own Zenject bindings are installed.
MAKE_AFFINITY_HOOK_INJECTED(gamecore_injected_test, GlobalNamespace::GameplayCoreSceneSetupData*,
                            (i2c::metadata_getter<&GlobalNamespace::GameCoreSceneSetup::InstallBindings>::method_info()), void,
                            GlobalNamespace::GameCoreSceneSetup* self) {
    INFO("gamecore_injected_test hook fired, injected setup data -> {}", fmt::ptr(Injected.ptr()));
    gamecore_injected_test(self);
}

// Same target as gamecore_no_inject_test (GameCoreSceneSetup::OnDestroy), but resolved with
// MAKE_AFFINITY_HOOK_MATCH instead of a manual i2c::metadata_getter<...>::method_info() call: the method
// pointer &GameCoreSceneSetup::OnDestroy is matched against this hook's own return type/parameters to find
// the MethodInfo. Stacking a second hook onto the same target this way is exactly what the affinity system
// is for - multiple mods installing hooks onto the same method without stepping on each other.
MAKE_AFFINITY_HOOK_MATCH(gamecore_match_test, &GlobalNamespace::GameCoreSceneSetup::OnDestroy, void,
                         GlobalNamespace::GameCoreSceneSetup* self) {
    INFO("gamecore_match_test hook fired, self -> {}", fmt::ptr(self));
    gamecore_match_test(self);
}

// Quick startup sanity checks: verify each hook's target method resolves, without needing a live game/container.
TEST(gamecore_hook_no_inject_resolves) {
    auto* addr = hook_gamecore_no_inject_test::addr();
    if (!addr) {
        LOG_FAIL("Could not resolve address for gamecore_no_inject_test (GameCoreSceneSetup::OnDestroy)");
        return;
    }
    LOG_OK("Resolved gamecore_no_inject_test address -> {}", fmt::ptr(addr));
}

TEST(gamecore_hook_injected_resolves) {
    auto* addr = hook_gamecore_injected_test::addr();
    if (!addr) {
        LOG_FAIL("Could not resolve address for gamecore_injected_test (GameCoreSceneSetup::InstallBindings)");
        return;
    }
    LOG_OK("Resolved gamecore_injected_test address -> {}", fmt::ptr(addr));
}

TEST(gamecore_hook_match_resolves) {
    auto* addr = hook_gamecore_match_test::addr();
    if (!addr) {
        LOG_FAIL("Could not resolve method info for gamecore_match_test (GameCoreSceneSetup::OnDestroy)");
        return;
    }
    LOG_OK("Resolved gamecore_match_test method info -> {}", fmt::ptr(addr));
}

// Registers all three hooks onto the real Location::GameCore container using the Lapiz affinity API
// (AFFINITY_HOOK(...).install(container)) - one with an injected parameter, one without, and one resolved
// via MAKE_AFFINITY_HOOK_MATCH stacked after gamecore_no_inject_test on the same OnDestroy target.
// Zenjector::Get() forces Lapiz's own load()/type registration to have run regardless of mod order,
// so this is safe to call here. HookHandle::Install logs "Hook: {} installed with flamingo!"
// (or aborts on failure) the moment the player actually loads into a level and GameCore's
// bindings are installed - the container test only completes once that happens in a live game.
TEST(gamecore_hook_install_onto_container) {
    static modloader::ModInfo const modInfo{MOD_ID, VERSION, 0};
    static auto const logger = Paper::ConstLoggerContext(MOD_ID "_GameCoreTests");

    ::Lapiz::Zenject::Zenjector::Get(modInfo)->Install(::Lapiz::Zenject::Location::GameCore, [](::Zenject::DiContainer* container) {
        AFFINITY_HOOK(logger, modInfo, gamecore_no_inject_test).install(container);
        AFFINITY_HOOK(logger, modInfo, gamecore_injected_test).install(container);
        AFFINITY_HOOK(logger, modInfo, gamecore_match_test).after(modInfo.id).install(container);
    });
    LOG_OK("Registered gamecore_no_inject_test, gamecore_injected_test, and gamecore_match_test onto Location::GameCore");
}
