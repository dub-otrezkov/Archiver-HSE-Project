#include "archive.h"
#include "binary_trie.h"
#include "bit_ostream.h"
#include "custom_byte.h"
#include "utilities.h"

#include <iostream>

void Archive(const char* target, const std::vector<const char*>& filenames) {
    BitOstream<std::ofstream> out((std::string(target)).c_str());

    for (size_t filename_index = 0; filename_index < filenames.size(); ++filename_index) {
        std::string path = static_cast<std::string>(filenames[filename_index]);
        if (!std::filesystem::exists(path)) {
            throw std::runtime_error("file search failed " + path + " " + std::filesystem::current_path().string());
        }

        std::unordered_map<int16_t, int64_t> frequency = GetSymbolsFrequency(path.c_str());
        BinaryTrie trie(frequency);
        std::unordered_map<int16_t, size_t> codes_lengths = trie.GetLengthOfCodes();
        std::vector<std::pair<size_t, int16_t>> codes_to_sort;
        for (std::pair<int16_t, size_t> element : codes_lengths) {
            codes_to_sort.push_back(std::make_pair(element.second, element.first));
        }
        std::sort(codes_to_sort.begin(), codes_to_sort.end());

        std::unordered_map<int16_t, std::vector<bool>> codes = GetNormalCode(codes_to_sort);

        out.Write(CustomByte(OutputIntegersBase, static_cast<int16_t>(codes.size())).Get());

        for (size_t i = 0; i < codes_to_sort.size(); i++) {
            out.Write(CustomByte(OutputIntegersBase, codes_to_sort[i].second).Get());
        }
        size_t next_length_to_check = 0;

        for (size_t i = 0; i < codes_to_sort.back().first; i++) {
            int16_t count_of_i_length = 0;
            for (; next_length_to_check < codes_to_sort.size() && codes_to_sort[next_length_to_check].first == i + 1;
                 count_of_i_length++, next_length_to_check++) {
            }
            out.Write(CustomByte(OutputIntegersBase, count_of_i_length).Get());
        }

        std::string name;
        ssize_t filename_size = path.end() - path.begin();
        for (ssize_t i = filename_size - 1; i >= 0 && filenames[filename_index][i] != '/'; i--) {
            name += filenames[filename_index][i];
        }
        std::reverse(name.begin(), name.end());

        for (char symbol : name) {
            out.Write(codes[CharToInt16(symbol)]);
        }
        out.Write(codes[FilenameEnd]);

        std::ifstream file(path, std::fstream::binary);

        if (!file.is_open()) {
            throw std::runtime_error("no such file");
        }

        for (;;) {
            file.peek();
            if (file.eof()) {
                break;
            }

            char symbol = 0;
            file.get(symbol);

            out.Write(codes[CharToInt16(symbol)]);
        }

        if (filename_index + 1 == filenames.size()) {
            out.Write(codes[ArchiveEnd]);
        } else {
            out.Write(codes[OneMoreFile]);
        }
    }
}
