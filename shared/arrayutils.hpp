#pragma once

namespace Lapiz::ArrayUtils {
    template<typename T>
    requires(std::is_convertible<T, Il2CppObject*>::value || std::is_arithmetic<T>::value)
    static void box_array(ArrayW<Il2CppObject*> arr, int index, T val)  {
        if constexpr (std::is_pointer_v<T>) arr->values[index] = val;
        else arr[index] = il2cpp_functions::value_box(classof(T), &val);
    }
    
    template <typename First, typename... Rest>
    requires(std::is_convertible<First, Il2CppObject*>::value || std::is_arithmetic<First>::value)
    static void box_array(ArrayW<Il2CppObject*> arr, int index, First& first, Rest&... rest) {
        if constexpr (std::is_pointer_v<First>) arr->values[index] = first;
        else arr[index] = il2cpp_functions::value_box(classof(First), &first);

        box_array(arr, ++index, rest...);
    }
    
    template <typename First, typename... Rest>
    requires(std::is_convertible<First, Il2CppObject*>::value || std::is_arithmetic<First>::value)
    static void box_array(ArrayW<Il2CppObject*> arr, First& first, Rest&... rest) {
        box_array(arr, 0, first, rest...);
    }

    template<typename... Targs>
    static ArrayW<Il2CppObject*> box_array(Targs&... rest) {
        auto res = ArrayW<Il2CppObject*>(sizeof...(rest));
        box_array(res, rest...);
        return res;
    }

    template<typename T, typename... Targs>
    void SetIndexType(ArrayW<System::Type*> arr, int index) {
        arr[index] = csTypeOf(T);
        if constexpr (sizeof...(Targs) > 0) SetIndexType<Targs...>(arr, ++index);
    }

    template<typename... Targs>
    ArrayW<System::Type*> TypeArray() {
        auto res = ArrayW<System::Type*>(sizeof...(Targs));
        if constexpr (sizeof...(Targs) > 0) SetIndexType<Targs...>(res, 0);
        return res;
    }
}