#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS() {
        capacity = 1;
        curr_size = 0;
        array = nullptr;
    };
    explicit ABS(const size_t capacity) {
        this->capacity = capacity;
        curr_size = 0;
        array = nullptr;
    };
    ABS(const ABS& other) {
        
    };
    ABS& operator=(const ABS& rhs) {
        if (this == &rhs) { return *this; }
        array = rhs.array;
        
    };
    ABS(ABS&& other) noexcept {

    };
    ABS& operator=(ABS&& rhs) noexcept {
        
    };
    ~ABS() noexcept {

    };

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {
        return curr_size;
    };

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {
        return capacity;
    };

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {
        return array;
    };

    // Push item onto the stack
    void push(const T& data) override {
        if (curr_size == capacity) {
            T* temp = new T[capacity * 2];
            // copy all 
            delete[] this->array;
            this->array = temp;
            this->capacity *= 2;
        }
        array[curr_size] = data;
        curr_size++;
    };

    T peek() const override {
        return array[curr_size-1];        
    };

    T pop() override {
        if (curr_size == 0) {
            throw std::runtime_error("tried to pop from empty array");
        }
        
        T val = array[curr_size-1];
        curr_size--;

        if (capacity > 1 && curr_size <= capacity / 4) {
            capacity /= 2;
            T* newArr = new T[capacity];
            for (size_t i = 0; i < curr_size; i++) {
                newArr[i] = array[i];
            }
            delete[] array;
            this->array = newArr;
        }
        return val;
    };

private:
    size_t capacity;
    size_t curr_size;
    T* array;
    static constexpr size_t scale_factor= 2;
};
