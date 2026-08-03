#include "affinity/HookHandle.hpp"

DEFINE_TYPE(Lapiz::Affinity, HookHandle);

namespace Lapiz::Affinity {
    void HookHandle::ctor() {}

    // Called by Zenject once this instance is resolved as part of the container's root resolution
    // (requires the binding to be marked NonLazy - see AffinityHookBuilder::install).
    void HookHandle::Initialize() { Install(); }

    // Called by Zenject when the owning DiContainer is disposed (e.g. on scene/context teardown),
    // since AsCached()-bound IDisposable instances are tracked and disposed automatically.
    void HookHandle::Dispose() { Uninstall(); }
}
