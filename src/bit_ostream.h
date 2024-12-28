#pragma once

#include "constants.h"
#include "utilities.h"

#include <cstdint>
#include <fstream>
#include <vector>

template <typename out_stream>
class BitOstream {
public:
    BitOstream() : out_(out_stream()), buffer_(0), buffer_size_(0) {
    }
    explicit BitOstream(const char* file_path)
        : out_(out_stream(file_path, std::fstream::binary)), buffer_(0), buffer_size_(0) {
    }

    ~BitOstream() {
        Flush();
        out_.close();
    }

    void Flush() {
        buffer_ = (buffer_ << (BitsInChar - buffer_size_));
        buffer_ = ReverseChar(buffer_);
        out_ << buffer_;
        buffer_size_ = 0;
        buffer_ = 0;
    }

    void Write(bool bit) {
        buffer_ = (buffer_ << 1) | bit;
        ++buffer_size_;
        if (buffer_size_ == BitsInChar) {
            Flush();
        }
    }

    void Write(const std::vector<bool>& bits) {
        for (bool bit : bits) {
            Write(bit);
        }
    }

private:
    out_stream out_;
    int8_t buffer_;
    int8_t buffer_size_;
};