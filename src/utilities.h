#pragma once

#include <cstdint>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "bit_istream.h"

constexpr int16_t FILENAME_END = 256;
constexpr int16_t ONE_MORE_FILE = 257;
constexpr int16_t ARCHIVE_END = 258;

template<typename T> 
std::ostream& operator << (std::ostream& out, std::vector<T> a) {
    for (auto el : a) {
        out << el << " ";
    }
    return out;
}

std::unordered_map<int16_t, int32_t> GetSymbolsFrequency(const char*);

class Byte9 {
public:
    Byte9(int16_t);
    ~Byte9() = default;
    std::vector<bool> Get();
    template<typename T>
    void Read(BitIstream<T>& in) {
        for (int i = 0; i < number.size(); i++) {
            number[i] = in.Get();
        }
    }
private:
    std::vector<bool> number;
};