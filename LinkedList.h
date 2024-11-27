// LinkedList.h 
#ifndef CSLINKEDLIST_H
#define CSLINKEDLIST_H

#include "Universal.h"

namespace cslib {
    template<typename T>
    class LinkedList {
    public:
        LinkedList();
        LinkedList(const LinkedList<T>& p_ll);
        LinkedList<T>& operator= (const LinkedList<T>& p_ll);
        ~LinkedList();

        size_t size() const;
              T& operator[](size_t p_index);
        const T& operator[](size_t p_index) const;

        T&   append(const T& p_data);
        T&   insert(const T& p_data, size_t p_index);
        void swap  (size_t p_left, size_t p_right);
        void remove(size_t p_index);

    protected:
        struct Node {
            T data;
            Node* next;
        };

        void m_copy(const LinkedList<T>& p_ll);

              Node* m_at(size_t p_index);
        const Node* m_at(size_t p_index) const;

        Node* m_data;
    public:
        class Iterator : public cslib::Iterator<LinkedList<T>::Node> {
        public:
            Iterator(LinkedList<T>::Node* p_ptr);
            Iterator& operator++();
            Iterator  operator++(int);

            T& operator* ();
            T* operator->();
        };

        class ConstIterator : public cslib::ConstIterator<LinkedList<T>::Node> {
        public:
            ConstIterator(const LinkedList<T>::Node* p_ptr);
            ConstIterator& operator++();
            ConstIterator  operator++(int);

            const T& operator* ();
            const T* operator->();
        };

        Iterator begin();
        ConstIterator cbegin() const;

        Iterator end();
        ConstIterator cend() const;
    };

    template<typename T>
    void LinkedList_reverse(LinkedList<T>& p_ll);
}



template<typename T>
cslib::LinkedList<T>::LinkedList() : m_data(nullptr) {}

template<typename T>
cslib::LinkedList<T>::LinkedList(const LinkedList<T>& p_ll) {
    m_copy(p_ll);
}

template<typename T>
cslib::LinkedList<T>& cslib::LinkedList<T>::operator= (const LinkedList<T>& p_ll) {
    m_copy(p_ll);
    return *this;
}

template<typename T>
cslib::LinkedList<T>::~LinkedList() {
    // Delete all and refocus
    Node* node = this->m_data;
    if (node == nullptr) {
        return;
    }
    while (node->next != nullptr) {
        Node* todo = node;
        node = node->next;

        delete todo;
    }
}

template<typename T>
size_t cslib::LinkedList<T>::size() const {
    // If nothing exists...
    if (m_data == nullptr) {
        return 0;
    }

    // This will be incremented
    size_t i = 0;

    // Until we are the end 
    Node* node = this->m_data;
    while (node != nullptr) {
        node = node->next;
        i++;
    }

    // Return the size
    return i;
}

template<typename T>
T& cslib::LinkedList<T>::operator[](size_t p_index) {
    Node* node = this->m_at(p_index);
    return node->data;
}

template<typename T>
const T& cslib::LinkedList<T>::operator[](size_t p_index) const {
    Node* node = this->m_at(p_index);
    return node->data;
}

template<typename T>
T& cslib::LinkedList<T>::append(const T& p_data) {
    // This is the value 
    Node* node = new Node;
    node->data = p_data;
    node->next = nullptr;

    if (this->m_data == nullptr) {
        this->m_data = node;
        return node->data;
    }

    // While we're not at the last
    Node* current = this->m_data;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = node;
    return node->data;
}

template<typename T>
T& cslib::LinkedList<T>::insert(const T& p_data, size_t p_index) {
    // Get size and create new node
    const size_t n = this->size();

    // Bound check
    if (p_index > n) {
        throw OutOfRange();
    }

    // If the index is the same as the size.
    if (p_index == n) {
        // Append
        return this->append(p_data);
    }

    Node* node = new Node;
    node->data = p_data;
    node->next = nullptr;

    // If we want to insert at the start
    if (p_index == 0) {
        // Get current start
        Node* next = this->m_data;
        node->next = next;
        this->m_data = node;
        return node->data;
    }

    // Otherwise, we will iterate until we get to the one we want
    size_t i = 1;
    Node* last = this->m_data;
    while (i != p_index) {
        // IF bounds are bad
        if (i < p_index && (last == nullptr || last->next == nullptr)) {
            throw OutOfRange();
        }

        last = last->next;
        i++;
    }

    // Add to last node
    Node* after = last->next;
    last->next = node;
    node->next = after;

    return node->data;

}

template<typename T>
void cslib::LinkedList<T>::swap(size_t p_left, size_t p_right) {
    // If both are the same...
    if (p_left == p_right) {
        return;
    }

    // Else find both and switch
    Node* left = this->m_at(p_left);
    Node* right = this->m_at(p_right);

    T temp = left->data;
    left->data = right->data;
    right->data = temp;

}

template<typename T>
void cslib::LinkedList<T>::remove(size_t p_index) {
    // Wait until good
    Node* last = nullptr;
    Node* node = this->m_data;
    if (node == nullptr) {
        throw OutOfRange();
    }

    size_t i = 0;
    for (size_t i = 0; i <= p_index; i++) {
        // If we're at 
        if (i == p_index) {
            // Get next value 
            Node* next = node->next;

            // Delete the current value
            delete node;

            // If last is nullptr
            if (last == nullptr) {
                this->m_data = next;
            } else {
                last->next = next;
            }
            return;
        }

        // If next is nullptr
        last = node;
        if (node->next == nullptr) {
            throw OutOfRange();
        }
        node = node->next;
    }

    throw OutOfRange();
}

