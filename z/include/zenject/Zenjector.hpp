#include "enum/LocationEnum.hpp"
#include "beatsaber-hook/shared/utils/logging.hpp"

namespace z {
    class Zenjector {

        /// @brief Installs a custom installer alongside another installer.
        template<class T>
        void Install(T args[]);

        /// @brief Install bindings to a custom location with a backing installer(s).
        void Install(z::Location);

        /// @brief Install bindings to another installer without a custom installer
        template<class TKey>
        void UseMetadataBinder(TKey);

        /// @brief Uses Ferns FMT packages on QPM. Not implemented, nor used currently.
        // void UseLogger();

        /// @brief Lets you use Lapiz' HTTP service system. Not implemented, nor used currently.
        // void UseHttpService();

        /// @brief Makes it possible for Quest mods to sync to a github service. Not implemented, nor used currently.
        // void UseLapizSync();
    };
}
