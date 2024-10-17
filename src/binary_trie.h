#include <unordered_map>
#include <cstdint>
#include <memory>
#include <algorithm>

#include "heap.h"

struct TrieNode {
    int16_t symbol;
    bool bit;
    int32_t position;
    int32_t depth = 0;
    std::array<int32_t, 2> go;

    TrieNode();
    TrieNode(int16_t, int32_t, int32_t);
    ~TrieNode();
};

class BinaryTrie {
public:
    void BuildHaffman(std::unordered_map<int16_t, int32_t>&);
    std::unordered_map<int16_t, size_t> GetCodes();
private:
    int last_index_ = 1;
    void LabelNodes(int32_t, int32_t);
    std::vector<std::shared_ptr<TrieNode>> trie_;
};