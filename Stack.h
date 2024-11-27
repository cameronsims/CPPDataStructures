#ifndef CSSTACK_H
#define CSSTACK_H

#include "LinkedList.h"

namespace cslib {
    class StackException : public OutOfRange {};
    class StackOverflow : public StackException {
    public:
        const char* what() const throw();
    };
    class StackUnderflow : public StackException {
        const char* what() const throw();
    };

    template<typename T>
    class Stack : protected LinkedList<T> {
    public:
        size_t size() const;
        bool empty() const;

              T& top();
        const T& top() const;

        T  pop();
        T& push(const T& p_data);

        class Iterator : public LinkedList<T>::Iterator {};
        class ConstIterator : public LinkedList<T>::ConstIterator {};

        Iterator begin();
        ConstIterator cbegin();
        Iterator end();
        ConstIterator cend();
    private:
        struct Node : public LinkedList<T>::Node {};
    };
}

const char* cslib::StackOverflow::what() const { return "Stack Overflow"; }
const char* cslib::StackUnderflow::what() const { return "Stack Underflow"; }

template<typename T>
size_t cslib::Stack<T>::size() const {
    // Get size from 
    return this->size();
}

template<typename T>
bool cslib::Stack<T>::empty() const {
    // Get size from 
    return (this->m_data == nullptr);
}

template<typename T>
T& cslib::Stack<T>::top() {
    if (this->empty()) {
        throw StackUnderflow();
    }
    return this->m_data->data;
}

template<typename T>
const T& cslib::Stack<T>::top() const {
    if (this->empty()) {
        throw StackUnderflow();
    }
    return this->m_data->data;
}

template<typename T>
T cslib::Stack<T>::pop() {
    if (this->empty()) {
        throw StackUnderflow();
    }

    // Save root value
    T temp = this->m_data->data;
    
    // Clear node
    Node* node = (Node*)this->m_data->next;
    delete this->m_data;

    // Save new root
    this->m_data = node;

    return temp;
}

template<typename T>
T& cslib::Stack<T>::push(const T& p_data) {
    // Get the current value
    Node* next = (Node*)this->m_data;

    Node* node = nullptr;
    
    try {
        node = new Node;
    } catch (const std::exception& e) {
        throw StackOverflow();
    }

    node->data = p_data;
    node->next = next;

    this->m_data = node;
    return node->data;
}

template<typename T>
typename cslib::Stack<T>::Iterator cslib::Stack<T>::begin() {
    return this->begin();
}

template<typename T>
typename cslib::Stack<T>::ConstIterator cslib::Stack<T>::cbegin() {
    return this->cbegin();
}

template<typename T>
typename cslib::Stack<T>::Iterator cslib::Stack<T>::end() {
    return this->end();
}

template<typename T>
typename cslib::Stack<T>::ConstIterator cslib::Stack<T>::cend() {
    return this->cend();
}



#endif