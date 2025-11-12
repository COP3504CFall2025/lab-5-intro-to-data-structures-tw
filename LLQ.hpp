#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() {
        list = LinkedList<T>{};
    };

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    };

    // Deletion
    T dequeue() override {
        if (getSize() == 0) throw std::runtime_error("");
        T val = peek();
        list.removeHead();
        return val;
    };

    // Access
    T peek() const override {
        if (getSize() == 0) throw std::runtime_error("");
        return list.getHead()->data;
    };

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    };

};