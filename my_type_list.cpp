#include <iostream>
#include <sstream>
#include <tuple>
#include <utility>

#include <cxxabi.h>

template<typename T>
struct i_type {
    using type = T;
};

template<typename... Ts>
struct type_seq;

template<typename IndexSeq, typename InsertType, size_t Pos, size_t Len, typename... Ts>
struct set_helper;

template<size_t... Indexes, typename InsertType, size_t Pos, size_t Len, typename... Ts>
struct set_helper<std::index_sequence<Indexes...>, InsertType, Pos, Len, Ts...>
  : i_type<type_seq<
        std::tuple_element_t<Indexes < Pos ? Indexes : Indexes == Pos ? Len : Indexes-1, std::tuple<Ts..., InsertType>>...>> {
    static_assert(Pos < Len, "out of range");
};

template<typename... Ts>
struct type_seq : i_type<type_seq<Ts...>> {
    template<typename SetType, size_t Pos>
    using Set = typename set_helper<std::make_index_sequence<sizeof...(Ts)>,
                             SetType,
                             Pos,
                             sizeof...(Ts),
                             Ts...>::type;
};

//

template<typename T, size_t N, typename... Ts>
struct gen_type_seq {
    using type = typename gen_type_seq<T, N - 1, Ts..., T>::type;
};

template<typename T, typename... Ts>
struct gen_type_seq<T, 0, Ts...> {
    using type = typename type_seq<Ts...>::type;
};

template <typename From, template <typename...> typename To>
struct foward_types;

template <template <typename...> typename From, template <typename...> typename To, typename... Ts>
struct foward_types<From<Ts...>, To>: i_type<To<Ts...>> {};

//

template<typename T>
void print_type()
{
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << std::endl;
}

template<typename T>
struct print_helper;

template<template<size_t...> typename T, size_t... Ts>
struct print_helper<T<Ts...>> {
    static void print(const bool bBrace = false)
    {
        std::stringstream buf;
        ((buf << Ts << ", "), ...);
        auto str = buf.str();
        std::cout << (bBrace ? "<" : "") << str.erase(str.length() - 2)
                  << (bBrace ? ">" : "") << std::endl;
    }
};
template<typename T>
struct print_length_helper;

template<template<size_t...> typename T, size_t... Ts>
struct print_length_helper<T<Ts...>> {
    static void print() { std::cout << sizeof...(Ts) << std::endl; }
};

struct I {};
struct O {};

int main()
{
    using t_seq = gen_type_seq<O, 100>::type;
    print_type<t_seq>();

    using t_list = foward_types<t_seq, type_seq>::type;
    print_type<t_list>();

    print_type<t_list::Set<I, 5>::Set<I, 2>::Set<I, 3>>();
}