template<typename T>
void cslib::LinkedList<T>::m_copy(const LinkedList<T>& p_ll) {
    // Get size of the other
    size_t n = p_ll.size();

    // If nothing
    if (n == 0) {
        this->m_data = nullptr;
        return;
    }

    // Add to the values
    Node* node = p_ll.m_data;

    // These are going to be added to "this"
    Node* last = nullptr;
    Node* next = nullptr;

    for (size_t i = 0; i < n; i++) {
        // Create new element 
        next = new Node;
        next->data = node->data;
        next->next = nullptr;

        // Do we have data?
        if (this->m_data == nullptr) {
            // If not, add next to this new data
            this->m_data = next;
        } else {
            last->next = next;
        }

        // Make next 
        node = node->next;
        last = next;
    }
}

template<typename T>
typename cslib::LinkedList<T>::Node* cslib::LinkedList<T>::m_at(size_t p_index) {
    // For each
    size_t i = 0;
    size_t n = this->size();

    // Check if valid relation
    if (p_index >= n) {
        throw OutOfRange();
    }

    // Get the element at
    Node* node = this->m_data;
    while (i < n) {
        // IF equal at position
        if (i == p_index) {
            return node;
        }

        node = node->next;
        i++;
    }

    throw OutOfRange();
}

template<typename T>
typename const cslib::LinkedList<T>::Node* cslib::LinkedList<T>::m_at(size_t p_index) const {
    // For each
    size_t i = 0;
    size_t n = this->size();

    // Check if valid relation
    if (p_index >= n) {
        throw OutOfRange();
    }

    // Get the element at
    const Node* node = this->m_data;
    while (i < n) {
        // IF equal at position
        if (i == p_index) {
            return node;
        }

        node = node->next;
        i++;
    }

    throw OutOfRange();
}

template<typename T>
typename cslib::LinkedList<T>::Iterator cslib::LinkedList<T>::begin() {
    Iterator it = Iterator(this->m_data);
    return it;
}

template<typename T>
typename cslib::LinkedList<T>::ConstIterator cslib::LinkedList<T>::cbegin() const {
    ConstIterator it(this->m_data);
    return it;
}

template<typename T>
typename cslib::LinkedList<T>::Iterator cslib::LinkedList<T>::end() {
    Iterator it = Iterator(nullptr);
    return it;
}

template<typename T>
typename cslib::LinkedList<T>::ConstIterator cslib::LinkedList<T>::cend() const {
    ConstIterator it(nullptr);
    return it;
}











template<typename T>
cslib::LinkedList<T>::Iterator::Iterator(cslib::LinkedList<T>::Node* p_ptr) {
    this->m_ptr = p_ptr;
}

template<typename T>
T& cslib::LinkedList<T>::Iterator::operator*() {
    return (this->m_ptr->data);
}

template<typename T>
T* cslib::LinkedList<T>::Iterator::operator->() {
    return &(this->m_ptr->data);
}

template<typename T>
typename cslib::LinkedList<T>::Iterator& cslib::LinkedList<T>::Iterator::operator++() {
    Node* next = this->m_ptr->next;
    this->m_ptr = next;
    return *this;
}

template<typename T>
typename cslib::LinkedList<T>::Iterator cslib::LinkedList<T>::Iterator::operator++(int) {
    Node* next = this->m_ptr->next;
    Iterator cpy = next;
    this->m_ptr = next;
    return cpy;
}

template<typename T>
cslib::LinkedList<T>::ConstIterator::ConstIterator(const cslib::LinkedList<T>::Node* p_ptr) {
    this->m_ptr = p_ptr;
}

template<typename T>
const T& cslib::LinkedList<T>::ConstIterator::operator*() {
    return (this->m_ptr->data);
}

template<typename T>
const T* cslib::LinkedList<T>::ConstIterator::operator->() {
    return &(this->m_ptr->data);
}

template<typename T>
typename cslib::LinkedList<T>::ConstIterator& cslib::LinkedList<T>::ConstIterator::operator++() {
    const Node* next = this->m_ptr->next;
    this->m_ptr = next;
    return *this;
}

template<typename T>
typename cslib::LinkedList<T>::ConstIterator cslib::LinkedList<T>::ConstIterator::operator++(int) {
    Node* next = this->m_ptr->next;
    ConstIterator cpy = next;
    this->m_ptr = next;
    return cpy;
}




// Helpers

template<typename T>
void cslib::LinkedList_reverse(cslib::LinkedList<T>& p_ll) {
    // Create an array
    const size_t n = p_ll.size();
    T* arr = new T[n];

    // Add to array
    size_t i = 0;
    for (auto it = p_ll.begin(); it != p_ll.end(); ++it) {
        arr[i] = (*it);
        i++;
    }

    // Now we will put this into the other
    i = n - 1;
    for (auto it = p_ll.begin(); it != p_ll.end(); ++it) {
        (*it) = arr[i];
        i--;
    }
}



#endif