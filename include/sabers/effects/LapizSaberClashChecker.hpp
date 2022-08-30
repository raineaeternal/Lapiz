#pragma once

#include "custom-types/shared/macros.hpp" 
#include "macros.hpp" 
#include "GlobalNamespace/SaberClashChecker.hpp"
#include "GlobalNamespace/SaberManager.hpp"
#include "GlobalNamespace/Saber.hpp"

#include "Zenject/DiContainer.hpp"
#include "sabers/LapizSaberFactory.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Sabers::Effects, LapizSaberClashChecker, GlobalNamespace::SaberClashChecker, classof(System::IDisposable*),
    DECLARE_PRIVATE_FIELD(GlobalNamespace::Saber*, _lastSaberA);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::Saber*, _lastSaberB);
    DECLARE_PRIVATE_FIELD(bool, _extraSabersDetected);
    DECLARE_PRIVATE_FIELD_DEFAULT(ListWrapper<GlobalNamespace::Saber*>, _sabers, nullptr);
    DECLARE_PRIVATE_FIELD(::Zenject::DiContainer*, _container);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::SaberManager*, _saberManager);
    DECLARE_PRIVATE_FIELD(Lapiz::Sabers::LapizSaberFactory*, _lapizSaberFactory);
    
    DECLARE_INSTANCE_METHOD(void, LapizSaberFactory_SaberCreated, Lapiz::Sabers::LapizSaber* lapizSaber);
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container, GlobalNamespace::SaberManager* saberManager, Lapiz::Sabers::LapizSaberFactory* lapizSaberFactory);
    public:
        bool SaberClashChecker_AreSabersClashing_override(UnityEngine::Vector3& clashingPoint, bool& result);
        UnorderedEventCallback<GlobalNamespace::Saber*, GlobalNamespace::Saber*> NewSabersClashed;
)