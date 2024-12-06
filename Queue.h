/**
 * @file Queue.h
 * @brief Holds the Queue Data Structure, Linear Data Structure. First-in-first out.
 **/

#ifndef CSQUEUE_H
#define CSQUEUE_H

#include "LinkedList.h"

namespace cslib {


    /**
     * @class Queue
     * @tparam T Type of the data structure.
     * @brief A First-in-first out data structure.
     **/
    template<typename T>
    class Queue : private LinkedList<T> {
    public:
        /**
         * @brief Constructs the data structure.
         */
        Queue();

        /**
         * @brief Gives the size of the stack, functions like a vector.
         * @return Size of the stack.
         */
        size_t size() const;

        /**
         * @brief Returns true if the data structure is empty
         * @return Returns true if empty, false if not.
         */
        bool empty() const;

        /**
         * @brief Gets the front value, the first put in.
         * @return Returns the next value that is to go.
         */
        T& front();

        /**
         * @brief Gets the front value, the first put in.
         * @return Returns the next value that is to go.
         */
        const T& front() const;

        /**
         * @param p_data The data that we are putting to the back of the stack.
         * 
         * @brief Adds value to back of stack.
         * @return Returns the value that was just placed in.
         */
        T& enqueue(const T& p_data);

        /**
         * @brief Pops the front of the stack, next value is now the value placed after "this" value.
         * @return Returns the value that just got dequeued.
         */
        T  dequeue();

        /// The iterator type in the Queue
        typedef LinkedList<T>::Iterator Iterator;

        /// The const iterator type in the Queue
        typedef LinkedList<T>::ConstIterator ConstIterator;

        /**
         * @brief Gets the top value of the queue by iterator.
         * @return Iterator representing top of the queue
         */
        Iterator begin();

        /**
         * @brief Gets the top value of the queue by iterator.
         * @return Iterator representing top of the queue
         */
        ConstIterator cbegin() const;

        /**
         * @brief Gets the value right after the end of the queue by iterator.
         * @return Iterator representing past the bottom of the stack
         */
        Iterator end();

        /**
         * @brief Gets the value right after the end of the queue by iterator.
         * @return Iterator representing past the bottom of the stack
         */
        ConstIterator cend() const;
    private:
        typedef LinkedList<T>::Node Node;
    };
}

template<typename T>
cslib::Queue<T>::Queue() : cslib::LinkedList<T>() {

}

template<typename T>
size_t cslib::Queue<T>::size() const {
    // If root was null...
    if (this->m_data == nullptr) {
        return 0;
    }
    
    // Loop until we reach end
    size_t i = 1;
    Node* node = this->m_data;
    while (node->next != nullptr) {
        node = node->next;
        i++;
    }
    return i + 1;
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
    return this->append(p_data);;
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

    return Iterator(nullptr);
}

template<typename T>
typename cslib::Queue<T>::ConstIterator cslib::Queue<T>::cend() const  {
    if (this->m_last == nullptr) {
        return ConstIterator(nullptr);
    }

    return ConstIterator(nullptr);
}





#endif