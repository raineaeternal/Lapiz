#pragma once

namespace Lapiz::Zenject::internal::filters {
    class IInstallFilter {
        bool ShouldInstall(ContextBinding binding);
    };
}
