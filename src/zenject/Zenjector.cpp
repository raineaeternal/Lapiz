#include "zenject/Zenjector.hpp"
#include "internal/InstallSet.hpp"
#include "internal/InstallInstruction.hpp"
#include "internal/filters/TypedInstallFilter.hpp"
#include "internal/filters/MultiTypedInstallFilter.hpp"

using namespace Lapiz::Zenject::Internal;
using namespace Lapiz::Zenject::Internal::Filters;

namespace Lapiz::Zenject {
    void Zenjector::Install(Zenject::Location location, ZenjectorCallback installCallback) {
        for (auto t : InstallerForLocation(location)) {
            _installInstructions.emplace(new InstallInstruction(t, installCallback));
        }
    }

    void Zenjector::Install(Il2CppClass* baseInstallerT, ZenjectorCallback installCallback) {
        _installInstructions.emplace(new InstallInstruction(baseInstallerT, installCallback));
    }

    void Zenjector::Install(Il2CppClass* customInstallerT, Il2CppClass* baseInstallerT, ArrayW<Il2CppObject*> parameters) {
        auto filter = new TypedInstallFilter(baseInstallerT);
        _installSets.emplace(new InstallSet(customInstallerT, filter, (parameters && parameters.size() > 0) ? parameters : nullptr));
    }

    void Zenjector::Install(Il2CppClass* customInstallerT, Zenject::Location location, ArrayW<Il2CppObject*> parameters) {
        auto filter = new MultiTypedInstallFilter(InstallerForLocation(location));
        _installSets.emplace(new InstallSet(customInstallerT, filter, (parameters && parameters.size() > 0) ? parameters : nullptr));
    }
}