/**
 * @file Stack.h
 * @brief Holds the Stack Data Structure, Linear Data Structure. Last-in-first out.
 **/

#ifndef CSSTACK_H
#define CSSTACK_H

#include "LinkedList.h"

namespace cslib {
    /**
     * @class StackException
     * @brief Base for all exceptions thrown by the stack
     **/
    class StackException : public OutOfRange {};
    
    /**
     * @class StackOverflow
     * @brief Base for overflow exceptions from the stack
     **/
    class StackOverflow : public StackException {
    public:
        const char* what() const throw();
    };
    
    /**
     * @class StackUnderflow
     * @brief Base for underflows of the stack
     **/
    class StackUnderflow : public StackException {
        const char* what() const throw();
    };


    /**
     * @class Stack
     * @tparam T Type of the data structure.
     * @brief A Last-in-first out data structure.
     **/
    template<typename T>
    class Stack : private LinkedList<T> {
    public:
        /**
         * @brief Constructor for the Stack Data Structure 
         */
        Stack();

        /**
         * @brief Returns the size of the stack.
         * @return Returns the size of a stack.
         */
        size_t size() const;
        
        /**
         * @brief Returns true if there is no data in the data structure.
         * @return True if empty, false if at least one item.
         */
        bool empty() const;

        /**
         * @brief Gets the top value of the stack without poping.
         * @return Top value of the stack.
         */
        T& top();

        /**
         * @brief Gets the top value of the stack without poping.
         * @return Top value of the stack.
         */
        const T& top() const;

        /**
         * @brief Removes the top value from the stack.
         * @return Gives the popped value back
         */
        T  pop();

        /**
         * @param p_data The data we are adding to the top of the stack. 
         * 
         * @brief Adds the parameter into the top of the stack
         * @return Top value of the stack.
         */
        T& push(const T& p_data);

        /// The iterator type in the Stack
        typedef LinkedList<T>::Iterator Iterator;

        /// The const iterator type in the Stack
        typedef LinkedList<T>::ConstIterator ConstIterator;

        /**
         * @brief Gets the top value of the stack by iterator.
         * @return Iterator representing top of the stack
         */
        Iterator begin();

        /**
         * @brief Gets the top value of the stack by iterator.
         * @return Iterator representing top of the stack
         */
        ConstIterator cbegin() const;
        
        /**
         * @brief Gets the value right after the end of the stack by iterator.
         * @return Iterator representing past the bottom of the stack
         */
        Iterator end();
        
        /**
         * @brief Gets the value right after the end of the stack by iterator.
         * @return Iterator representing past the bottom of the stack
         */
        ConstIterator cend() const;
    private:
        /// The node in the Stack
        typedef LinkedList<T>::Node Node;
    };
}

const char* cslib::StackOverflow::what() const throw() { return "Stack Overflow"; }
const char* cslib::StackUnderflow::what() const throw() { return "Stack Underflow"; }

template<typename T>
cslib::Stack<T>::Stack() : cslib::LinkedList<T>() {

}

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
typename cslib::Stack<T>::ConstIterator cslib::Stack<T>::cbegin() const {
    return this->cbegin();
}

template<typename T>
typename cslib::Stack<T>::Iterator cslib::Stack<T>::end() {
    return this->end();
}

template<typename T>
typename cslib::Stack<T>::ConstIterator cslib::Stack<T>::cend() const {
    return this->cend();
}



#endif