#include "archive.h"
#include "utilities.h"
#include "binary_trie.h"
#include "bit_ostream.h"
#include <iostream>

void Archive(const char* target, const std::vector<const char*>& filenames) {
    BitOstream<std::ofstream> out(target);

    for (int filename_index = 0; filename_index < filenames.size(); filename_index++) {
        std::unordered_map<int16_t, int32_t> frequency = GetSymbolsFrequency(filenames[filename_index]);
        BinaryTrie trie;
        trie.BuildHaffman
        (frequency);
        std::unordered_map<int16_t, size_t> codes_lengths = trie.GetCodes();
        std::vector<std::pair<size_t, int16_t>> codes_to_sort;
        for (const std::pair<int16_t, size_t>& element : codes_lengths) {
            codes_to_sort.push_back(std::make_pair(element.second, element.first));
        }
        std::sort(codes_to_sort.begin(), codes_to_sort.end());
        int current_pos = 0;

        std::unordered_map<int16_t, std::vector<bool>> codes;
        codes[codes_to_sort[0].second] = std::vector<bool>(codes_to_sort[0].first, false);
        for (int i = 1; i < codes_to_sort.size(); i++) {
            codes[codes_to_sort[i].second] = codes[codes_to_sort[i - 1].second];
            for (int bit = 0; bit < codes_to_sort[i].first; bit++) {
                codes[codes_to_sort[i].second][bit] = !codes[codes_to_sort[i].second][bit];
                if (codes[codes_to_sort[i].second][bit]) {
                    break;
                }
            }
            for (; codes[codes_to_sort[i].second].size() < codes_to_sort[i].first;) {
                codes[codes_to_sort[i].second].insert(codes[codes_to_sort[i].second].begin(), false);
            }
        }

        // for (auto [f, s] : codes) {
        //     std::cout << f << " " << (char) f << ": ";
        //     for (auto i : s) std::cout << i;
        //     std::cout << "\n";
        // }

        out.Write(Byte9(codes.size()).Get());

        int j = 0;

        for (int i = 0; i < codes_to_sort.back().first; i++) {
            int cnt = 0;
            for (; j < codes_to_sort.size() && codes_to_sort[j].first == i + 1; cnt++, j++) {
            }
            out.Write(Byte9(cnt).Get());
        }
        for (int i = 0; i < codes_to_sort.size(); i++) {
            out.Write(Byte9(codes_to_sort[i].second).Get());
        }
        for (int i = 0; filenames[filename_index][i] != '\0'; i++) {
            out.Write(codes[filenames[filename_index][i]]);
        }
        out.Write(codes[FILENAME_END]);

        std::ifstream file(filenames[filename_index]);
        for (;;) {
            file.peek();
            if (file.eof()) {
                break;
            }

            char x;
            file.get(x);

            // std::cout << (char) x << " " << codes[x] << "\n";
            out.Write(codes[x]);
        }

        if (filename_index + 1 == filenames.size()) {
            out.Write(codes[ARCHIVE_END]);
        } else {
            out.Write(codes[ONE_MORE_FILE]);
        }
    }
}
