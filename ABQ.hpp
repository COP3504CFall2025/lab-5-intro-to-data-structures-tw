#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity;
    size_t curr_size;
    T* array;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ() {
        this->capacity = 1;
        curr_size = 0;
        array = new T[1];
    };
    explicit ABQ(const size_t capacity) {
        this->capacity = capacity;
        curr_size = 0;
        array = new T[capacity];
    };
    ABQ(const ABQ& other) {
        capacity = other.capacity;
        curr_size = other.curr_size;
        array = new T[other.capacity];
        for (size_t i = 0; i < other.getSize(); i++) {
            array[i] = other.array[i];
        }
    };
    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) { return *this; }

        array = rhs.array;
        curr_size = rhs.curr_size;
        capacity = rhs.capacity;

        rhs.array = nullptr;
        rhs.curr_size = 0;
        rhs.capacity = 0;
        return *this;
    };
    ABQ(ABQ&& other) noexcept {
        capacity = other.capacity;
        curr_size = other.curr_size;
        array = other.array;
        other.array = nullptr;
        other.capacity = 0;
        other.curr_size = 0;
    };
    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) { return *this; }
        delete[] array;
        
        capacity = rhs.capacity;
        curr_size = rhs.curr_size;
        array = rhs.array;
        rhs.array = nullptr;
        rhs.capacity = 0;
        rhs.curr_size = 0;
        return *this;
    };
    ~ABQ() noexcept {
        delete[] array;
        capacity = 0;
        curr_size = 0;
    };

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size;
    };
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity;
    };
    [[nodiscard]] T* getData() const noexcept {
        return array;
    };

    // Insertion
    void enqueue(const T& data) override {
        if (curr_size == capacity) {
            T* temp = new T[capacity * 2];
            for (size_t i = 0; i < curr_size; i++) {
                temp[i] = array[i];
            }
            delete[] this->array;
            this->array = temp;
            this->capacity *= 2;
        }
        array[curr_size] = data;
        curr_size++;
    };

    // Access
    T peek() const override {
        if (curr_size == 0) {
            throw std::runtime_error("tried to pop from empty array");
        }
        return array[0]; 
    };

    // Deletion
    T dequeue() override {
        if (curr_size == 0) {
            throw std::runtime_error("tried to pop from empty array");
        }
        
        T val = array[0];
        curr_size--;
        for (size_t i = 0; i < curr_size - 1; i++) {
            array[i] = array[i+1];
        }
        if (capacity > 1 && curr_size <= capacity / 4) {
            capacity /= 2;
            T* newArr = new T[capacity];
            for (size_t i = 0; i < curr_size - 1; i++) {
                newArr[i] = array[i+1];
            }
            delete[] array;
            this->array = newArr;
        }
        return val;
    };

};
