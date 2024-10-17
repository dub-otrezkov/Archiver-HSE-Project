#include <fstream>
#include <cstdint>
#include <vector>

template<typename out_stream>
class BitOstream {
public:
    BitOstream(const char* arg): out_(out_stream(arg)), buffer_(0), buffer_size_(0) {
    }

    ~BitOstream() {
        Flush();
        out_.close();
    }

    void Flush() {
        out_ << buffer_;
        buffer_size_ = 0;
        buffer_ = 0;
    }

    void Write(bool bit) {
        buffer_ = (buffer_ << 1) | bit;
        ++buffer_size_;
        if (buffer_size_ == 8) {
            Flush();
        }
    }

    void Write(std::vector<bool> bits) {
        for (bool bit : bits) {
            Write(bit);
        }
    }
private:
    out_stream out_;
    int8_t buffer_;
    int8_t buffer_size_;
};