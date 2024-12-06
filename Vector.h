/**
 * @file Vector.h
 * @brief A dynamic array
 **/

#ifndef CSVECTOR_H
#define CSVECTOR_H

#include "Universal.h"

namespace cslib {
    /**
     * @class Vector
     * @tparam T Type of the data structure.
     * @brief A dynamically allocated array
     **/
    template<class T>
    class Vector {
    public:
        /** 
         * @brief Constructs the vector class
         */
        Vector();

        /**
         * @param p_size The size we're allocating
         * 
         * @brief Constructs the vector class of a size
         */
        explicit Vector(size_t p_size);

        /**
         * @param p_vector The vector we're copying 
         * 
         * @brief Constructs the vector class with an existing vector.
         */
        Vector(const Vector<T>& p_vector);

        /**
         * @param p_vector The vector we're copying
         *
         * @brief Constructs the vector class with an existing vector.
         * @return Returns the vector we just constructed.
         */
        Vector<T>& operator= (const Vector<T>& p_vector);

        /**
         * @brief Deconstructs the Vector
         */
        ~Vector();
    
        /**
         * @brief Gets the size of the size of the vector
         * @return Returns the vector's size
         */
        size_t size() const;

        /**
         * @param p_index The index of the array
         *
         * @brief Gets the value of a value in the array
         * @return Returns the value located in the array
         */
        T& operator[](size_t p_index);

        /**
         * @param p_index The index of the array
         *
         * @brief Gets the value of a value in the array
         * @return Returns the value located in the array
         */
        const T& operator[](size_t p_index) const;

        /**
         * @param p_value The value we're pushing into the vector
         *
         * @brief Add the value to the back of the vector
         * @return Returns the value located in the array
         */
        T& push(const T& p_value);



        class Iterator : public cslib::Iterator<T> {
        public:
            explicit Iterator(T* p_ptr = nullptr);

            Iterator& operator++();
            Iterator  operator++(int);
            Iterator& operator--();
            Iterator  operator--(int);
        };
        class ConstIterator : public cslib::ConstIterator<T> {
        public:
            explicit ConstIterator(const T* p_ptr = nullptr);

            ConstIterator& operator++();
            ConstIterator  operator++(int);
            ConstIterator& operator--();
            ConstIterator  operator--(int);
        };

        /**
         * @brief Gets the iterator
         * @return Returns the iterator to the first
         */
        Iterator begin();

        /**
         * @brief Gets the iterator
         * @return Returns the iterator to the first
         */
        ConstIterator cbegin() const;

        /**
         * @brief Gets the iterator
         * @return Returns the iterator to after the last element
         */
        Iterator end();

        /**
         * @brief Gets the iterator
         * @return Returns the iterator to after the last element
         */
        ConstIterator cend() const;

    private:
        /**
         * @param p_size Resizes the vector
         *
         * @brief Changes the vector size
         */
        void m_resize(size_t p_size);

        /**
         * @param p_array The array we're copying
         * @param p_size The size of the array we're copying
         *
         * @brief Copies an array into the array
         */
        void m_copy(T* p_array, size_t p_size);
    
        /// The internal array 
        T* m_array = nullptr;

        /// The allocated size 
        size_t m_allocatedSize = 0;

        /// The size to the user
        size_t m_size = 0;
    };
}













// Vector Implementation

#define VECTOR_RESIZE_DEFAULT 2*this->size()

template<class T>
cslib::Vector<T>::Vector() {
    m_allocatedSize = 1;
    m_size = 0;
    m_array = new T[m_allocatedSize];
}

template<class T>
cslib::Vector<T>::Vector(size_t p_size) {
    // If invalid size
    if (p_size < 1) {
        throw OutOfRange();
    }
    // Otherwise just make normal values
    m_allocatedSize = p_size;
    m_size = 0;
    
    try {
        m_array = new T[m_allocatedSize];
    } catch (const std::exception&) {
        throw OutOfRange();
    }
}

template<class T>
cslib::Vector<T>::Vector(const Vector<T>& p_vector) {
    // Copy both sizes
    this->m_allocatedSize = p_vector.m_allocatedSize;
    this->m_size = p_vector.m_size;
    // Copy all the data over
    this->copy(p_vector.m_array, p_vector.m_size);
}

template<class T>
cslib::Vector<T>::~Vector() {
    delete[] m_array;
}

template<class T>
size_t cslib::Vector<T>::size() const {
    return this->m_size;
}

template<class T>
T& cslib::Vector<T>::push(const T& p_value) {
    if (this->m_size == this->m_allocatedSize) {
        this->m_resize(VECTOR_RESIZE_DEFAULT);
    }
    // Set a new value at the end
    T& newValue = this->m_array[this->m_size];
    newValue = p_value;

    // Increase the size
    this->m_size++;

    return this->m_array[this->m_size - 1];
}


