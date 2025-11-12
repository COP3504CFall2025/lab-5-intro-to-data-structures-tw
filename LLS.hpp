#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() {
        list = LinkedList<T>{};
    };

    // Insertion
    void push(const T& item) override {
        list.addTail(item);
    };

    // Deletion
    T pop() override {
        if (getSize() == 0) throw std::runtime_error("");
        T val = list.getTail()->data;
        list.removeTail();
        return val;
    };

    // Access
    T peek() const override {
        if (getSize() == 0) throw std::runtime_error("");
        return list.getTail()->data;
    };

    //Getters
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };
};