#include "binary_trie.h"
#include "constants.h"
#include "custom_byte.h"
#include "dearchive.h"
#include "utilities.h"

#include <filesystem>

void Dearchive(const char* archive) {
    if (!std::filesystem::exists((std::string(archive)))) {
        throw std::runtime_error("file search failed " + std::string(archive) + " " +
                                 std::filesystem::current_path().string());
    }

    BitIstream<std::ifstream> in((std::string(archive)).c_str());

    for (bool finished = false; !finished;) {

        CustomByte symbols_count(OutputIntegersBase);
        symbols_count.Read(in);

        std::vector<std::pair<size_t, int16_t>> lengths;

        for (int i = 0; i < symbols_count.GetNumber(); i++) {
            CustomByte elem(OutputIntegersBase);
            elem.Read(in);
            lengths.push_back(std::make_pair(0, elem.GetNumber()));
        }
        size_t to_set = 0;
        for (int i = 0; to_set < static_cast<size_t>(symbols_count.GetNumber()); i++) {
            CustomByte cnt_i(OutputIntegersBase);
            cnt_i.Read(in);
            for (int j = 0; j < cnt_i.GetNumber(); j++) {
                lengths[to_set].first = i + 1;
                ++to_set;
            }
        }

        std::unordered_map<int16_t, std::vector<bool>> codes = GetNormalCode(lengths);

        BinaryTrie trie(codes);
        BinaryTrie::Iterator current_iter = trie.Begin();

        std::string filename;

        for (;;) {
            bool r = in.Get();
            current_iter.Go(r);
            if (current_iter->symbol != -1) {
                if (current_iter->symbol == FilenameEnd) {
                    break;
                }
                filename.push_back(static_cast<char>(current_iter->symbol));
            }
        }

        std::ofstream out(filename, std::fstream::binary);
        std::vector<bool> cur;
        for (;;) {
            bool r = in.Get();
            current_iter.Go(r);

            cur.push_back(r);

            if (current_iter->symbol != -1) {
                if (current_iter->symbol == OneMoreFile) {
                    break;
                }
                if (current_iter->symbol == ArchiveEnd) {
                    finished = true;
                    return;
                }
                out << static_cast<char>(current_iter->symbol);
                cur.clear();
            }
        }
        out.close();
    }
}