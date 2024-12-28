#include "constants.h"
#include "utilities.h"

#include <numeric>
#include <stdexcept>

char ReverseChar(char x) {
    char one = 1;
    for (char bit = 0; bit * 2 < BitsInChar; bit++) {
        if (((x >> bit) & 1) != ((x >> (BitsInChar - bit - 1)) & 1)) {
            x = static_cast<char>(
                std::min(x ^ static_cast<char>(one << bit), static_cast<int>(std::numeric_limits<char>::max())));
            x = static_cast<char>(std::min(x ^ static_cast<char>(one << (BitsInChar - bit - 1)),
                                           static_cast<int>(std::numeric_limits<char>::max())));
        }
    }
    return x;
}

int16_t CharToInt16(char x) {
    int16_t result = 0;
    int16_t power_of_2 = 1;
    for (int16_t i = 0; i < BitsInChar; i++) {
        if (((x >> i) & 1) == 1) {
            result = static_cast<int16_t>(
                std::min(result + power_of_2, static_cast<int>(std::numeric_limits<int16_t>::max())));
        }
        power_of_2 = static_cast<int16_t>(
            std::min(power_of_2 + power_of_2, static_cast<int>(std::numeric_limits<int16_t>::max())));
    }
    return result;
}

std::unordered_map<int16_t, int64_t> GetSymbolsFrequency(std::string filename) {
    std::unordered_map<int16_t, int64_t> frequencies;
    for (int i = 0; filename[i] != '\0'; i++) {
        ++frequencies[filename[i]];
    }
    ++frequencies[FilenameEnd];
    ++frequencies[ArchiveEnd];
    ++frequencies[OneMoreFile];

    std::ifstream file(filename, std::fstream::binary);

    for (;;) {
        file.peek();
        if (file.eof()) {
            break;
        }
        char symbol = 0;
        file.get(symbol);

        ++frequencies[CharToInt16(symbol)];
    }
    return frequencies;
}

std::unordered_map<int16_t, std::vector<bool>> GetNormalCode(
    const std::vector<std::pair<size_t, int16_t>>& codes_to_sort) {

    std::unordered_map<int16_t, std::vector<bool>> codes;
    codes[codes_to_sort[0].second] = std::vector<bool>(codes_to_sort[0].first, false);
    for (size_t i = 1; i < codes_to_sort.size(); i++) {
        codes[codes_to_sort[i].second] = codes[codes_to_sort[i - 1].second];
        for (size_t bit = 0; bit < codes_to_sort[i].first; bit++) {
            codes[codes_to_sort[i].second][bit] = !codes[codes_to_sort[i].second][bit];
            if (codes[codes_to_sort[i].second][bit]) {
                break;
            }
        }
        for (; codes[codes_to_sort[i].second].size() < codes_to_sort[i].first;) {
            codes[codes_to_sort[i].second].insert(codes[codes_to_sort[i].second].begin(), false);
        }
    }
    for (auto& [symbol, code] : codes) {
        std::reverse(code.begin(), code.end());
    }
    return codes;
}
