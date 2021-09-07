#include <iostream>
#include <thread>
#include <chrono>
#include <future>

using namespace std::chrono_literals;

void func(std::promise<double> p, double x)
{
    std::cout << "0%" << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "50%" << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "100%" << std::endl;
    p.set_value(x*2);
}

int main()
{
    std::promise<double> p;
    auto f = p.get_future();

    double x = 3.14159265358;
    std::thread th1(func, std::move(p), x);
    std::thread th2(func, std::move(p), x);
    std::thread th3(func, std::move(p), x);

    auto result = f.get();

    th1.join();
    th2.join();
    th3.join();
}
