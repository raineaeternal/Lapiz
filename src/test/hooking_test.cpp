#include "tests.hpp"

#include "System/String.hpp"

#include "beatsaber-hook/shared/hooking.hpp"

#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/SaberClashEffect.hpp"

#include "affinity/HookHandle.hpp"
#include "affinity/hooking.hpp"
#include "utilities/logging.hpp"


DECLARE_CLASS_CODEGEN(Test, TestInjected, System::Object) {
  DECLARE_CTOR(ctor);
  DECLARE_INJECT_FIELD(GlobalNamespace::SaberManager*, saberManager);
};

DEFINE_TYPE(Test, TestInjected);

namespace Test {
    void TestInjected::ctor() {}
}

MAKE_AFFINITY_HOOK_INJECTED(test2, ::Test::TestInjected*,
                            (i2c::metadata_getter<&GlobalNamespace::SaberClashEffect::Start>::method_info()), void, GlobalNamespace::SaberClashEffect* self) {
    auto saberManager = Injected->saberManager;
    INFO("Injected value: {}", fmt::ptr(Injected.ptr()));
    INFO("SaberManager: {}", fmt::ptr(saberManager));
}

// Actually installing this hook requires a live Zenject DiContainer from the running game
// (see Lapiz::Affinity::AffinityHookBuilder::install), which isn't available from this
// standalone test mod's late_load. This only verifies the hook's target method resolves.
TEST(affinity_hook_injected_resolves) {
    auto* addr = hook_test2::addr();
    if (!addr) {
        LOG_FAIL("Could not resolve address for hook_test2 (SaberClashEffect::Start)");
        return;
    }
    LOG_OK("Resolved hook_test2 address -> {}", fmt::ptr(addr));
}

