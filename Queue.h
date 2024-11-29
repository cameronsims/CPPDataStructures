#ifndef CSQUEUE_H
#define CSQUEUE_H

#include "LinkedList.h"

namespace cslib {
    template<typename T>
    class Queue : private LinkedList<T> {
    public:
        Queue();

        size_t size() const;
        bool empty() const;

              T& front();
        const T& front() const;

        T& enqueue(const T& p_data);
        T  dequeue();

        class Iterator : public LinkedList<T>::Iterator {};
        class ConstIterator : public LinkedList<T>::ConstIterator {};

        Iterator begin();
        ConstIterator cbegin() const;
        Iterator end();
        ConstIterator cend() const;
    private:
        struct Node : public LinkedList<T>::Node {};

        Node* m_last;
    };
}

template<typename T>
cslib::Queue<T>::Queue() : cslib::LinkedList<T>(), m_last(nullptr) {

}

template<typename T>
size_t cslib::Queue<T>::size() const {
    this->size();
}

template<typename T>
bool cslib::Queue<T>::empty() const {
    return (this->m_data == nullptr);
}

template<typename T>
T& cslib::Queue<T>::front() {
    if (this->empty()) {
        throw OutOfRange();
    }

    return this->m_data->data;
}

template<typename T>
const T& cslib::Queue<T>::front() const {
    if (this->empty()) {
        throw OutOfRange();
    }

    return this->m_data->data;
}

template<typename T>
T& cslib::Queue<T>::enqueue(const T& p_data) {
    // Get new data 
    Node* node = new Node;
    node->data = p_data;
    node->next = nullptr;
    
    // If the current / last is nullptr...
    if (this->m_data == nullptr) {
        this->m_data = node;
        this->m_last = node;
        return node->data;
    }

    // Set last back by 1
    this->m_last->next = node;
    this->m_last = (Queue<T>::Node*)this->m_last->next;

    return node->data;
}

template<typename T>
T cslib::Queue<T>::dequeue() {
    // Get the front node.
    Node* node = (cslib::Queue<T>::Node*)this->m_data->next;

    // Delete the front
    T temp = this->m_data->data;
    delete this->m_data;

    // Set new front
    this->m_data = node;

    if (this->m_data == nullptr) {
        this->m_last = nullptr;
    }

    return temp;
}

template<typename T>
typename cslib::Queue<T>::Iterator cslib::Queue<T>::begin() {
    return this->begin();
}

template<typename T>
typename cslib::Queue<T>::ConstIterator cslib::Queue<T>::cbegin() const  {
    return this->cbegin();
}

template<typename T>
typename cslib::Queue<T>::Iterator cslib::Queue<T>::end() {
    if (this->m_last == nullptr) {
        return Iterator(nullptr);
    }

    return Iterator(this->m_last->next);
}

template<typename T>
typename cslib::Queue<T>::ConstIterator cslib::Queue<T>::cend() const  {
    if (this->m_last == nullptr) {
        return ConstIterator(nullptr);
    }

    return ConstIterator(this->m_last->next);
}





#endif