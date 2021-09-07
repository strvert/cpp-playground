#include <iostream>
#include <string>
#include <tuple>

struct strct1 {
    float f;
    int i;
    std::string s;
};

struct strct2 {
    double d;
    std::uint16_t u16;
    char c[64];
};

struct strct3 {
    float f;
    std::int16_t i16;
    std::string s;
};

namespace strct_cast_impl {
using intermediate_strct = std::tuple<double, std::uint16_t, std::string>;
struct istrct_maker {
    intermediate_strct istrct;
    void operator()(double d, std::uint16_t u16, std::string s)
    {
        istrct = std::make_tuple(d, u16, s);
    }
    intermediate_strct get() const { return istrct; }
};

struct istrct_breaker {
    const intermediate_strct& istrct;
    istrct_breaker(const intermediate_strct& istrct) : istrct(istrct) {}
    const intermediate_strct& get() const { return istrct; }
};
}

template<typename To, typename From>
To strct_cast(const From& in_strct)
{
    using namespace strct_cast_impl;
    istrct_maker maker;
    break_strct(maker, in_strct);

    To to_strct;
    istrct_breaker breaker(maker.get());
    make_strct(to_strct, breaker);
    return to_strct;
}

template<typename Maker>
void break_strct(Maker& s, const strct1& strct)
{
    s(strct.f, strct.i, strct.s);
}

template<typename Maker>
void break_strct(Maker& s, const strct2& strct)
{
    s(strct.d, strct.u16, strct.c);
}

template<typename Maker>
void break_strct(Maker& s, const strct3& strct)
{
    s(strct.f, strct.i16, strct.s);
}

template<typename Reciever>
void make_strct(strct1& strct, const Reciever& reciever)
{
    const auto& [d, i, s] = reciever.get();
    strct.f = d;
    strct.i = i;
    strct.s = s;
}

template<typename Reciever>
void make_strct(strct2& strct, const Reciever& reciever)
{
    const auto& [d, i, s] = reciever.get();
    strct.d = d;
    strct.u16 = i;
    s.copy(strct.c, s.size() > 64 ? 64 : s.size());
}

template<typename Reciever>
void make_strct(strct3& strct, const Reciever& reciever)
{
    const auto& [d, i, s] = reciever.get();
    strct.f = d;
    strct.i16 = i;
    strct.s = s;
}


#include <fmt/core.h>

int main()
{
    strct1 s1 { 10.2, 153, "test" };

    strct2 s2 = strct_cast<strct2>(s1);
    strct1 s1_2 = strct_cast<strct1>(s2);
    strct3 s3 = strct_cast<strct3>(s1);

    fmt::print("{}: {}, {}, {}\n", typeid(s2).name(), s2.d, s2.u16, s2.c);
    fmt::print("{}: {}, {}, {}\n", typeid(s1_2).name(), s1_2.f, s1_2.i, s1_2.s);
    fmt::print("{}: {}, {}, {}\n", typeid(s3).name(), s3.f, s3.i16, s3.s);
}
