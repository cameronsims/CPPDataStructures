/**
 * @file Iterator.h
 * @brief Holds the basic iterator classes, used to traverse data structures.
 **/
#ifndef CSITERATOR_H
#define CSITERATOR_H

namespace cslib {
    /**
     * @class Iterator
     * @tparam T Type of the data structure we're iterating.
     * @brief Way of reading through a data structure.
     **/
    template<typename T>
    class Iterator {
    public:
        /**
         * @param p_ptr The pointer to the current value
         * 
         * @brief Constructs the class
         */
        explicit Iterator(T* p_ptr = nullptr);

        /**
         * @param p_ptr The pointer to the current value
         *
         * @brief Tests if two iterators are equal
         * @return Returns true if they're pointing to the same value.
         */
        bool operator==(const Iterator<T>& p_it);

        /**
         * @param p_ptr The pointer to the current value
         *
         * @brief Tests if two iterators aren't equal
         * @return Returns true if they're not pointing to the same value.
         */
        bool operator!=(const Iterator<T>& p_it);

        /**
         * @brief Deferences the value
         * @return Returns the value pointed
         */
        T& operator*();

        /**
         * @brief Deferences the value
         * @return Returns the value pointed
         */
        T* operator->();

        //virtual Iterator<T>& operator++() = 0;
        //virtual Iterator<T>  operator++(int) = 0;
    protected:
        /// Pointer to the current value
        T* m_ptr;
    };

    /**
     * @class ConstIterator
     * @tparam T Type of the data structure we're iterating.
     * @brief Way of reading through a data structure.
     **/
    template<typename T>
    class ConstIterator {
    public:
        /**
         * @param p_ptr The pointer to the current value
         *
         * @brief Constructs the class
         */
        explicit ConstIterator(const T* p_ptr = nullptr);

        /**
         * @param p_ptr The pointer to the current value
         *
         * @brief Tests if two iterators are equal
         * @return Returns true if they're pointing to the same value.
         */
        bool operator==(const ConstIterator<T>& p_it);

        /**
         * @param p_ptr The pointer to the current value
         *
         * @brief Tests if two iterators aren't equal
         * @return Returns true if they're not pointing to the same value.
         */
        bool operator!=(const ConstIterator<T>& p_it);

        /**
         * @brief Deferences the value
         * @return Returns the value pointed
         */
        const T& operator*();
        
        /**
         * @brief Deferences the value
         * @return Returns the value pointed
         */
        const T* operator->();

        //virtual ConstIterator<T>& operator++() = 0;
        //virtual ConstIterator<T>  operator++(int) = 0;
    protected:
        /// Pointer to the current value
        const T* m_ptr;
    };
}







template<typename T>
cslib::Iterator<T>::Iterator(T* p_ptr) : m_ptr(p_ptr) {

}

template<typename T>
bool cslib::Iterator<T>::operator==(const Iterator<T>& p_it) {
    return (this->m_ptr == p_it.m_ptr);
}

template<typename T>
bool cslib::Iterator<T>::operator!=(const Iterator<T>& p_it) {
    return (this->m_ptr != p_it.m_ptr);
}

template<typename T>
T& cslib::Iterator<T>::operator*() {
    return *(this->m_ptr);
}

template<typename T>
T* cslib::Iterator<T>::operator->() {
    return this->m_ptr;
}



template<typename T>
cslib::ConstIterator<T>::ConstIterator(const T* p_ptr) : m_ptr(p_ptr) {

}

template<typename T>
bool cslib::ConstIterator<T>::operator==(const ConstIterator<T>& p_it) {
    return (this->m_ptr == p_it.m_ptr);
}

template<typename T>
bool cslib::ConstIterator<T>::operator!=(const ConstIterator<T>& p_it) {
    return (this->m_ptr != p_it.m_ptr);
}

template<typename T>
const T& cslib::ConstIterator<T>::operator*() {
    return *(this->m_ptr);
}

template<typename T>
const T* cslib::ConstIterator<T>::operator->() {
    return this->m_ptr;
}


#endif