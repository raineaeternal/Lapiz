#pragma once

#include "beatsaber-hook/shared/hooking.hpp"

class Hooks {
   private:
    static inline std::vector<void (*)()> installFuncs;

   public:
    static inline void AddInstallFunc(void (*installFunc)()) { installFuncs.push_back(installFunc); }

    static inline void InstallHooks() {
        for (auto& func : installFuncs)
            func();
    }
};

#define AUTO_HOOK_FUNCTION(name_)                                        \
    namespace {                                                          \
        struct Auto_Install_##name_ {                                    \
            static void Install();                                       \
            Auto_Install_##name_() { ::Hooks::AddInstallFunc(Install); } \
        };                                                               \
    }                                                                    \
    static Auto_Install_##name_ Auto_Install_Instance_##name_;           \
    void Auto_Install_##name_::Install()

#define AUTO_INSTALL_ORIG(name_) \
    AUTO_HOOK_FUNCTION(hook_##name_) { INSTALL_HOOK_ORIG(Paper::ConstLoggerContext(MOD_ID "_Install_" #name_), name_); }

#define AUTO_INSTALL(name_) \
    AUTO_HOOK_FUNCTION(hook_##name_) { INSTALL_HOOK(Paper::ConstLoggerContext(MOD_ID "_Install_" #name_), name_); }

#define MAKE_AUTO_HOOK_MATCH(name_, method, ret_type, ...)                                                                       \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                         \
        static constexpr auto cast_test = []<typename T>() { return requires { static_cast<T>(method); }; };                     \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                                \
        using cast_t = ::i2c::detail::method_check<cast_test, func_t>::type;                                                     \
        static_assert(cast_test.operator()<cast_t>(), "Hook method signature does not match!");                                  \
        static_assert(::i2c::detail::match_hookable<static_cast<cast_t>(method)>, "Method cannot be hooked!");                   \
        __INTERNAL_HOOK_STRUCT(name_, ::i2c::metadata_getter<static_cast<cast_t>(method)>::method_info(), ret_type, __VA_ARGS__) \
    };                                                                                                                           \
    AUTO_INSTALL(name_)                                                                                                          \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

#define MAKE_AUTO_ORIG_HOOK_MATCH(name_, method, ret_type, ...)                                                                  \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                         \
        static constexpr auto cast_test = []<typename T>() { return requires { static_cast<T>(method); }; };                     \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                                \
        using cast_t = ::i2c::detail::method_check<cast_test, func_t>::type;                                                     \
        static_assert(cast_test.operator()<cast_t>(), "Hook method signature does not match!");                                  \
        static_assert(::i2c::detail::match_hookable<static_cast<cast_t>(method)>, "Method cannot be hooked!");                   \
        __INTERNAL_HOOK_STRUCT(name_, ::i2c::metadata_getter<static_cast<cast_t>(method)>::method_info(), ret_type, __VA_ARGS__) \
    };                                                                                                                           \
    AUTO_INSTALL_ORIG(name_)                                                                                                     \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)
