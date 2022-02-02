#include "enum/LocationEnum.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

namespace z {
    class Zenjector {
      public:
        /// @brief Installs a custom installer alongside another installer.
        template<class T>
        void Install(T args[]) {
            
        };

        /// @brief Install bindings to a custom location with a backing installer(s).
        void Install(z::Location) {

        };

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
