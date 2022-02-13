#pragma once

namespace z::zenject::internal::filters {
    class IInstallFilter {
        bool ShouldInstall(ContextBinding binding);
    };
}
