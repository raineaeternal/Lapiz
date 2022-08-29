#pragma once

#include "zenject/AttributeRegistration.hpp"

#ifdef DECLARE_INJECT_METHOD
#error "DECLARE_INJECT_METHOD is already defined! Undefine it before including macros.hpp!"
#endif

/// TODO: inject field
/// TODO: inject field ID
/// TODO: inject field optional
/// TODO: inject field optional ID

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD(ret, name, ...)                                                                           \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isMethod() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_OPTIONAL(ret, name, ...)                                                                  \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isMethod() const override { return true; }                                                                 \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID(ret, name, ID, ...)                                                                    \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isMethod() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID_OPTIONAL(ret, name, ID, ...)                                                           \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isMethod() const override { return true; }                                                                 \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_METHOD(ret, name, __VA_ARGS__)

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD(type_, name)                                                                               \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isField() const override { return true; }                                                                  \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_OPTIONAL(type_, name)                                                                      \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        bool isField() const override { return true; }                                                                  \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID(type_, name, ID)                                                                        \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isField() const override { return true; }                                                                  \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID_OPTIONAL(type_, name, ID)                                                               \
private:                                                                                                                \
    struct __AttributeRegistration_##name : ::Lapiz::Zenject::Attributes::AttributeRegistration {                       \
        __AttributeRegistration_##name() : ::Lapiz::Zenject::Attributes::AttributeRegistration() {}                     \
        Il2CppClass* get_declaringType() const override {                                                               \
            return ___TargetType::___TypeRegistration::klass_ptr;                                                         \
        }                                                                                                               \
        const char* get_name() const override { return #name; }                                                         \
        const char* get_id() const override { return ID; }                                                              \
        bool isField() const override { return true; }                                                                  \
        bool optional() const override { return true; }                                                                 \
    };                                                                                                                  \
    static inline __AttributeRegistration_##name __##name##_AttributeRegistration;                                      \
DECLARE_INSTANCE_FIELD(type_, name)

