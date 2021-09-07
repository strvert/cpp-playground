#include <iostream>
#include <type_traits>
#include <cxxabi.h>
#include <utility>

template <int... Ns>
struct seq_gen;

template <int... Ns>
struct seq{};

template <int N, int... Ns>
struct seq_gen<N, Ns...>{
    using type = seq_gen<N-1, N-1, Ns...>;
};

template <int... Ns>
struct seq_gen<0, Ns...>{
    using type = seq<Ns...>;
};


template <typename T>
void print_type()
{
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << std::endl;
}

template <int N>
using mis = std::make_integer_sequence<int, N>;

int main()
{
    print_type<seq_gen<1000>::type>();
    print_type<std::index_sequence<1, 2, 3>>();
    print_type<mis<100>()>();
}
