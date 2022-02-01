#pragma once
#include "main.hpp"

#include "beatsaber-hook/shared/utils/hooking.hpp"

namespace z {
    class HookingUtility {
    private:
        inline static std::vector<void (*)(Logger &logger)> installFuncs;
    public:
        static void AddInstallFunc(void (*installFunc)(Logger &logger)) {
            installFuncs.push_back(installFunc);
        }

        static void InstallHooks(Logger &logger) {
            for (auto installFunc : installFuncs) {
                installFunc(logger);
            }
        }
    };
}
#define zInstallHooks(func) \
struct __zRegister##func { \
    __zRegister##func() { \
       z::HookingUtility::AddInstallFunc(func); \
    } \
}; \
static __zRegister##func __zRegisterInstance##func