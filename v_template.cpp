#include <cstddef>
#include <tuple>
#include <utility>

template<typename...>
struct List;
constexpr std::size_t map_ins(std::size_t i, std::size_t from, std::size_t to)
{
    return i < to ? i : i == to ? from : i - 1;
}

template<typename, typename, std::size_t, typename...>
struct ins_hlp;

template<std::size_t... Is, typename U, std::size_t N, typename... Ts>
struct ins_hlp<std::index_sequence<Is...>, U, N, Ts...> {
    static_assert(N <= sizeof...(Ts), "Insert index out of range");
    using type = List<std::tuple_element_t<map_ins(Is, sizeof...(Ts), N),
                                           std::tuple<Ts..., U>>...>;
};

constexpr std::size_t map_rem(std::size_t i, std::size_t idx)
{
    return i < idx ? i : i + 1;
}

template<typename, std::size_t, typename...>
struct rem_hlp_2;

template<std::size_t... Is, std::size_t N, typename... Ts>
struct rem_hlp_2<std::index_sequence<Is...>, N, Ts...> {
    using type =
      List<std::tuple_element_t<map_rem(Is, N), std::tuple<Ts...>>...>;
};

template<std::size_t N, typename... Ts>
struct rem_hlp {
    static_assert(N < sizeof...(Ts), "Remove index out of range");
    using type = typename rem_hlp_2<std::make_index_sequence<sizeof...(Ts) - 1>,
                                    N,
                                    Ts...>::type;
};

template<typename... Ts>
struct List {
    template<typename U, std::size_t N>
    using Insert = typename ins_hlp<std::make_index_sequence<sizeof...(Ts) + 1>,
                                    U,
                                    N,
                                    Ts...>::type;
    template<std::size_t N>
    using Remove = typename rem_hlp<N, Ts...>::type;
};

template<typename... Ts>
struct type_seq {
    using type = type_seq;
};

template<typename T, size_t N, typename... Ts>
struct gen_type_seq {
    using type = typename gen_type_seq<T, N - 1, Ts..., T>::type;
};

template<typename T, typename... Ts>
struct gen_type_seq<T, 0, Ts...> {
    using type = typename type_seq<Ts...>::type;
};

#include <cxxabi.h>
#include <iostream>

int main()
{
    List<int, bool, char, int, int, float> l1;
    std::cout << abi::__cxa_demangle(typeid(l1).name(), 0, 0, 0) << std::endl;

    decltype(l1)::Insert<double, 3> l2;
    std::cout << abi::__cxa_demangle(typeid(l2).name(), 0, 0, 0) << std::endl;

    decltype(l2)::Insert<unsigned int, 2> l3;
    std::cout << abi::__cxa_demangle(typeid(l3).name(), 0, 0, 0) << std::endl;
}
