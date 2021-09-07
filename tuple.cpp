#include <cxxabi.h>
#include <iostream>

template<typename... T>
struct Tuple {
};

template<typename T, typename... Rest>
struct Tuple<T, Rest...> {
    T first;
    Tuple<Rest...> rest;

    Tuple(const T& f, const Rest&... r)
      : first(f)
      , rest(r...)
    {}
};

template<size_t idx, typename T>
struct GetHelper;

template<typename T, typename... Rest>
struct GetHelper<0, Tuple<T, Rest...>> {
    static T get(Tuple<T, Rest...>& data) { return data.first; }
};

template<size_t idx, typename T, typename... Rest>
struct GetHelper<idx, Tuple<T, Rest...>> {
    static auto get(Tuple<T, Rest...>& data)
    {
        return GetHelper<idx - 1, Tuple<Rest...>>::get(data.rest);
    }
};

template<size_t N, typename T>
auto get(T tuple)
{
    return GetHelper<N, T>::get(tuple);
}

template<size_t idx, typename T>
struct EHelper;

template<>
struct EHelper<0, Tuple<std::string>> {
    static auto get(Tuple<std::string>& data) { return data.first; }
};

template<>
struct EHelper<1, Tuple<bool, std::string>> {
    static auto get(Tuple<bool, std::string>& data)
    {
        return EHelper<1 - 1, Tuple<std::string>>::get(data.rest);
    }
};

template<>
struct EHelper<2, Tuple<int, bool, std::string>> {
    static auto get(Tuple<int, bool, std::string>& data)
    {
        return EHelper<2 - 1, Tuple<bool, std::string>>::get(data.rest);
    }
};

template<typename... Ts>
struct type_seq;

template<typename T, typename... Ts>
struct type_seq<T, Ts...> {
};

template<size_t Idx, typename T>
struct type_getter;

template<typename T, typename... Ts>
struct type_getter<0, type_seq<T, Ts...>> {
    using type = T;
};

template<size_t Idx, typename T, typename... Ts>
struct type_getter<Idx, type_seq<T, Ts...>> {
    using type = typename type_getter<Idx - 1, type_seq<Ts...>>::type;
};

template<typename T>
void print_type()
{
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << std::endl;
}

void rec_print() {};

template<typename First, typename... Rest>
void rec_print(First first, Rest... rest)
{
    std::cout << first << std::endl;
    rec_print(rest...);
}

template<typename... Ts>
void fold_print(Ts... args)
{
    (std::cout << ... << args) << std::endl;
}

#include <tuple>

template<size_t i, typename... Args>
struct printer {
    static void print(const std::tuple<Args...>& t)
    {
        std::cout << get<i>(t) << std::endl;
        printer<i + 1, Args...>::print(t);
    }
};

template<typename... Args>
struct printer<sizeof...(Args), Args...> {
    static void print(const std::tuple<Args...>&) {}
};

template<typename... Args>
void print(const std::tuple<Args...>& t)
{
    printer<0, Args...>::print(t);
}

// void print23(const std::tuple<Args...>& t) {
//     for...(const auto& elem: t)
//     {
//         std::cout << elem << std::endl;
//     }
// }

template<typename... Args>
void apply_print(const std::tuple<Args...>& t)
{
    std::apply(
      [](const auto&... args) { ((std::cout << args << std::endl), ...); }, t);
}

int main()
{
    rec_print(1, 'a', "abc");
    fold_print(1, 'a', "abc");
    // using t = type_seq<int, bool, char, std::string>;
    std::tuple<int, bool, char, std::string> t(1, true, 'a', "abcd");
    print(t);
    apply_print(t);

    // print_type<type_getter<0, t>::type>();
    // print_type<type_getter<1, t>::type>();
    // print_type<type_getter<2, t>::type>();
    // print_type<type_getter<3, t>::type>();
}
