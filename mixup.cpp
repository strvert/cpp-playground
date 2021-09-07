#include <iostream>
#include <string>

template <typename T, typename U>
struct Point
{
    T x;
    U y;

    template <typename V, typename W>
    Point<T, W> mixup(Point<V, W> const& other) {
        return Point<T, W>{
            .x = this->x,
            .y = other.y
        };
    }

    friend std::ostream& operator<<(std::ostream& os, Point<T, U> const& pt);
};

template <typename T, typename U>
std::ostream& operator<<(std::ostream& os, Point<T, U> const& pt)
{
    os << pt.x << ", " << pt.y;
    return os;
}


int main()
{
    using namespace std::string_literals;

    Point<int, float> p1{10, 12.3};
    Point<std::string, bool> p2{"string"s, false};

    Point<int, bool> p3 = p1.mixup(p2);

    std::cout << p3 << std::endl;
}
