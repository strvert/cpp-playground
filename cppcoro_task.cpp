#include <chrono>
#include <thread>
#include <string>

#include <fmt/core.h>
#include <cppcoro/sync_wait.hpp>
#include <cppcoro/task.hpp>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using namespace std::chrono_literals;

auto getTimeSince(const time_point<high_resolution_clock>& start)
{
    auto end = high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

cppcoro::task<> second(const time_point<high_resolution_clock>& start)
{
    // auto sec = second(start);
    std::this_thread::sleep_for(1s);
    fmt::print("Second waited {} sec.\n", getTimeSince(start));
    co_return;
}

cppcoro::task<> first(const time_point<high_resolution_clock>& start)
{
    auto sec = second(start);
    std::this_thread::sleep_for(1s);
    co_await sec;
    fmt::print("First waited {} sec.\n", getTimeSince(start));
}

int main()
{
    fmt::print("\n");
    auto start = high_resolution_clock::now();
    cppcoro::sync_wait(first(start));
}
