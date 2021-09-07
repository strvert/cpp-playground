#include <iostream>
#include <fmt/core.h>
#include <experimental/coroutine>
#include <cppcoro/generator.hpp>

cppcoro::generator<const int> test_coroutine() {
    for (int i = 0; i < 10; i++) {
        if (i > 5) {
            co_return;
        }
        co_yield i;
    }
}

cppcoro::generator<int> range() {
    int n = 5000;
    while(true) {
        if (n == 0) co_return;
        co_yield n / 3;
        fmt::print("ho!!!\n");
        n /= 3;
    }
}

int main() {
    for (auto&& n: range())
    {
        fmt::print("#{}\n", n);
    }
}
