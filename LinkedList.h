/**
 * @file LinkedList.h
 * @brief Holds the LinkedList data structure, nodes held in a line.
 **/
#ifndef CSLINKEDLIST_H
#define CSLINKEDLIST_H

#include "Universal.h"

namespace cslib {
    /**
     * @class LinkedListException
     * @brief Basis for all exceptions thrown by linked list
     **/
    class LinkedListException : public Exception {
    public:
        const char* what() const throw();
    };

    /**
     * @class LinkedListNodeCantCreate
     * @brief Thrown when node can't be created
     **/
    class LinkedListNodeCantCreate : public LinkedListException {
    public:
        const char* what() const throw();
    };

    /**
     * @class LinkedList
     * @tparam T Type of the data structure.
     * @brief A list of values held in a line, insertions/removals can be made quickly.
     **/
    template<typename T>
    class LinkedList {
    public:
        /**
         * @brief Constructs the class
         */
        LinkedList();

        /**
         * @brief Deep copies the LinkedList
         */
        LinkedList(const LinkedList<T>& p_ll);

        /**
         * @brief Deep copies the LinkedList.
         * @return Returns "this" data structure
         */
        LinkedList<T>& operator= (const LinkedList<T>& p_ll);

        /**
         * @brief Destroys the class
         */
        ~LinkedList();

        /**
         * @brief Gets the size of the Linked List
         * @return Returns the size of the linked list, functions like a vector.
         */
        size_t size() const;

        /**
         * @param p_index The index of the node we wish
         * 
         * @brief Gets an index of a value in the linkedlist.
         * @return Returns the value in the correct node.
         */
        T& operator[](size_t p_index);

        /**
         * @param p_index The index of the node we wish
         *
         * @brief Gets an index of a value in the linkedlist.
         * @return Returns the value in the correct node.
         */
        const T& operator[](size_t p_index) const;

        /**
         * @param p_data The data we are adding
         *
         * @brief Adds the value to the far end.
         * @return Returns the value just inserted.
         */
        T&   append(const T& p_data);

        /**
         * @param p_data The data we are adding
         * @param p_index The index we are inserting into.
         *
         * @brief Adds the value to the index given (p_index)
         * @return Returns the value just inserted.
         */
        T&   insert(const T& p_data, size_t p_index);

        /**
         * @param p_left The left hand index
         * @param p_right The right hand index
         *
         * @brief Swaps the two nodes
         */
        void swap  (size_t p_left, size_t p_right);
        
        /**
         * @param p_data The data we are adding
         *
         * @brief Deletes the index given
         * @return Returns the value just removed.
         */
        T remove(size_t p_index);

    protected:
        /**
         * @structure Node
         * @brief The node of some sort of data
         **/
        struct Node {
            /// Actual data.
            T data;
            /// The next node.
            Node* next;
        };

        /**
         * @param p_ll The linked list to copy into "this"
         *
         * @brief Copies the right hand into this data structure.
         */
        void m_copy(const LinkedList<T>& p_ll);

        /**
         * @param p_data The data we're copying
         *
         * @brief Creates the node
         * @return Returns the new node
         */
        Node* m_create(const T& p_data);

        /**
         * @param p_index The index we are retrieving
         *
         * @brief Gets the pointer of the node at the location.
         * @return Returns a pointer to the node
         */
        Node* m_at(size_t p_index);

        /**
         * @param p_index The index we are retrieving
         *
         * @brief Gets the pointer of the node at the location.
         * @return Returns a pointer to the node
         */
        const Node* m_at(size_t p_index) const;

        /// The front of the LinkedList
        Node* m_data;
        
        /// The last of the LinkedList
        Node* m_last;
    public:
        /**
         * @class Iterator
         * @brief The iterator for a linkedlist type structure.
         **/
        class Iterator : public cslib::Iterator<LinkedList<T>::Node> {
        public:
            /**
             * @param p_ptr The pointer of the Iterator
             *
             * @brief Constructs the Iterator
             */
            Iterator(LinkedList<T>::Node* p_ptr);

            /**
             * @brief Gets the last iterator
             * @return Returns the value that was next
             */
            Iterator& operator++();

            /**
             * @brief Gets the last iterator
             * @return Returns the value that was next
             */
            Iterator  operator++(int);

            /**
             * @brief Gets the value at the location
             * @return Gets the value that this iterator represents
             */
            T& operator* ();

            /**
             * @brief Gets the value at the location
             * @return Gets the value that this iterator represents
             */
            T* operator->();
        };

        /**
         * @class ConstIterator
         * @brief The iterator for a linkedlist type structure.
         **/
        class ConstIterator : public cslib::ConstIterator<LinkedList<T>::Node> {
        public:
            /**
             * @param p_ptr The pointer of the Const Iterator 
             * 
             * @brief Constructs the Iterator
             */
            ConstIterator(const LinkedList<T>::Node* p_ptr);

            /**
             * @brief Gets the next iterator
             * @return Returns the value that was next
             */
            ConstIterator& operator++();

            /**
             * @brief Gets the last iterator
             * @return Returns the value that was next
             */
            ConstIterator  operator++(int);

            /**
             * @brief Gets the value at the location
             * @return Gets the value that this iterator represents 
             */
            const T& operator* ();

