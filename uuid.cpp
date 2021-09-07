#include <iostream>
#include <cstdint>

inline void ByteToHexString(uint8_t Byte, char* HexStr)
{
    const uint8_t Mask = 0b00001111;

    const uint8_t Low = (Byte & Mask);
    const uint8_t High = (Byte & (Mask << 4)) >> 4;

    auto Conv = [&](const uint8_t V) {
        return V <= 9 ? '0' + V : 'A' + (V - 10);
    };
    HexStr[1] = Conv(Low);
    HexStr[0] = Conv(High);
}


int main()
{
    char Buf[3];
    Buf[2] = '\0';

    ByteToHexString(0x1A, Buf);
    std::cout << Buf << std::endl;
}
