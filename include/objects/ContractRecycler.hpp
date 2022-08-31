#pragma once

#include "custom-types/shared/macros.hpp"
#include "macros.hpp"
#include "Zenject/DiContainer.hpp"
#include "System/IDisposable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(Lapiz::Objects, ContractRecycler, Il2CppObject, classof(::System::IDisposable*),
    DECLARE_PRIVATE_FIELD(::Zenject::DiContainer*, _container);
    DECLARE_CTOR(ctor, ::Zenject::DiContainer* container);
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
)