            /**
             * @brief Gets the value at the location
             * @return Gets the value that this iterator represents
             */
            const T* operator->();
        };

        /**
         * @brief Gets the iterator to the front of the data structure.
         * @return Returns a iterator to the node
         */
        Iterator begin();

        /**
         * @brief Gets the iterator to the front of the data structure.
         * @return Returns a iterator to the node
         */
        ConstIterator cbegin() const;

        /**
         * @brief Gets the iterator to the value after the back of the data structure.
         * @return Returns a iterator to the node
         */
        Iterator end();

        /**
         * @brief Gets the iterator to the value after the back of the data structure.
         * @return Returns a iterator to the node
         */
        ConstIterator cend() const;
    };

    /**
     * @fn LinkedList_reverse
     * @tparam T The type of the structure
     * @param p_ll LinkedList structure
     * 
     * @brief Reverses the data structure.
     */

    template<typename T>
    void LinkedList_reverse(LinkedList<T>& p_ll);

    /**
     * @fn LinkedList_contains
     * @tparam T The type of the structure
     * @param p_ll LinkedList structure
     * @param p_data The data we're looking for
     *
     * @brief Checks the LinkedList for a data
     * @return True if the linked list contains the said data
     */
    template<typename T>
    bool LinkedList_contains(const LinkedList<T>& p_ll, const T& p_data);
}

template<typename T>
cslib::LinkedList<T>::LinkedList() : m_data(nullptr), m_last(nullptr) {

}

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
    size_t i = 1;

    // Until we are the end 
    Node* node = this->m_data;
    while (node->next != nullptr) {
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
    Node* node = this->m_create(p_data);
    
    // If there is nothing
    if (this->m_data == nullptr) {
        this->m_data = node;
        this->m_last = node;
    }

    // Set this value to the last
    else {
        this->m_last->next = node;
        this->m_last = this->m_last->next;
    }
    
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

    Node* node = this->m_create(p_data);

    // If we want to insert at the start
    if (p_index == 0) {
        // Get current start
        Node* next = this->m_data;
        node->next = next;

        // If the data is nullptr
        if (this->m_data == nullptr) {
            this->m_last = next;
        }
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
T cslib::LinkedList<T>::remove(size_t p_index) {
    // Check fi we're empty
    if (this->m_data == nullptr) {
        throw OutOfRange();
    }

    // If we're removing the first...
    if (p_index == 0) {
        // Delete the first node and replace it with the one after.
        Node* delNode = this->m_data;
        Node* aftNode = nullptr;
        if (delNode->next != nullptr) {
            aftNode = delNode->next;
        }

        T temp = delNode->data;
        delete delNode;

        this->m_data = aftNode;

        return temp;
    }
    
    // Loop until we get a good node
    Node* last = this->m_data;
    Node* node = this->m_data;
    size_t i = 0;
    while (i < p_index) {
        last = node;
        node = node->next;

        if (node == nullptr) {
            throw OutOfRange();
        }

        i++;
    }

    Node* after = node->next;
    T temp = node->data;
    delete node;
    
    if (after == nullptr) {
        this->m_last = last;
        last->next = nullptr;
        return temp;
    }
    
    last->next = after;
    return temp;
}

template<typename T>
void cslib::LinkedList<T>::m_copy(const LinkedList<T>& p_ll) {
    // Get size of the other
    size_t n = p_ll.size();

    // If nothing
    if (n == 0) {
        this->m_data = nullptr;
        this->m_last = nullptr;
        return;
    }

    // Add to the values
    Node* node = p_ll.m_data;

    // These are going to be added to "this"
    Node* last = nullptr;
    Node* next = nullptr;

    for (LinkedList<T>::ConstIterator it = p_ll.cbegin(); it != p_ll.cend(); ++it) {
        // Create new element 
        next = this->m_create(*it);

        // Do we have data?
        if (this->m_data == nullptr) {
            // If not, add next to this new data
            this->m_data = next;
            this->m_last = next;
        } else {
            last->next = next;
        }

        // Make next 
        node = node->next;
        last = next;
    }
    
    this->m_last = next;
}

template<typename T>
typename cslib::LinkedList<T>::Node* cslib::LinkedList<T>::m_create(const T& p_data) {
    // Creates a new node 
    try {
        Node* node = new Node();
        node->data = p_data;
        node->next = nullptr;
        return node;
    } catch (std::exception&) {
        throw LinkedListNodeCantCreate();
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
    Iterator it(this->m_data);
    return it;
}

template<typename T>
typename cslib::LinkedList<T>::ConstIterator cslib::LinkedList<T>::cbegin() const {
    ConstIterator it(this->m_data);
    return it;
}

template<typename T>
typename cslib::LinkedList<T>::Iterator cslib::LinkedList<T>::end() {
    Iterator it(nullptr);
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

template<typename T>
bool cslib::LinkedList_contains(const LinkedList<T>& p_ll, const T& p_data) {
    // Iterator 
    typedef LinkedList<T>::ConstIterator LLConstIterator;
    for (LLConstIterator it = p_ll.cbegin(); it != p_ll.cend(); ++it) {
        // If we found it
        if (*it == p_data) {
            return true;
        }
    }

    return false;
}


#endif