template<class T>
T& cslib::Vector<T>::operator[](size_t p_index) {
    // Check if the index is lower than 0
    //if (p_index < 0) {
    //    // Throw an exception
    //    throw VectorOutOfRange();
    //}

    // If the index is bigger than the size
    if (this->m_allocatedSize <= p_index) {
        // Resize the vector
        this->m_resize(VECTOR_RESIZE_DEFAULT);
    }
    // If the index is bigger than the user expected size
    if (this->m_size <= p_index) {
        // Change the value of the size to the p_index value
        this->m_size = p_index + 1;
    }
    // Return the specific part of the array
    return this->m_array[p_index];
}

template<class T>
const T& cslib::Vector<T>::operator[](size_t p_index) const {
    // TODO: Check if it is a valid index, if it is THROW AN ERROR
    if (p_index >= this->m_size) {
        // Throw access violation
        throw OutOfRange();
    }

    return this->m_array[p_index];
}

template<class T>
cslib::Vector<T>& cslib::Vector<T>::operator=(const Vector<T>& p_vector) {
    // Get the size of the vector
    this->m_resize(p_vector.m_allocatedSize);
    
    // Deep copy
    this->m_copy(p_vector.m_array, p_vector.m_size);

    // Return self
    return *this;
}

template<class T>
void cslib::Vector<T>::m_resize(size_t p_size) {
    // Create temporary value to store the values in
    T* temp = new T[p_size];

    // Get the smallest size
    const size_t smallerSize = (this->m_allocatedSize < p_size) ? this->m_allocatedSize : p_size;

    // Add values into the array
    for (size_t i = 0; i < smallerSize; i++) {
        // Add into the array
        temp[i] = this->m_array[i];
    }

    // Recreate the array
    this->m_allocatedSize = p_size;

    // If the new size is lower than the user expected size
    if (this->m_size > m_allocatedSize) {
        this->m_size = m_allocatedSize;
    }
    // Redefine the array
    this->m_copy(temp, p_size);

    // Delete temporary values
    delete[] temp;
}


template<class T>
void cslib::Vector<T>::m_copy(T* p_array, size_t p_size) {
    // Redefine the array
    this->m_array = new T[p_size];
    // Save values into the old array location
    for (size_t i = 0; i < p_size; i++) {
        // Add into the array
        this->m_array[i] = p_array[i];
    }
}


template<class T>
cslib::Vector<T>::Iterator::Iterator(T* p_ptr) : cslib::Iterator<T>::Iterator(p_ptr) {

}

template<class T>
typename cslib::Vector<T>::Iterator cslib::Vector<T>::begin() {
    Iterator it = Iterator(this->m_array);
    return it;
}

template<class T>
typename cslib::Vector<T>::ConstIterator cslib::Vector<T>::cbegin() const {
    ConstIterator cit = ConstIterator(this->m_array);
    return cit;
}

template<class T>
typename cslib::Vector<T>::Iterator cslib::Vector<T>::end() {
    T* last = this->m_array + (m_size);// * sizeof(T);
    Iterator it = Iterator(last);
    return it;
}

template<class T>
typename cslib::Vector<T>::ConstIterator cslib::Vector<T>::cend() const {
    const T* last = this->m_array + (m_size);// * sizeof(T);
    ConstIterator cit = ConstIterator(last);
    return cit;
}

template<class T>
typename cslib::Vector<T>::Iterator& cslib::Vector<T>::Iterator::operator++() {
    this->m_ptr++;
    return *this;
}

template<class T>
typename cslib::Vector<T>::Iterator  cslib::Vector<T>::Iterator::operator++(int) {
    Iterator it = Iterator(this->m_ptr + 1);
    this->m_ptr++;
    return it;
}

template<class T>
typename cslib::Vector<T>::Iterator& cslib::Vector<T>::Iterator::operator--() {
    this->m_ptr--;
    return *this;
}

template<class T>
typename cslib::Vector<T>::Iterator  cslib::Vector<T>::Iterator::operator--(int) {
    Iterator it = Iterator(this->m_ptr - 1);
    this->m_ptr--;
    return it;
}

template<class T>
cslib::Vector<T>::ConstIterator::ConstIterator(const T* p_ptr) : cslib::ConstIterator<T>::ConstIterator(p_ptr) {

}

template<class T>
typename cslib::Vector<T>::ConstIterator& cslib::Vector<T>::ConstIterator::operator++() {
    this->m_ptr++;
    return *this;
}

template<class T>
typename cslib::Vector<T>::ConstIterator  cslib::Vector<T>::ConstIterator::operator++(int) {
    ConstIterator it = Iterator(this->m_ptr + 1);
    this->m_ptr++;
    return it;
}

template<class T>
typename cslib::Vector<T>::ConstIterator& cslib::Vector<T>::ConstIterator::operator--() {
    this->m_ptr--;
    return *this;
}

template<class T>
typename cslib::Vector<T>::ConstIterator  cslib::Vector<T>::ConstIterator::operator--(int) {
    ConstIterator it = Iterator(this->m_ptr - 1);
    this->m_ptr--;
    return it;
}




#endif // CSVECTOR_H