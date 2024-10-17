#include "utilities.h"
#include <iostream>

std::unordered_map<int16_t, int32_t> GetSymbolsFrequency(const char* filename) {
    std::unordered_map<int16_t, int32_t> frequencies;
    for (int i = 0; filename[i] != '\0'; i++) {
        ++frequencies[filename[i]];
    }
    ++frequencies[FILENAME_END];
    ++frequencies[ARCHIVE_END];
    ++frequencies[ONE_MORE_FILE];

    std::ifstream file(filename);

    for (;;) {
        file.peek();
        if (file.eof()) {
            break;
        }
        char x;
        file.get(x);

        // std::cout << (int) x << " " << (char) x << "!\n";
        ++frequencies[x];
    }
    return frequencies;
}

Byte9::Byte9(int16_t value = 0) {
    number.assign(9, false);
    for (int bit = 0; bit < 9; ++bit) {
        number[bit] = (value >> bit) & 1;
    }
}

std::vector<bool> Byte9::Get() {
    return number;
}


// template<typename T>
// BitIstream<T>& Byte9::operator>> (BitIstream<T>& in, Byte9& x) {
//     in >> x.number;
//     return in;
// }