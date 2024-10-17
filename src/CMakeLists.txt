add_executable(
    archiver
    archiver.cpp
    archive.h
    archive.cpp
    dearchive.h
    dearchive.cpp
    utilities.h
    utilities.cpp
    binary_trie.h
    binary_trie.cpp
    bit_ostream.h
    bit_istream.h
    hello.txt
)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/hello.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})