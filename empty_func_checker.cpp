#include <iostream>

struct InvalidType_One {
};

struct ValidType_Two {
    struct TargetMarker;
};

struct ValidType_Three {
    struct TargetMarker;
};

// template<typename T>
// struct Check {
//     template<typename U>
//     static char (
//       &Resolve(typename U::TargetMarker*))[(std::is_same<ValidType_Three, U>::value) ? 3 : 2];
//
//     template<typename U>
//     static char (&Resolve(...))[1];
//
//     static constexpr const auto Value = sizeof(Resolve<T>(0));
// };

struct Check_1 {
    static constexpr const auto Value = 1;
};

struct Check_2 {
    static constexpr const auto Value = 2;
};

struct Check_3 {
    static constexpr const auto Value = 3;
};


int main()
{
    std::cout << Check<InvalidType_One>::Value << std::endl;
    std::cout << Check<ValidType_Two>::Value << std::endl;
    std::cout << Check<ValidType_Three>::Value << std::endl;
}
