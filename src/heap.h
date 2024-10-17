#pragma once

#include <functional>
#include <vector>

template<
    typename T,
    class Compare = std::less<T>
>
class Heap {
public:
    Heap() :size_(0) {};
    ~Heap() {}

    void Push(T new_val) {
        ++size_;
        elements.push_back(new_val);
        for (int v = elements.size() - 1; v > 0 && Compare{}(elements[v], elements[(v - 1) >> 1]); std::swap(elements[v], elements[(v - 1) >> 1]), v = (v - 1) >> 1) {}
    }

    void Pop() {
        if (size_ == 0) {
            return;
        }
        
        --size_;
        std::swap(elements[0], elements.back());
        elements.pop_back();
        for (int v = 0; v * 2 + 1 < elements.size();) {
            if (Compare{}(elements[v * 2 + 1], elements[v]) && (v * 2 + 2 == elements.size() || !Compare{}(elements[v * 2 + 2], elements[v * 2 + 1]))) {
                std::swap(elements[v], elements[v * 2 + 1]);
                v = v * 2 + 1;
            } else if (v * 2 + 2 < elements.size() && Compare{}(elements[v * 2 + 2], elements[v])) {
                std::swap(elements[v], elements[v * 2 + 2]);
                v = v * 2 + 2;
            } else {
                break;
            }
        }
    }

    T Top() {
        return elements[0];
    }

    size_t Size() {
        return size_;
    }

private:
    std::vector<T> elements;
    size_t size_;
};
