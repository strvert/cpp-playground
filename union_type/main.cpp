#include <iostream>
#include <string>
#include <fmt/core.h>

template <size_t N, char Str[N]>
struct UnionTypeImpl
{
    static void print() {
        fmt::print("{}\n", Str);
    }
};

template<>


int main()
{
    UnionTypeImpl<3, {'a', 'b', 'c'}>;
}
