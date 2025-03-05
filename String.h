#ifndef CSSTRING_H
#define CSSTRING_H

#include "Universal.h"
#include <wchar.h>

namespace cslib {
    template<typename T>
    class StringBasic {
    public:
    
        StringBasic();
        StringBasic(const StringBasic<T>& p_str);
        StringBasic(const T* const p_str);
        explicit StringBasic(size_t p_size);
        
        StringBasic<T>& operator= (const StringBasic<T>& p_str);
        ~StringBasic();
        
              T& operator[](size_t p_index);
        const T& operator[](size_t p_index) const;
        size_t size() const;
        
        StringBasic<T> substring(size_t p_begin, size_t p_end) const;
        
    private:    
        void m_copy      (const T* const p_str, size_t p_size);
        void m_allocate  (size_t p_chars); 
        bool m_isInBounds(size_t p_index) const;
        static size_t m_getSize(const T* const p_str);
    
        T* m_data;
        size_t m_size;
    };
    
    
    
    typedef StringBasic<char> String;
    typedef StringBasic<wchar_t> WString;
}

template<typename T>
cslib::StringBasic<T>::StringBasic() : m_data(nullptr), m_size(0) {
    
}

template<typename T>
cslib::StringBasic<T>::StringBasic(const cslib::StringBasic<T>& p_str) {
    this->m_copy(p_str.m_data, p_str.size());
}

template<typename T>
cslib::StringBasic<T>::StringBasic(const T* const p_str) {
    const size_t size = StringBasic<T>::m_getSize(p_str);
    this->m_copy(p_str, size);
}

template<typename T>
cslib::StringBasic<T>::StringBasic(size_t p_size) {
    this->m_allocate(p_size);
}

template<typename T>
cslib::StringBasic<T>& cslib::StringBasic<T>::operator= (const cslib::StringBasic<T>& p_str) {
    this->m_copy(p_str.m_data, p_str.m_size);
    return *this;
}

template<typename T>
cslib::StringBasic<T>::~StringBasic() {
    delete this->m_data;
    this->m_data = nullptr;
    this->m_size = 0;
}

template<typename T>
T& cslib::StringBasic<T>::operator[](size_t p_index) {
    if (!this->m_isInBounds(p_index)) {
        throw cslib::OutOfRange();    
    }
    return this->m_data[p_index];
}

template<typename T>
const T& cslib::StringBasic<T>::operator[](size_t p_index) const {
    if (!this->m_isInBounds(p_index)) {
        throw cslib::OutOfRange();    
    }
    return this->m_data[p_index];
}

template<typename T>
size_t cslib::StringBasic<T>::size() const {
    return this->m_size;    
}

template<typename T>
cslib::StringBasic<T> cslib::StringBasic<T>::substring(size_t p_begin, size_t p_end) const {
    if (!this->m_isInBounds(p_begin) || !this->m_isInBounds(p_end)) {
        throw cslib::OutOfRange();   
    }
    if (p_begin == p_end) {
        return cslib::StringBasic<T>();    
    }
    
    const bool BACKWARDS = (p_begin > p_end);
    const size_t BIGGEST = (BACKWARDS)  ? p_begin : p_end;
    const size_t SMALLEST = (BACKWARDS) ? p_end   : p_begin;
    const size_t DIFFERENCE = BIGGEST - SMALLEST;
    cslib::StringBasic<T> substr(DIFFERENCE);
    
    size_t i = p_begin;
    size_t j = 0;
    while (j <= DIFFERENCE) {
        substr.m_data[j] = this->m_data[i];
        
        i = (BACKWARDS) ? (i - 1) : (i + 1);
        j++;
    }
    
    return substr;
}

template<typename T>
void cslib::StringBasic<T>::m_copy(const T* const p_str, size_t p_size) {
    this->m_allocate(p_size);
    
    size_t i = 0;
    for (i = 0; i < p_size; i++) {
        this->m_data[i] = p_str[i];    
    }
    this->m_data[i] = 0;
}

template<typename T>
void cslib::StringBasic<T>::m_allocate  (size_t p_chars) {
    if (!this->m_data || this->m_size > 0) {
        delete this->m_data;
        this->m_size = 0;
    }
    
    this->m_data = new T[p_chars + 1];
    this->m_data[p_chars] = 0;
    this->m_size = p_chars + 1;
}

template<typename T>
size_t cslib::StringBasic<T>::m_getSize(const T* const p_str) {
    size_t i = 0; 
    while (p_str[++i] != 0);
    return i;
}

template<typename T>
bool cslib::StringBasic<T>::m_isInBounds(size_t p_index) const {
    std::cout << (this->m_data != nullptr) << (this->m_size > p_index)<< "\n";
    return (this->m_data != nullptr && this->m_size > p_index);
}

#endif
