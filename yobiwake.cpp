#include <iostream>
#include <string>

enum class StructType {
    None,
    Int,
    Float,
    Double,
};

template <typename T>
struct GetStructType {
    static constexpr const StructType Type = StructType::None;
};

template <>
struct GetStructType<int> {
    static constexpr const StructType Type = StructType::Int;
};

template <>
struct GetStructType<float> {
    static constexpr const StructType Type = StructType::Float;
};

template <>
struct GetStructType<double> {
    static constexpr const StructType Type = StructType::Double;
};

template <typename T, StructType Type = GetStructType<T>::Type>
struct TargetClass {
    static void Do () {
        std::cout << "Generic" << std::endl;
    }
};

template <typename T>
struct TargetClass<T, StructType::Int> {
    static void Do () {
        std::cout << "Int" << std::endl;
    }
};

template <typename T>
struct TargetClass<T, StructType::Float> {
    static void Do () {
        std::cout << "Float" << std::endl;
    }
};

template <typename T>
struct TargetClass<T, StructType::Double> {
    static void Do () {
        std::cout << "Double" << std::endl;
    }
};

int main()
{
    TargetClass<int>::Do();
    TargetClass<float>::Do();
    TargetClass<char>::Do();
    TargetClass<double>::Do();
}
