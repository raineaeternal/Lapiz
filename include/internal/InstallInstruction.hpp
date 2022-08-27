#pragma once

#include "System/Type.hpp"
#include "zenject/Zenjector.hpp"

namespace Lapiz::Zenject::Internal {

    class InstallInstruction
    {
        public:
            InstallInstruction(Il2CppClass* installerType, ZenjectorCallback installCallback) : _installerType(installerType), _installCallback(installCallback) {};
        private:
            const Il2CppClass* _installerType;
            const ZenjectorCallback _installCallback;
    };
}
