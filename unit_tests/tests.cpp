#include <catch.hpp>

#include <iostream>
#include <sstream>

#include "../src/heap.h"
#include "../src/binary_trie.h"
#include "../src/bit_istream.h"

TEST_CASE("heap_test") {
    Heap<std::string> h;
    REQUIRE(h.Size() == 0);
    h.Push("3");
    h.Push("2");
    h.Push("1");
    h.Push("4");
    h.Push("1");
    REQUIRE(h.Size() == 5);
    REQUIRE(h.Top() == "1");
    h.Pop();
    REQUIRE(h.Top() == "1");
    h.Pop();
    REQUIRE(h.Top() == "2");
    REQUIRE(h.Size() == 3);
}

TEST_CASE("heap_test_custom_comp") {
    Heap<int, decltype([](int i, int j) -> bool {
        return i > j;
    })> h;
    REQUIRE(h.Size() == 0);
    h.Push(5);
    h.Push(1);
    h.Push(1);
    h.Push(4);
    h.Push(5);
    REQUIRE(h.Top() == 5);
    h.Pop();
    REQUIRE(h.Top() == 5);
    h.Pop();
    REQUIRE(h.Top() == 4);
}

TEST_CASE("trie_test") {
    BinaryTrie trie;
    trie.Add(1, {0, 0, 1, 1});
    trie.Add(2, {0, 1, 0});
    std::unordered_map<int16_t, size_t> res = trie.GetLengthOfCodes();
    std::unordered_map<int16_t, size_t> need = {
        {1, 4},
        {2, 3}
    };
    REQUIRE(res == need);
}

TEST_CASE("bit_ostream") {
    BitIstream<std::ifstream> in("D:\\HSE\\CPPHSE\\ami-Viacheslav-Kozitskii-SVO_MONSTR\\tasks\\archiver\\unit_tests\\test_ifstream");
    std::vector<bool> need = {
        true,
        false,
        false,
        false,
        true,
        true,
        false
    };
    std::vector<bool> result(need.size());
    for (size_t i = 0; i < result.size(); i++) {
        result[i] = in.Get();
    }
    REQUIRE(result == need);
}