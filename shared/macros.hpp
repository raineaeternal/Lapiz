#pragma once

#include "zenject/LapizInjectAttribute.hpp"
#include "objects/LapizSerializableAttribute.hpp"

#ifdef __MAKE_INJECT_ATTRIBUTE
#error "__MAKE_INJECT_ATTRIBUTE is already defined! Undefine it before including macros.hpp!"
#endif

// Makes the attribute registration to lapiz for all your injection needs
#define __MAKE_INJECT_ATTRIBUTE(name_, isMethod_, isField_, optional_, id_)                     \
    struct __InjectAttributeRegistration_##name_ : public ::Lapiz::Zenject::InjectAttribute {   \
        __InjectAttributeRegistration_##name_() : ::Lapiz::Zenject::InjectAttribute() {}        \
        const char* get_name() const override { return #name_; }                                \
        const char* get_id() const override { return id_; }                                     \
        bool isMethod() const override { return isMethod_; }                                    \
        bool isField() const override { return isField_; }                                      \
        bool optional() const override { return optional_; }                                    \
        Il2CppClass* get_declaringType() const override {                                       \
            return ___TargetType::___TypeRegistration::klass_ptr;                               \
        }                                                                                       \
    };                                                                                          \
    static inline __InjectAttributeRegistration_##name_ __##name_##_InjectAttributeRegistration

