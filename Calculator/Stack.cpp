#include "Stack.h"

template <class T>
Stack<T>::Stack(size_t size) {
    top = size - 1;
    index = top;
    stack = new T[size];
};

template <class T>
void Stack<T>::push(T item) {
    stack[index--] = item;
};

template <class T>
T Stack<T>::pop() {
    return stack[++index];
}