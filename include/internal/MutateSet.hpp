#pragma once

#include "System/Type.hpp"
#include "Delegate.hpp"

namespace Lapiz::Zenject::Internal {
    class MutateSet {
        public:
            MutateSet(Il2CppClass* typeToMutate, std::string locationContractName, ZenjectDelegate onMutate) : _typeToMutate(typeToMutate), _locationContractName(locationContractName), _onMutate(onMutate) {}

            auto get_typeToMutate() const { return _typeToMutate; }
            auto get_locationContractName() const { return _locationContractName; }
            auto get_onMutate() const { return _onMutate; }

        private:
            const Il2CppClass* _typeToMutate;
            const std::string _locationContractName;
            const ZenjectDelegate _onMutate;
    };
}