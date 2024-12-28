#include "custom_byte.h"

CustomByte::CustomByte(int16_t bits) : count_of_bits_(bits), number_(std::vector<bool>(bits, false)) {
}

CustomByte::CustomByte(int16_t bits, int16_t value) : count_of_bits_(bits), number_(std::vector<bool>(bits, false)) {
    number_.assign(count_of_bits_, false);
    for (int16_t bit = 0; bit < count_of_bits_; ++bit) {
        number_[bit] = (value >> bit) & 1;
    }
}

std::vector<bool> CustomByte::Get() {
    return number_;
}

int16_t CustomByte::GetNumber() {
    int result = 0;
    int power_of_2 = 1;
    for (int16_t i = 0; i < count_of_bits_; i++) {
        if (number_[i]) {
            result += power_of_2;
        }
        power_of_2 += power_of_2;
    }
    return static_cast<int16_t>(std::min(static_cast<int>(std::numeric_limits<int16_t>::max()), result));
}
