#include "binary_trie.h"

TrieNode::TrieNode() : go({0, 0}), depth(0), symbol(-1), bit(false) {
}

TrieNode::TrieNode(int16_t symbol, size_t left, size_t right)
    : go({left, right}), depth(0), symbol(symbol), bit(false) {
}

TrieNode::~TrieNode() = default;

BinaryTrie::BinaryTrie() : trie_({new TrieNode(), new TrieNode()}), root_index_(1) {
}

BinaryTrie::BinaryTrie(const std::unordered_map<int16_t, std::vector<bool>>& values)
    : trie_({new TrieNode(), new TrieNode()}), root_index_(1) {

    for (auto& [symbol, code] : values) {
        Add(symbol, code);
    }
}

BinaryTrie::BinaryTrie(const std::unordered_map<int16_t, int64_t>& frequencies) : trie_({}) {
    trie_.push_back(new TrieNode());

    Heap<std::array<int64_t, 3>,
         decltype([](const std::array<int64_t, 3>& i, const std::array<int64_t, 3>& j) -> bool { return i < j; })>
        sorted_nodes;

    for (auto [symbol, frequency] : frequencies) {
        trie_.push_back(new TrieNode(symbol, 0, 0));
        sorted_nodes.Push({frequency, symbol, static_cast<int32_t>(trie_.size() - 1)});
    }

    for (; sorted_nodes.Size() > 1;) {
        auto [frequency1, symbol1, node1] = sorted_nodes.Top();
        sorted_nodes.Pop();
        auto [frequency2, symbol2, node2] = sorted_nodes.Top();
        sorted_nodes.Pop();

        trie_.push_back(new TrieNode(-1, static_cast<size_t>(node1), static_cast<size_t>(node2)));
        trie_[node1]->bit = false;
        trie_[node2]->bit = true;

        sorted_nodes.Push(
            {frequency1 + frequency2, std::min(symbol1, symbol2), static_cast<int32_t>(trie_.size() - 1)});
    }
    root_index_ = trie_.size() - 1;
    LabelNodes(root_index_, 0);
}

void BinaryTrie::LabelNodes(size_t current, int depth) {
    if (current == 0) {
        return;
    }
    trie_[current]->depth = depth;

    LabelNodes(trie_[current]->go[0], depth + 1);
    LabelNodes(trie_[current]->go[1], depth + 1);
}

BinaryTrie::~BinaryTrie() {
    for (size_t i = 0; i < trie_.size(); i++) {
        delete trie_[i];
    }
}

void BinaryTrie::Add(int16_t symbol, std::vector<bool> code) {
    size_t current_node = root_index_;
    for (bool bit : code) {
        if (trie_[current_node]->go[bit] == 0) {
            trie_[current_node]->go[bit] = trie_.size();
            trie_.push_back(new TrieNode());
            trie_.back()->bit = bit;
            trie_.back()->depth = trie_[current_node]->depth + 1;
        }
        current_node = trie_[current_node]->go[bit];
    }
    trie_[current_node]->symbol = symbol;
}

std::unordered_map<int16_t, size_t> BinaryTrie::GetLengthOfCodes() {
    std::unordered_map<int16_t, size_t> result;
    for (size_t current_node = 1; current_node < trie_.size(); current_node++) {
        if (trie_[current_node]->symbol != -1) {
            result[trie_[current_node]->symbol] = trie_[current_node]->depth;
        }
    }
    return result;
}

BinaryTrie::Iterator::Iterator(BinaryTrie* trie) : base_(trie) {
    vertex_index_ = base_->root_index_;
}

BinaryTrie::Iterator::Iterator() : vertex_index_(-1), base_(nullptr) {
}

BinaryTrie::Iterator::~Iterator() {
}

TrieNode* BinaryTrie::Iterator::operator->() {
    TrieNode* temp = base_->trie_[vertex_index_];
    return temp;
}

void BinaryTrie::Iterator::Go(bool bit) {
    if (base_->trie_[vertex_index_]->go[bit] == 0) {
        vertex_index_ = base_->root_index_;
    }
    vertex_index_ = base_->trie_[vertex_index_]->go[bit];
    if (vertex_index_ == 0) {
        throw std::runtime_error("went to invalid trie vertex");
    }
}

BinaryTrie::Iterator BinaryTrie::Begin() {
    return Iterator(this);
}