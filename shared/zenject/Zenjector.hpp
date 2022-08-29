#pragma once

#include "Location.hpp"
#include "utilities/logging.hpp"
#include "System/Collections/Generic/IEnumerable_1.hpp"
#include "../concepts.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/SceneDecoratorContext.hpp"

namespace Lapiz::Zenject {
    class ZenjectManager;

    namespace Internal {
        class InstallSet;
        class InstallInstruction;
        class MutateSet;
    }

    typedef std::function<void(::Zenject::DiContainer*)> ZenjectorCallback;
    class Zenjector {
        public:

            /// @brief Installs a custom installer to a location with a backing installer(s).
            /// @tparam T The type of your custom installer.
            /// @param location The location to install it to.
            /// @param parameters Parameters for the constructor of the installer. This will override Zenject's constructor injection on this installer,
            /// and the installer type cannot be a MonoInstaller if using this.
            template<Lapiz::concepts::IInstaller T>
            inline void Install(Zenject::Location location, ArrayW<Il2CppObject*> parameters) {
                Install(classof(T), location, parameters);
            };
            

            /// @brief Installs a custom installer to a location with a backing installer(s).
            /// @tparam TCustomInstaller The type of your custom installer.
            /// @tparam TBaseInstaller The installer to install TCustomInstaller with.
            /// @param parameters Parameters for the constructor of the installer. This will override Zenject's constructor injection on this installer,
            /// and the installer type cannot be a MonoInstaller if using this.
            template<Lapiz::concepts::IInstaller TCustomInstaller,  Lapiz::concepts::IInstaller TBaseInstaller>
            inline void Install(ArrayW<Il2CppObject*> parameters) {
                Install(classof(TCustomInstaller), classof(TBaseInstaller), parameters);
            };

            /// @brief Install bindings to a custom location with a backing installer(s).
            /// @param location The location to install it to.
            /// @param installCallback The callback which is used to install custom bindings into the container.
            void Install(Zenject::Location location, ZenjectorCallback installCallback);

            /// @brief Install bindings alongsise another installer without a custom installer.
            /// @tparam TBaseInstaller The installer to install your bindings with.
            /// @param installCallback The callback which is used to install custom bindings into the container.
            template<Lapiz::concepts::IInstaller TBaseInstaller>
            void Install(ZenjectorCallback installCallback) {
                Install(classof(TBaseInstaller), installCallback);
            };

            /// @brief Searches a decorator context for the first instance that matches a type, then invokes a callback with that instance for it to be modified or mutated.
            /// @tparam TMutableType The type to mutate.
            /// @param contractName The contract name of the SceneDecoratorContext to search on.
            /// @param mutationCallback The callback used to mutate the object instance.
            template<typename TMutableType>
            requires(std::is_convertible_v<TMutableType, Il2CppObject*> && !std::is_same_v<TMutableType, Il2CppObject*>)
            void Mutate(std::string contractName, std::function<void(::Zenject::SceneDecoratorContext*, TMutableType)> mutationCallback) {
                Mutate(classof(TMutableType), contractName, [mutationCallback](::Zenject::SceneDecoratorContext* context, Il2CppObject* obj){ mutationCallback(context, reinterpret_cast<TMutableType>(obj)); });
            }

            /// @brief Searches a decorator context for the first instance that matches a type, then invokes a callback with that instance for it to be modified or mutated.
            /// @param typeToMutate the Il2CppClass* of the type to mutate, this would be the class of the argument passed second in the mutationCallback
            /// @param contractName The contract name of the SceneDecoratorContext to search on.
            /// @param mutationCallback The callback used to mutate the object instance.
            void Mutate(Il2CppClass* typeToMutate, std::string contractName, std::function<void(::Zenject::SceneDecoratorContext*, Il2CppObject*)> mutationCallback);

            /// @brief Install bindings to another installer without a custom installer
            static void UseMetadataBinder() {};

            /// @brief Lets you use Lapiz' HTTP service system. Not implemented, nor used currently.
            static void UseHttpService() {};

            /// @brief Makes it possible for Quest mods to sync to an external service, like GitHub. Not implemented, nor used currently.
            static void UseLapizSync() {};
        private:
            friend class ZenjectManager;

            void Install(Il2CppClass* baseInstallerT, ZenjectorCallback installCallback);
            void Install(Il2CppClass* customInstallerT, Il2CppClass* baseInstallerT, ArrayW<Il2CppObject*> parameters);
            void Install(Il2CppClass* customInstallerT, Zenject::Location location, ArrayW<Il2CppObject*> parameters);

            std::unordered_set<Internal::InstallSet*> _installSets;
            std::unordered_set<Internal::InstallInstruction*> _installInstructions;
            std::unordered_set<Internal::MutateSet*> _mutateSets;
    };
}
