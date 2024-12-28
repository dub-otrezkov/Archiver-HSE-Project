#pragma once

#include <functional>
#include <vector>

template <typename T, class Compare = std::less<T> >
class Heap {
public:
    Heap() : size_(0) {
    }

    ~Heap() = default;

    void Push(T new_val) {
        ++size_;
        elements_.push_back(new_val);
        for (int v = elements_.size() - 1; v > 0 && Compare{}(elements_[v], elements_[(v - 1) >> 1]);
             std::swap(elements_[v], elements_[(v - 1) >> 1]), v = (v - 1) >> 1) {
        }
    }

    void Pop() {
        if (size_ == 0) {
            return;
        }

        --size_;
        std::swap(elements_[0], elements_.back());
        elements_.pop_back();
        for (size_t v = 0; v * 2 + 1 < elements_.size();) {
            if (Compare{}(elements_[v * 2 + 1], elements_[v]) &&
                (v * 2 + 2 == elements_.size() || !Compare{}(elements_[v * 2 + 2], elements_[v * 2 + 1]))) {
                std::swap(elements_[v], elements_[v * 2 + 1]);
                v = v * 2 + 1;
            } else if (v * 2 + 2 < elements_.size() && Compare{}(elements_[v * 2 + 2], elements_[v])) {
                std::swap(elements_[v], elements_[v * 2 + 2]);
                v = v * 2 + 2;
            } else {
                break;
            }
        }
    }

    T Top() {
        return elements_[0];
    }

    size_t Size() {
        return size_;
    }

private:
    std::vector<T> elements_;
    size_t size_;
};
