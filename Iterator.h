#pragma once
#ifndef CSITERATOR_H
#define CSITERATOR_H

namespace cslib {
    template<typename T>
    class Iterator {
    public:
        Iterator(T* p_ptr = nullptr);

        Iterator<T>& operator= (const Iterator<T>& p_it);
        bool operator==(const Iterator<T>& p_it);
        bool operator!=(const Iterator<T>& p_it);

        T& operator*();
        T* operator->();

        //virtual Iterator<T>& operator++() = 0;
        //virtual Iterator<T>  operator++(int) = 0;
    protected:
        T* m_ptr;
    };

    template<typename T>
    class ConstIterator {
    public:
        ConstIterator(const T* p_ptr = nullptr);

        ConstIterator<T>& operator= (const ConstIterator<T>& p_it);
        bool operator==(const ConstIterator<T>& p_it);
        bool operator!=(const ConstIterator<T>& p_it);

        const T& operator*();
        const T* operator->();

        //virtual ConstIterator<T>& operator++() = 0;
        //virtual ConstIterator<T>  operator++(int) = 0;
    protected:
        const T* m_ptr;
    };
}







template<typename T>
cslib::Iterator<T>::Iterator(T* p_ptr) : m_ptr(p_ptr) {

}

template<typename T>
cslib::Iterator<T>& cslib::Iterator<T>::operator= (const Iterator<T>& p_it) {
    m_ptr = p_it->m_ptr;
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
cslib::ConstIterator<T>& cslib::ConstIterator<T>::operator= (const ConstIterator<T>& p_it) {
    m_ptr = p_it->m_ptr;
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