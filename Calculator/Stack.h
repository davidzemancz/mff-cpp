#pragma once
template <class T>
class Stack {
    T* stack;
    size_t size, top;
    size_t index;
public:
    Stack(size_t size);
    void push(T item);
    T pop();
};
 