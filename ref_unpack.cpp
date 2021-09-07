#include <cstdint>
#include <fmt/core.h>

struct FIntermediateGuid {
    uint32_t Data1;
    uint16_t Data2;
    uint16_t Data3;
    uint8_t Data4[8];
};

int main()
{
    FIntermediateGuid Guid { 1, 2, 3, { 1, 2, 3, 4, 5, 6, 7, 8 } };
    auto& [Data1, Data2, Data3, Data4] = Guid;

    Data1 = 3;
    fmt::print("{}\n", Guid.Data1);
}
