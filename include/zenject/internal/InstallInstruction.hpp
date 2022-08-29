#pragma once

#include "System/Type.hpp"
#include "zenject/Zenjector.hpp"

namespace Lapiz::Zenject::Internal {

    class InstallInstruction
    {
        public:
            InstallInstruction(Il2CppClass* baseInstaller, ZenjectorCallback installCallback) : _baseInstaller(baseInstaller), _installCallback(installCallback) {};
            auto get_baseInstaller() const { return _baseInstaller; }
            void onInstall(::Zenject::DiContainer* container) const { if (_installCallback) _installCallback(container); }
        private:
            const Il2CppClass* _baseInstaller;
            const ZenjectorCallback _installCallback;
    };
}
