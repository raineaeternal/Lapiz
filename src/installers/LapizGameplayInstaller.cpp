#include "installers/LapizGameplayInstaller.hpp"

#include "sabers/SaberModelProvider.hpp"
#include "sabers/SaberModelManager.hpp"
#include "sabers/LapizSaberFactory.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(Lapiz::Installers, LapizGameplayInstaller);

namespace Lapiz::Installers {
    void LapizGameplayInstaller::InstallBindings() {
        auto container = get_Container();

        container->BindInterfacesAndSelfTo<Lapiz::Sabers::SaberModelProvider*>()->AsSingle();
        container->BindInterfacesAndSelfTo<Lapiz::Sabers::SaberModelProvider*>()->AsSingle();
        container->Bind<Lapiz::Sabers::LapizSaberFactory*>()->AsSingle();
    }
}