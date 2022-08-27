#pragma once

#include "Location.hpp"
#include "utilities/logging.hpp"
#include "System/Collections/Generic/IEnumerable_1.hpp"
#include "Zenject/IInstaller.hpp"

using namespace Zenject;

namespace Lapiz::Zenject {
    class Zenjector {
      public:
        /// @brief Installs a custom installer alongside custom type.
        /// @tparam TCustomInstaller Your installer class. Required for this to work.
        /// @tparam TCustomType A custom type to make Garbage Collection not cause potential Null pointer dereferences unnecessarily.
        /// @param location Required to install something to the DiContainer location.
        template<class TCustomInstaller, class TCustomType>
        requires (std::is_convertible_v<TCustomInstaller, IInstaller>)
        static void Install(Zenject::Location location) {
            std::unordered_set < Il2CppClass * > installerTypes = Zenject::getInstallerForLocation(location);
        };

        /// @brief Installs the Binding instructions and methods to the specified domain location. Recommend using this only for the App domain.
        /// @param location Required to install to the DiContainer.
        /// @param installCallback Your lambda you install to the specified domain with.
        static void Install(Zenject::Location location, std::function<void(DiContainer*)> installCallback) {
            std::unordered_set < Il2CppClass * > installerTypes = Zenject::InstallerForLocation(location);
        };

        /// @brief Install bindings to another installer without a custom installer
        static void UseMetadataBinder() {};

        /// @brief Lets you use Lapiz' HTTP service system. Not implemented, nor used currently.
        static void UseHttpService() {};

        /// @brief Makes it possible for Quest mods to sync to an external service, like GitHub. Not implemented, nor used currently.
        static void UseLapizSync() {};
    };
}
