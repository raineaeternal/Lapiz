#include "affinity.hpp"

#include "beatsaber-hook/shared/safeptr.hpp"

#ifdef MAKE_AFFINITY_HOOK
#error "MAKE_AFFINITY_HOOK already defined! Undefine it before including hooking.hpp!"
#endif

#define __INTERNAL_AFFINITY_HOOK_STRUCT(name_, addr_, ret_type, ...)     \
    constexpr static const char* name() { return #name_; }              \
    static auto addr() { return addr_; }                                \
    static func_t hook() { return hook_m_##name_; }                     \
    static func_t* trampoline() { return &name_; }                      \
    static ret_type hook_m_##name_(__VA_ARGS__); /* Hook */             \
    static inline ret_type (*name_)(__VA_ARGS__) = nullptr; /* Orig */

// Injected value. I would've wanted this to be passed as a parameter by flamingo but oh well
#define __INTERNAL_AFFINITY_HOOK_INJECTED_STRUCT(injected_t) \
    using injected_type = injected_t;                        \
    static inline safe_ptr<injected_t> Injected;

// Defines a hook to a manually found address or il2cpp method, installable with a fluent AFFINITY_HOOK builder.
// addr_info must be in parentheses, and can either be an expression that produces a pointer,
// or a find_class_info, method name, and boolean flag if an instance method.
// If given an il2cpp method, it will search for one that matches the given return type and parameters.
#define MAKE_AFFINITY_HOOK(name_, addr_info, ret_type, ...)                                                             \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                       \
        __INTERNAL_AFFINITY_HOOK_STRUCT(name_, ::i2c::detail::resolve_addr<func_t>{} addr_info, ret_type, __VA_ARGS__) \
    };                                                                                                                  \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

// Same as MAKE_AFFINITY_HOOK, but also declares a safe_ptr<injected_t> Injected member that flamingo
// will populate with the current mod's instance of injected_t before each call into the hook body.
#define MAKE_AFFINITY_HOOK_INJECTED(name_, injected_t, addr_info, ret_type, ...)                                        \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                \
        __INTERNAL_AFFINITY_HOOK_INJECTED_STRUCT(injected_t)                                                           \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                       \
        __INTERNAL_AFFINITY_HOOK_STRUCT(name_, ::i2c::detail::resolve_addr<func_t>{} addr_info, ret_type, __VA_ARGS__) \
    };                                                                                                                  \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

// Defines a hook to a method with metadata provided through i2c::metadata_getter, installable with a fluent
// AFFINITY_HOOK builder. Will automatically cast overloads, check types, and detect static/instance methods,
// based on the given return type and parameters. Generic methods cannot be hooked with this macro.
#define MAKE_AFFINITY_HOOK_MATCH(name_, method, ret_type, ...)                                                                     \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                           \
        static constexpr auto cast_test = []<typename T>() { return requires { static_cast<T>(method); }; };                       \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                                   \
        using cast_t = ::i2c::detail::method_check<cast_test, func_t>::type;                                                        \
        static_assert(cast_test.operator()<cast_t>(), "Hook method signature does not match!");                                    \
        static_assert(::i2c::detail::match_hookable<static_cast<cast_t>(method)>, "Method cannot be hooked!");                      \
        __INTERNAL_AFFINITY_HOOK_STRUCT(name_, ::i2c::metadata_getter<static_cast<cast_t>(method)>::method_info(), ret_type, __VA_ARGS__) \
    };                                                                                                                              \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

// Same as MAKE_AFFINITY_HOOK_MATCH, but also declares a safe_ptr<injected_t> Injected member that flamingo
// will populate with the current mod's instance of injected_t before each call into the hook body.
#define MAKE_AFFINITY_HOOK_MATCH_INJECTED(name_, injected_t, method, ret_type, ...)                                                \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                                           \
        __INTERNAL_AFFINITY_HOOK_INJECTED_STRUCT(injected_t)                                                                       \
        static constexpr auto cast_test = []<typename T>() { return requires { static_cast<T>(method); }; };                       \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                                   \
        using cast_t = ::i2c::detail::method_check<cast_test, func_t>::type;                                                        \
        static_assert(cast_test.operator()<cast_t>(), "Hook method signature does not match!");                                    \
        static_assert(::i2c::detail::match_hookable<static_cast<cast_t>(method)>, "Method cannot be hooked!");                      \
        __INTERNAL_AFFINITY_HOOK_STRUCT(name_, ::i2c::metadata_getter<static_cast<cast_t>(method)>::method_info(), ret_type, __VA_ARGS__) \
    };                                                                                                                              \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

#ifdef AFFINITY_HOOK
#error "AFFINITY_HOOK already defined! Undefine it before including hooking.hpp!"
#endif

// Creates a fluent builder for a hook made with MAKE_AFFINITY_HOOK, scoped under mod_id.
// Chain .before(other_mod_id), .after(other_mod_id), and/or .final(), then call .install(container)
// with the DiContainer the hook's handle should be bound into.
// Optionally takes an address to install to directly, bypassing the hook's own addr().
#define AFFINITY_HOOK(logger, mod_id, name_, ...) \
    ::Lapiz::Affinity::make_affinity_hook_builder<hook_##name_>(logger, mod_id __VA_OPT__(,) __VA_ARGS__)

