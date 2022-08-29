#include "installers/LapizGameplayInstaller.hpp"
#include "sabers/SaberModelProvider.hpp"
#include "sabers/SaberModelManager.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"

DEFINE_TYPE(Lapiz::Installers, LapizGameplayInstaller);

namespace Lapiz::Installers {
    void LapizGameplayInstaller::InstallBindings() {
        auto container = get_Container();
        container->Bind<Lapiz::Sabers::SaberModelProvider*>()->AsSingle();
    }
}