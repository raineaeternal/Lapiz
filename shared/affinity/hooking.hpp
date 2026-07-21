#include "affinity.hpp"

#ifdef MAKE_AFFINITY_HOOK
#error "MAKE_AFFINITY_HOOK already defined! Undefine it before including hooking.hpp!"
#endif

// Defines a hook to a manually found address or il2cpp method, installable with a fluent AFFINITY_HOOK builder.
// addr_info must be in parentheses, and can either be an expression that produces a pointer,
// or a find_class_info, method name, and boolean flag if an instance method.
// If given an il2cpp method, it will search for one that matches the given return type and parameters.
#define MAKE_AFFINITY_HOOK(name_, addr_info, ret_type, ...)                                                      \
    struct BS_HOOK_HIDDEN hook_##name_ {                                                                         \
        using func_t = ret_type (*)(__VA_ARGS__);                                                                \
        constexpr static const char* name() { return #name_; }                                                  \
        static auto addr() { return ::i2c::detail::resolve_addr<func_t>{} addr_info; }                          \
        static func_t hook() { return hook_m_##name_; }                                                          \
        static func_t* trampoline() { return &name_; }                                                           \
        static ret_type hook_m_##name_(__VA_ARGS__); /* Hook */                                                  \
        static inline ret_type (*name_)(__VA_ARGS__) = nullptr; /* Orig */                                       \
    };                                                                                                           \
    ret_type hook_##name_::hook_m_##name_(__VA_ARGS__)

// Creates a fluent builder for a hook made with MAKE_AFFINITY_HOOK, scoped under mod_id.
// Chain .before(other_mod_id), .after(other_mod_id), and/or .final(), then call .install(container)
// with the DiContainer the hook's handle should be bound into.
// Optionally takes an address to install to directly, bypassing the hook's own addr().
#define AFFINITY_HOOK(logger, mod_id, name_, ...) \
    ::affinity::make_affinity_hook_builder<hook_##name_>(logger, mod_id __VA_OPT__(,) __VA_ARGS__)

