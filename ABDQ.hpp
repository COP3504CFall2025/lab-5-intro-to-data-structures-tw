#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;
    void resize() {
        std::size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * SCALE_FACTOR;
        T* new_data = new T[new_capacity];

        for (std::size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[(front_ + i) % capacity_];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
        front_ = 0;
        back_ = size_;
    }

public:
    // Big 5
    ABDQ() {
        capacity_ = 1;
        size_ = 0;
        front_ = 0;
        back_ = 0;
        data_ = new T[1];
    };
    explicit ABDQ(std::size_t capacity) {
        data_ = new T[capacity];
        capacity_ = capacity;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    };
    ABDQ(const ABDQ& other) {
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data_[i];
        }
    };
    ABDQ(ABDQ&& other) noexcept {
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    };
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) { return *this; }
        delete[] data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        data_ = new T[capacity_];
        for (size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data_[i];
        }
        return *this;
    };
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) { return *this; }

        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        
        return *this;
    };
    ~ABDQ() {
        delete[] data_;
    };

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            resize();
        }
        front_ = (front_ + capacity_ - 1) % capacity_;
        data_[front_] = item;
        size_++;
    };
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            resize();
        }
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    };

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("size 0");
        }
        T item = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        return item;
    };
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("size 0");
        }
        back_ = (back_ + capacity_ - 1) % capacity_;
        T item = data_[back_];
        size_--;
        return item;      
    };

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("size 0");
        return data_[front_];
    };
    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("size 0");
        size_t actual_back = (back_ - 1 + capacity_) % capacity_;
        return data_[actual_back];
    };

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    };

};
