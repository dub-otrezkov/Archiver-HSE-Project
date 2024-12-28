#pragma once

#include "constants.h"

#include <algorithm>
#include <cstdint>
#include <fstream>
#include <unordered_map>
#include <vector>

char ReverseChar(char);

int16_t CharToInt16(char);

template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> a) {
    for (auto el : a) {
        out << el << " ";
    }
    return out;
}

std::unordered_map<int16_t, int64_t> GetSymbolsFrequency(std::string);

std::unordered_map<int16_t, std::vector<bool>> GetNormalCode(const std::vector<std::pair<size_t, int16_t>>&);
