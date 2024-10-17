#include "binary_trie.h"
#include <iostream>

TrieNode::TrieNode() = default;

TrieNode::TrieNode(int16_t _symbol, int32_t left, int32_t right): symbol(_symbol), go({left, right}) {
}

TrieNode::~TrieNode() {
}

void BinaryTrie::BuildHaffman(std::unordered_map<int16_t, int32_t>& frequencies) {
    trie_.push_back(std::shared_ptr<TrieNode>(new TrieNode(-1, 0, 0)));

    Heap<std::array<int32_t, 3>, decltype([](const std::array<int, 3>& i, const std::array<int, 3>& j) -> bool {
        return i < j;
    })> sorted_nodes;

    for (auto [symbol, frequency] : frequencies) {
        trie_.push_back(std::shared_ptr<TrieNode>(new TrieNode(symbol, 0, 0)));
        sorted_nodes.Push({frequency, symbol, static_cast<int32_t>(trie_.size() - 1)});

        // std::cout << "!! " << static_cast<int32_t>(trie_.size() - 1) << "\n";
    }

    for (; sorted_nodes.Size() > 1;) {
        auto [frequency1, symbol1, node1] = sorted_nodes.Top();
        sorted_nodes.Pop();
        auto [frequency2, symbol2, node2] = sorted_nodes.Top();
        sorted_nodes.Pop();

        trie_.push_back(std::shared_ptr<TrieNode>(new TrieNode(-1, node1, node2)));

        trie_[node1]->bit = false;
        trie_[node2]->bit = true;
        
        // std::cout << "!! " << node1 << " " << node2 << "\n";

        sorted_nodes.Push({frequency1 + frequency2, -1, static_cast<int32_t>(trie_.size() - 1)});
    }
    LabelNodes(trie_.size() - 1, 0);
    std::sort(trie_.begin() + 1, trie_.end(), [](const std::shared_ptr<TrieNode>& element1, const std::shared_ptr<TrieNode>& element2) -> bool {
        return element1->position < element2->position;
    });
}

void BinaryTrie::LabelNodes(int32_t current, int depth_) {
    if (current == 0) {
        return;
    }
    trie_[current]->position = ++last_index_;
    trie_[current]->depth = depth_;

    LabelNodes(trie_[current]->go[0], depth_ + 1);
    LabelNodes(trie_[current]->go[1], depth_ + 1);

    trie_[current]->go[0] = trie_[trie_[current]->go[0]]->position;
    trie_[current]->go[1] = trie_[trie_[current]->go[1]]->position;
}

std::unordered_map<int16_t, size_t> BinaryTrie::GetCodes() {
    std::unordered_map<int16_t, size_t> result;
    for (int current_node = 2; current_node < trie_.size(); current_node++) {
        if (trie_[current_node]->symbol != -1) {
            result[trie_[current_node]->symbol] = trie_[current_node]->depth;
        }
    }
    return result;
}