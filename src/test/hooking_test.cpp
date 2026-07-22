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

MAKE_AFFINITY_HOOK_INJECTED(test2, ::Test::TestInjected*,
                            (i2c::metadata_getter<&GlobalNamespace::SaberClashEffect::Start>::method_info()), void, GlobalNamespace::SaberClashEffect* self) {
    auto saberManager = Injected->saberManager;
    INFO("Injected value: {}", fmt::ptr(Injected));
    INFO("SaberManager: {}", fmt::ptr(saberManager));
}

