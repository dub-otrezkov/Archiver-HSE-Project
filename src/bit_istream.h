#pragma once

#include <cstdint>
#include <vector>

template<typename in_stream>
class BitIstream {
public:
    BitIstream(const char* arg): in(in_stream(arg)), buffer_(0), buffer_size_(0) {};
    ~BitIstream() {
        in.close();
    }
    bool Get() {
        if (buffer_size_ == 0) {
            buffer_size_ = 8;
            in.get(buffer_);
        }

        bool result = (buffer_ >> 7) & 1;
        buffer_ = (buffer_ << 1);
        --buffer_size_;
        return result;
    }
private:
    in_stream in;
    char buffer_;
    int8_t buffer_size_;
};