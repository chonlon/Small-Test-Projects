#include <cstdint>

enum class  Color : uint8_t {
    Black = 0x00,
    White = 0x01,

};

bool bittest(const uint8_t bits, const uint8_t bitnum) {
    return (bits & (0x01 << bitnum)) != 0;
}

struct JoyState {
    JoyState(const uint8_t bits)
        : up(!bittest(bits, 0)),
        down(!bittest(bits, 1)),
        left(!bittest(bits, 2)),
        right(!bittest(bits, 3)),
        fire(!bittest(bits, 4)) {}



    bool up;
    bool down;
    bool left;
    bool right;
    bool fire;
};

volatile uint8_t& memory(const uint16_t loc) {
    return *reinterpret_cast<uint8_t*>(loc);
}

JoyState joyPortA() {
    return JoyState(memory(0xDc00));
}

int main() {
    const auto update_border = [=](Color color) {
        memory(0xd020) = static_cast<uint8_t>(color);
    };

    while (true) {
        if (joyPortA().fire) {
            update_border(Color::White);
        }
        else {
            update_border(Color::Black);
        }
    }

    return 1;
}