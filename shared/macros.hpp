#pragma once

#include "zenject/AttributeRegistration.hpp"

#ifdef DECLARE_INJECT_METHOD
#error "DECLARE_INJECT_METHOD is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD(ret, name, ...)                                                                           \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isMethod() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_OPTIONAL
#error "DECLARE_INJECT_METHOD_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_OPTIONAL(ret, name, ...)                                                                  \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isMethod() const override { return true; }                                                                 \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_ID
#error "DECLARE_INJECT_METHOD_ID is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID(ret, name, ID, ...)                                                                    \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isMethod() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_ID_OPTIONAL
#error "DECLARE_INJECT_METHOD_ID_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID_OPTIONAL(ret, name, ID, ...)                                                           \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isMethod() const override { return true; }                                                                 \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

#ifdef DECLARE_INJECT_FIELD
#error "DECLARE_INJECT_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD(type_, name)                                                                               \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isField() const override { return true; }                                                                  \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

#ifdef DECLARE_INJECT_FIELD_OPTIONAL
#error "DECLARE_INJECT_FIELD_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_OPTIONAL(type_, name)                                                                      \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isField() const override { return true; }                                                                  \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

#ifdef DECLARE_INJECT_FIELD_ID
#error "DECLARE_INJECT_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID(type_, name, ID)                                                                        \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isField() const override { return true; }                                                                  \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

#ifdef DECLARE_INJECT_FIELD_ID_OPTIONAL
#error "DECLARE_INJECT_FIELD_ID_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID_OPTIONAL(type_, name, ID)                                                               \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                       \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isField() const override { return true; }                                                                  \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

#define DECLARE_PRIVATE_FIELD(type_, name_)                                                                                  \
private:                                                                                                                     \
    struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator {                                                  \
        ___FieldRegistrator_##name_() {                                                                                      \
            ___TargetType::___TypeRegistration::addField(this);                                                              \
        }                                                                                                                    \
        constexpr const char* name() const override {                                                                        \
            return #name_;                                                                                                   \
        }                                                                                                                    \
        const Il2CppType* type() const override {                                                                            \
            ::il2cpp_functions::Init();                                                                                      \
            return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
        }                                                                                                                    \
        constexpr uint16_t fieldAttributes() const override {                                                                \
            return FIELD_ATTRIBUTE_PUBLIC;                                                                                   \
        }                                                                                                                    \
        constexpr size_t size() const override {                                                                             \
            return sizeof(type_);                                                                                            \
        }                                                                                                                    \
        int32_t offset() const override {                                                                                    \
            return offsetof(___TargetType, name_);                                                                           \
        }                                                                                                                    \
    };                                                                                                                       \
    static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;                                                 \
private:                                                                                                                     \
    type_ name_

#define DECLARE_PRIVATE_FIELD_DEFAULT(type_, name_, default_)                                                                \
private:                                                                                                                     \
    struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator {                                                  \
        ___FieldRegistrator_##name_() {                                                                                      \
            ___TargetType::___TypeRegistration::addField(this);                                                              \
        }                                                                                                                    \
        constexpr const char* name() const override {                                                                        \
            return #name_;                                                                                                   \
        }                                                                                                                    \
        const Il2CppType* type() const override {                                                                            \
            ::il2cpp_functions::Init();                                                                                      \
            return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
        }                                                                                                                    \
        constexpr uint16_t fieldAttributes() const override {                                                                \
            return FIELD_ATTRIBUTE_PUBLIC;                                                                                   \
        }                                                                                                                    \
        constexpr size_t size() const override {                                                                             \
            return sizeof(type_);                                                                                            \
        }                                                                                                                    \
        int32_t offset() const override {                                                                                    \
            return offsetof(___TargetType, name_);                                                                           \
        }                                                                                                                    \
    };                                                                                                                       \
    static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;                                                 \
private:                                                                                                                     \
    type_ name_ = default_

#define DECLARE_PRIVATE_METHOD(ret, name, ...)                                                                               \
private:                                                                                                                     \
ret name(__VA_ARGS__);                                                                                                       \
___CREATE_INSTANCE_METHOD(name, #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)