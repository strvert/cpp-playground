#include <fmt/core.h>

bool print(const std::string& str)
{
    fmt::print("{}\n", str);
    if (str[0] == 'T')
    {
        return true;
    }
    return false;
}

int main()
{
    if (print("F") || print("F"))
    {
        fmt::print("TRUE\n");
    } else {
        fmt::print("FALSE\n");
    }
}
