#include <cxxabi.h>
#include <tuple>
#include <type_traits>
#include <iostream>
#include <utility>

namespace detail {

// iseq_if_c
template<bool C, class T, class E>
struct iseq_if_c_impl;

template<class T, class E>
struct iseq_if_c_impl<true, T, E> {
    using type = T;
};

template<class T, class E>
struct iseq_if_c_impl<false, T, E> {
    using type = E;
};

template<bool C, class T, class E>
using iseq_if_c = typename iseq_if_c_impl<C, T, E>::type;

// iseq_identity
template<class T>
struct iseq_identity {
    using type = T;
};

template<class S1, class S2>
struct append_integer_sequence;

template<class T, T... I, T... J>
struct append_integer_sequence<std::integer_sequence<T, I...>,
                               std::integer_sequence<T, J...>> {
    using type = std::integer_sequence<T, I..., (J + sizeof...(I))...>;
};

template<class T, T N>
struct make_integer_sequence_impl;

template<class T, T N>
struct make_integer_sequence_impl_ {
private:
    static_assert(N >= 0,
                  "make_integer_sequence<T, N>: N must not be negative");

    static T const M = N / 2;
    static T const R = N % 2;

    using S1 = typename make_integer_sequence_impl<T, M>::type;
    using S2 = typename append_integer_sequence<S1, S1>::type;
    using S3 = typename make_integer_sequence_impl<T, R>::type;
    using S4 = typename append_integer_sequence<S2, S3>::type;

public:
    using type = S4;
};

template<class T, T N>
struct make_integer_sequence_impl
  : iseq_if_c<N == 0,
              iseq_identity<std::integer_sequence<T>>,
              iseq_if_c<N == 1,
                        iseq_identity<std::integer_sequence<T, 0>>,
                        make_integer_sequence_impl_<T, N>>> {
};

} // namespace detail

// make_integer_sequence
template<class T, T N>
using make_integer_sequence =
  typename detail::make_integer_sequence_impl<T, N>::type;

// index_sequence
template<std::size_t... I>
using index_sequence = std::integer_sequence<std::size_t, I...>;

// make_index_sequence
template<std::size_t N>
using make_index_sequence = make_integer_sequence<std::size_t, N>;

// index_sequence_for
template<class... T>
using index_sequence_for = make_integer_sequence<std::size_t, sizeof...(T)>;

template<typename T>
void print_type()
{
    std::cout << abi::__cxa_demangle(typeid(T).name(), 0, 0, 0) << std::endl;
}

template <int... Ns>
struct type_sequence {};

template <int N, template <int... Ns> typename T>
struct get{
    static void print() {
    }
};

int main()
{
    print_type<std::tuple_element_t<2, std::tuple<int, char, double>>>();
}
