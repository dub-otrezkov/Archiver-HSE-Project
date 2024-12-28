#pragma once

#include "bit_istream.h"
#include "constants.h"

#include <numeric>
#include <stdexcept>
#include <vector>

class CustomByte {
public:
    explicit CustomByte(int16_t);
    explicit CustomByte(int16_t, int16_t);
    ~CustomByte() = default;
    std::vector<bool> Get();
    template <typename T>
    void Read(BitIstream<T>& in) {
        for (size_t i = 0; i < number_.size(); i++) {
            number_[i] = in.Get();
        }
    }

    int16_t GetNumber();

private:
    int16_t count_of_bits_;
    std::vector<bool> number_;
};