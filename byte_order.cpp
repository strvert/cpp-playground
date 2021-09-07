#include <fmt/core.h>

std::string ByteToString(const uint8_t Byte, const bool Upper)
{
    constexpr uint8_t Mask = 0x0F;

    char Buf[3];
    Buf[2] = '\0';

    const uint8_t Low = (Byte & Mask);
    const uint8_t High = (Byte & (Mask << 4)) >> 4;

    auto Conv = [&](const uint8_t V) {
        return V <= 9 ? '0' + V : (Upper ? 'A' : 'a') + (V - 10);
    };
    Buf[0] = Conv(High);
    Buf[1] = Conv(Low);

    return std::string(Buf);
}

template <typename T>
void print_bytes(const T Value, const size_t Len = sizeof(T)) {
    const uint8_t* Ptr = reinterpret_cast<const uint8_t*>(&Value);

    std::string PrintStr("0x");

    for (int Idx = 0; Idx < Len; Idx++)
    {
        PrintStr += ByteToString(*(Ptr + Idx), true);
    }

    fmt::print("{}\n", PrintStr);
}

template <size_t Len>
void print_bytes(const uint8_t (&Array)[Len]) {
    const uint8_t* Ptr = reinterpret_cast<const uint8_t*>(Array);

    std::string PrintStr("0x");

    for (int Idx = 0; Idx < Len; Idx++)
    {
        PrintStr += ByteToString(*(Ptr + Idx), true);
    }

    fmt::print("{}\n", PrintStr);
}

int main()
{
    uint16_t Bytes = 0xABCD;
    uint8_t ByteArray[2] = { 0xAB, 0xCD };

    print_bytes(Bytes);
    print_bytes(ByteArray);

    uint32_t Bytes2 = 0x1234ABCD;
    uint8_t ByteArray2[4] = { 0x12, 0x34, 0xAB, 0xCD };

    print_bytes(Bytes2);
    print_bytes(ByteArray2);

    uint32_t Bytes3 = 0xABCD0000;
    uint32_t Bytes4 = 0;

    std::memcpy(&Bytes4, &Bytes3, 2);
    print_bytes(Bytes3);
    print_bytes(Bytes4);

    uint32_t Bytes5 = 0x0000ABCD;
    uint32_t Bytes6 = 0;

    std::memcpy(&Bytes6, &Bytes5, 2);
    print_bytes(Bytes5);
    print_bytes(Bytes6);
}
