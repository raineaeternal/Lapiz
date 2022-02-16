#include "enum/LocationEnum.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "System/Collections/Generic/IEnumerable_1.hpp"
#include "Zenject/IInstaller.hpp"

namespace z::zenject {
    class Zenjector {
      public:
        /// @brief Installs a custom installer alongside another installer.
        template<class TCustomInstaller>
        requires (std::is_convertible_v<TCustomInstaller, Zenject::IInstaller>)
        void Install(zenject::Location location) {
            std::unordered_set < Il2CppClass * > installerTypes = zenject::getInstallerForLocation(location);
        };

        /// @brief Install bindings to a custom location with a backing installer(s).
        // void Install(int) {

        // };

        /// @brief Install bindings to another installer without a custom installer
        template<class TKey>
        void UseMetadataBinder(TKey) {

        };

        /// @brief Lets you use Lapiz' HTTP service system. Not implemented, nor used currently.
        void UseHttpService() {

        };

        /// @brief Makes it possible for Quest mods to sync to an external service, like GitHub. Not implemented, nor used currently.
        void UseLapizSync() {

        };
    };
}
