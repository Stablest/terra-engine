#pragma once
#include <vector>

template <typename T>
class DenseArray {
    std::vector<T> dense_;

public:
    void add(const T& value) {
        dense_.push_back(value);
    }

    void add(T&& value) {
        dense_.push_back(std::move(value));
    }

    void swap(int pos1, int pos2) {
        std::swap(dense_[pos1], dense_[pos2]);
    }

    void pop() {
        dense_.pop_back();
    }

    T& get(int pos) {
        return dense_[pos];
    }

    [[nodiscard]] int size() const {
        return dense_.size();
    }

    [[nodiscard]] bool empty() const {
        return dense_.empty();
    }

};
