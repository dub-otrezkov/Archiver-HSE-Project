#pragma once

#include "constants.h"
#include "utilities.h"

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <vector>

template <typename in_stream>
class BitIstream {
public:
    BitIstream() : in_(in_stream()), buffer_(0), buffer_size_(0) {
    }
    explicit BitIstream(const char* file_path)
        : in_(in_stream(file_path, std::fstream::binary)), buffer_(0), buffer_size_(0) {
        if (!in_.is_open()) {
            throw std::runtime_error("no such file");
        }
    }

    ~BitIstream() {
        // in_.close();
    }

    bool Get() {
        in_.peek();
        if (buffer_size_ == 0) {
            if (in_.eof()) {
                throw std::runtime_error("reading from closed stream");
            }
            buffer_size_ = BitsInChar;
            in_.get(buffer_);
            buffer_ = ReverseChar(buffer_);
        }

        bool result = (buffer_ >> (BitsInChar - 1)) & 1;
        buffer_ = (buffer_ << 1);
        --buffer_size_;
        return result;
    }

private:
    in_stream in_;
    char buffer_;
    int8_t buffer_size_;
};