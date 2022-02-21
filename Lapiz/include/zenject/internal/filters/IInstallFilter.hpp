#pragma once

namespace lapiz::zenject::internal::filters {
    class IInstallFilter {
        bool ShouldInstall(ContextBinding binding);
    };
}
