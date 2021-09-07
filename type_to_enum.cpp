#include <iostream>
#include <map>

enum class TypeEnum : uint8_t {
    Unknown = 1,
    Int,
    Float,
    Double,
    Char,
};

template<typename T>
struct Mapper {
    struct MTable;
    using ET = TypeEnum;
    using enum ET;
    template<ET E>
    struct ToEnum {
        char _[static_cast<std::underlying_type_t<ET>>(E)];
    };

    inline static constexpr const ET Value =
      static_cast<ET>(sizeof(MTable::From(static_cast<T*>(nullptr))));
    template<typename NP> using Type = std::add_pointer_t<NP>;

    struct MTable {
        static ToEnum<Unknown> From(...);
        static ToEnum<Int> From(Type<int>);
        static ToEnum<Float> From(Type<float>);
        static ToEnum<Double> From(Type<double>);
        static ToEnum<Char> From(Type<char>);
    };
};
template<typename T>
TypeEnum MapperV = Mapper<T>::Value;

int main()
{
    const std::map<TypeEnum, const char*> ToString = {
        { TypeEnum::Unknown, "Unknown" }, { TypeEnum::Int, "Int" },
        { TypeEnum::Float, "Float" },     { TypeEnum::Double, "Double" },
        { TypeEnum::Char, "Char" },
    };

    std::cout << ToString.at(MapperV<int>) << std::endl;
    std::cout << ToString.at(MapperV<float>) << std::endl;
    std::cout << ToString.at(MapperV<double>) << std::endl;
    std::cout << ToString.at(MapperV<char>) << std::endl;
    std::cout << ToString.at(MapperV<bool>) << std::endl;
    std::cout << ToString.at(MapperV<TypeEnum>) << std::endl;
}
