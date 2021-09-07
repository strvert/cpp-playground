#include <iostream>
#include <sstream>
#include <cxxabi.h>

template<typename T>
struct id {
    using type = T;
};

template<typename T>
using type_of = typename T::type;

template<size_t... N>
struct sizes : id<sizes<N...>> {};

//

template <size_t N, typename... T>
struct Choose;

template <size_t N, typename H, typename... T>
struct Choose<N, H, T...> : Choose<N-1, T...> {};

template <typename H, typename... T>
struct Choose<0, H, T...> : id<H> {};

template <size_t N, typename... T>
using choose = type_of<Choose<N, T...>>;

template <typename T, typename U>
struct SizesConcat;

template <size_t... Ns1, size_t... Ns2>
struct SizesConcat<sizes<Ns1...>, sizes<Ns2...>> : sizes<Ns1..., (sizeof...(Ns1)+Ns2)...>{};

template <typename T, typename U>
using sizes_concat = type_of<SizesConcat<T, U>>;

//

template <size_t L, size_t I = 0, typename S = sizes<>>
struct Range;

template <size_t L, size_t I, size_t... N>
struct Range<L, I, sizes<N...>> : Range<L, I+1, sizes<N..., I>> {};

template <size_t L, size_t...N>
struct Range <L, L, sizes<N...>> : sizes<N...> {};

template <size_t L>
using RangeT = type_of<Range<L>>;

template <size_t L>
using range = sizes_concat<sizes_concat<sizes_concat<
                RangeT<L/4>, RangeT<L/4>>,RangeT<L/4>>, RangeT<L-(L*3)/4>>;

//

template <typename... Ts>
struct type_seq : id<type_seq<Ts...>> {};

template <size_t N, typename T>
struct choose_type;

template <size_t N, typename... Ts>
struct choose_type<N, type_seq<Ts...>> {
    using type = choose<N, Ts...>;
};

// template<typename T>
// void print_type()
// {
//     std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << std::endl;
// }
//

// template<class S1, class S2>
// using Concat = Invoke<concat<S1, S2>>;

// template<size_t N> struct gen_seq;
// template<size_t N> using GenSeq = Invoke<gen_seq<N>>;

template<class T> using Invoke = typename T::type;

template<size_t...> struct seq{ using type = seq; };

template<class S1, class S2, size_t I1_L> struct concat;

template<size_t... I1, size_t... I2, size_t I1_L>
struct concat<seq<I1...>, seq<I2...>, I1_L>
  : seq<I1..., (I1_L+I2)...>{};

template<size_t N>
struct gen_seq : Invoke<concat<Invoke<gen_seq<N/2>>,
                        Invoke<gen_seq<N - N/2>>, N/2>>{};

template<> struct gen_seq<0> : seq<>{};
template<> struct gen_seq<1> : seq<0>{};

template <typename T>
struct print_helper;

template <template <size_t...> typename T, size_t... Ts>
struct print_helper<T<Ts...>> {
    static void print(const bool bBrace = false) {
        std::stringstream buf;
        ((buf << Ts << ", "), ...);
        auto str = buf.str();
        std::cout << (bBrace ? "<" : "")
            << str.erase(str.length()-2)
            << (bBrace ? ">" : "")
            << std::endl;
    }
};
template <typename T>
struct print_length_helper;

template <template <size_t...> typename T, size_t... Ts>
struct print_length_helper<T<Ts...>> {
    static void print(const bool bBrace = false) {
        std::cout << sizeof...(Ts) << std::endl;
    }
};



// template<size_t... Ts>
// void print_tuple_type<sizes<Ts...>>()
// {
// }

int main() {
    // print_type<sizes<10, 1, 3, 2>>();
    // print_type<sizes<10, 1, 3, 2>::type>();

    // struct I{};
    // struct O{};

    // using seq1 = type_seq<I, O, I, O>;

    // print_type<choose_type<0, seq1>::type>();
    // print_type<choose_type<1, seq1>::type>();
    // print_type<choose_type<2, seq1>::type>();
    // print_type<choose_type<3, seq1>::type>();


    print_helper<gen_seq<5>::type>::print(true);
    print_length_helper<gen_seq<200000>::type>::print(true);
}
