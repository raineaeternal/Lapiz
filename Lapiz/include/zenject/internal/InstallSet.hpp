#pragma once

#include "System/Type.hpp"

namespace lapiz::zenject::internal {

    struct InstallSet
    {
        System::Type installerType;
        IInstallFilter installFilter;

        object[]? initialParameters;

        InstallSet(System::Type installerType, IInstallFilter installFilter, object[]? initialParameters = null)
        {
            this->installerType = installerType;
            this->installFilter = installFilter;
            this->initialParameters = initialParameters;
        }
    };
}
