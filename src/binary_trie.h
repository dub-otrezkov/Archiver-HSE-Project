#pragma once

#include "heap.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <unordered_map>

struct TrieNode {
    std::array<size_t, 2> go;
    int32_t depth;
    int16_t symbol;
    bool bit;

    TrieNode();
    TrieNode(int16_t, size_t, size_t);
    ~TrieNode();
};

class BinaryTrie {
public:
    BinaryTrie();
    explicit BinaryTrie(const std::unordered_map<int16_t, std::vector<bool>>&);
    explicit BinaryTrie(const std::unordered_map<int16_t, int64_t>&);
    ~BinaryTrie();
    std::unordered_map<int16_t, size_t> GetLengthOfCodes();
    void Add(int16_t, std::vector<bool>);

    class Iterator {
    public:
        Iterator();
        explicit Iterator(BinaryTrie*);
        ~Iterator();

        void Go(bool);
        TrieNode* operator->();

    private:
        size_t vertex_index_;
        BinaryTrie* base_;
    };

    Iterator Begin();

protected:
    std::vector<TrieNode*> trie_;
    size_t root_index_;

private:
    void LabelNodes(size_t, int32_t);
    Iterator begin_;
    friend Iterator;
};