#ifdef DECLARE_INJECT_METHOD
#error "DECLARE_INJECT_METHOD is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD(ret_, name_, ...)              \
__MAKE_INJECT_ATTRIBUTE(name_, true, false, false, nullptr); \
DECLARE_INSTANCE_METHOD(ret_, name_, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_OPTIONAL
#error "DECLARE_INJECT_METHOD_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_OPTIONAL(ret_, name_, ...)    \
__MAKE_INJECT_ATTRIBUTE(name_, true, false, true, nullptr); \
DECLARE_INSTANCE_METHOD(ret_, name_, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_ID
#error "DECLARE_INJECT_METHOD_ID is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID(ret_, name_, id_, ...)    \
__MAKE_INJECT_ATTRIBUTE(name_, true, false, false, id_);   \
DECLARE_INSTANCE_METHOD(ret_, name_, __VA_ARGS__)

#ifdef DECLARE_INJECT_METHOD_ID_OPTIONAL
#error "DECLARE_INJECT_METHOD_ID_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the method(s) declared with this macro will automatically get called when zenject instantiates these objects, having their arguments called with the resolved types
#define DECLARE_INJECT_METHOD_ID_OPTIONAL(ret_, name_, ID_, ...) \
__MAKE_INJECT_ATTRIBUTE(name_, true, false, true, ID_);          \
DECLARE_INSTANCE_METHOD(ret_, name_, __VA_ARGS__)

#ifdef DECLARE_INJECT_FIELD
#error "DECLARE_INJECT_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD(type_, name_)                      \
__MAKE_INJECT_ATTRIBUTE(name_, false, true, false, nullptr);    \
DECLARE_INSTANCE_FIELD(type_, name_)

#ifdef DECLARE_INJECT_FIELD_OPTIONAL
#error "DECLARE_INJECT_FIELD_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_OPTIONAL(type_, name_)             \
__MAKE_INJECT_ATTRIBUTE(name_, false, true, true, nullptr);    \
DECLARE_INSTANCE_FIELD(type_, name_)

#ifdef DECLARE_INJECT_FIELD_ID
#error "DECLARE_INJECT_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID(type_, name_, id_)          \
__MAKE_INJECT_ATTRIBUTE(name_, false, true, false, id_);    \
DECLARE_INSTANCE_FIELD(type_, name_)

#ifdef DECLARE_INJECT_FIELD_ID_OPTIONAL
#error "DECLARE_INJECT_FIELD_ID_OPTIONAL is already defined! Undefine it before including macros.hpp!"
#endif

/// the field(s) declared with this macro will automatically get filled when zenject instantiates these objects, resolving the types of these fields
#define DECLARE_INJECT_FIELD_ID_OPTIONAL(type_, name_, id_)   \
__MAKE_INJECT_ATTRIBUTE(name_, false, true, false, id_);      \
DECLARE_INSTANCE_FIELD(type_, name_)

#ifdef DECLARE_PRIVATE_FIELD
#error "DECLARE_PRIVATE_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

#define DECLARE_PRIVATE_FIELD(type_, name_)                                                                                  \
private:                                                                                                                     \
    struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator {                                                  \
        ___FieldRegistrator_##name_() {                                                                                      \
            ___TargetType::___TypeRegistration::addField(this);                                                              \
        }                                                                                                                    \
        constexpr const char* name() const override { return #name_; }                                                       \
        const Il2CppType* type() const override {                                                                            \
            ::il2cpp_functions::Init();                                                                                      \
            return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
        }                                                                                                                    \
        constexpr uint16_t fieldAttributes() const override { return FIELD_ATTRIBUTE_PUBLIC; }                               \
        constexpr size_t size() const override { return sizeof(type_); }                                                     \
        int32_t offset() const override { return offsetof(___TargetType, name_); }                                           \
    };                                                                                                                       \
    static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;                                                 \
private:                                                                                                                     \
    type_ name_

#ifdef DECLARE_PRIVATE_FIELD_DEFAULT
#error "DECLARE_PRIVATE_FIELD_DEFAULT is already defined! Undefine it before including macros.hpp!"
#endif

#define DECLARE_PRIVATE_FIELD_DEFAULT(type_, name_, default_)                                                                \
private:                                                                                                                     \
    struct ___FieldRegistrator_##name_ : ::custom_types::FieldRegistrator {                                                  \
        ___FieldRegistrator_##name_() {                                                                                      \
            ___TargetType::___TypeRegistration::addField(this);                                                              \
        }                                                                                                                    \
        constexpr const char* name() const override { return #name_; }                                                       \
        const Il2CppType* type() const override {                                                                            \
            ::il2cpp_functions::Init();                                                                                      \
            return ::il2cpp_functions::class_get_type(::il2cpp_utils::il2cpp_type_check::il2cpp_no_arg_class<type_>::get()); \
        }                                                                                                                    \
        constexpr uint16_t fieldAttributes() const override { return FIELD_ATTRIBUTE_PUBLIC; }                               \
        constexpr size_t size() const override { return sizeof(type_); }                                                     \
        int32_t offset() const override { return offsetof(___TargetType, name_); }                                           \
    };                                                                                                                       \
    static inline ___FieldRegistrator_##name_ ___##name_##_FieldRegistrator;                                                 \
private:                                                                                                                     \
    type_ name_ = default_

#ifdef DECLARE_PRIVATE_METHOD
#error "DECLARE_PRIVATE_METHOD is already defined! Undefine it before including macros.hpp!"
#endif

#define DECLARE_PRIVATE_METHOD(ret, name, ...)                                                                               \
private:                                                                                                                     \
ret name(__VA_ARGS__);                                                                                                       \
___CREATE_INSTANCE_METHOD(name, #name, METHOD_ATTRIBUTE_PUBLIC | METHOD_ATTRIBUTE_HIDE_BY_SIG, nullptr)

#ifdef __MAKE_SERIALIZABLE_ATTRIBUTE
#error "__MAKE_SERIALIZABLE_ATTRIBUTE is already defined! Undefine it before including macros.hpp!"
#endif

// Makes the attribute registration to lapiz for all your serializable needs
#define __MAKE_SERIALIZABLE_ATTRIBUTE(type_, name_)                                                         \
    struct __SerializableAttributeRegistration_##name_ : public ::Lapiz::Objects::SerializableAttribute {   \
        __SerializableAttributeRegistration_##name_() : ::Lapiz::Objects::SerializableAttribute() {}        \
        const char* get_name() const override { return #name_; }                                            \
        bool isMethod() const override { return false; }                                                    \
        bool isField() const override { return true; }                                                      \
        Il2CppClass* get_declaringType() const override {                                                   \
            return ___TargetType::___TypeRegistration::klass_ptr;                                           \
        }                                                                                                   \
    };                                                                                                      \
    static inline __SerializableAttributeRegistration_##name_ __##name_##_SerializableAttributeRegistration

#ifdef DECLARE_SERIALIZABLE_FIELD
#error "DECLARE_SERIALIZABLE_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

#define DECLARE_SERIALIZABLE_FIELD(type_, name_)  \
__MAKE_SERIALIZABLE_ATTRIBUTE(type_, name_);      \
DECLARE_INSTANCE_FIELD(type_, name_)

#ifdef DECLARE_PRIVATE_SERIALIZABLE_FIELD
#error "DECLARE_PRIVATE_SERIALIZABLE_FIELD is already defined! Undefine it before including macros.hpp!"
#endif

#define DECLARE_PRIVATE_SERIALIZABLE_FIELD(type_, name_)  \
__MAKE_SERIALIZABLE_ATTRIBUTE(type_, name_);      \
DECLARE_PRIVATE_FIELD(type_, name_)