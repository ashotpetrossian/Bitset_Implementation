#include <iostream>
#include "Bitset.h"

// *********Constructors********** //
template<size_t n>
constexpr Bitset<n>::Bitset() noexcept : array() { }

template<size_t n>
constexpr Bitset<n>::Bitset(long val) noexcept 
    :  Bitset() { 
        array[0] = val;
    }

template<size_t n>
Bitset<n>::Bitset(std::string str) : Bitset() {
    if (str.size() > n) {
        throw std::out_of_range("String is bigger then the bites you have\nTerminated\n");
    }
    for (size_t i = 0; i < str.size(); i++)
    {
        size_t index = (str.size() - i) / n;
        size_t pos = str.size() - i - index * bits;
        if ( str[i] == '1' ) {
            set(pos);
        } else if ( str[i] != '1' && str[i] != '0') {
            throw std::invalid_argument("String involves not bit char\nTerminated\n");
        }
    }  
}

// *********CMP operator***********//
template<size_t n>
bool Bitset<n>::operator==(const Bitset<n>& rhs) const noexcept {
    for (size_t i = 0; i < n; i++)
    {
        if (this->operator[](i) != rhs.operator[](i)) { return false; }
    }
    return true;
}

// *********Capacity********** //
template<size_t n>
constexpr size_t Bitset<n>::size() const noexcept {
    return n;
}


// **********Modifiers********** //
template<size_t n>
Bitset<n>& Bitset<n>::set() noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] |= ~zero_bit;
    }    
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::set(size_t position) {
    size_t index = position / bits;
    size_t pos = position - index * bits;
    array[index] |= ( one_bit << pos );
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::reset() noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] &= zero_bit;
    }
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::reset(size_t position) {
    size_t index = position / bits;
    size_t pos = position - index * bits;
    array[index] &= ~( one_bit << pos );
    return *this;
}


template<size_t n>
Bitset<n>& Bitset<n>::flip() noexcept {    
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] = ~(array[i]);
    }
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::flip(size_t position) {
    size_t index = position / n;
    size_t pos = position - index * bits;
    array[index] ^= ( one_bit << pos );
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::operator&=(const Bitset<n>& other) noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] &= other.array[i];
    }
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::operator|=(const Bitset<n>& other) noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] |= other.array[i];
    }
    return *this;
}

template<size_t n>
Bitset<n>& Bitset<n>::operator^=(const Bitset<n>& other) noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] ^= other.array[i];
    }
    return *this;
}

template<size_t n>
Bitset<n> Bitset<n>::operator~() const noexcept {
    Bitset<n> tmp;
    for (size_t i = 0; i < m_size; i++)
    {
        tmp.array[i] = ~array[i];
    }
    return tmp;
}

template<size_t n>
Bitset<n> Bitset<n>::operator<<(size_t position) const noexcept {
    Bitset<n> tmp;
    for (size_t i = 0; i < m_size; i++)
    {
        tmp.array[i] = (array[i] << position);
    }
    return tmp;
}

template<size_t n>
Bitset<n>& Bitset<n>::operator<<=(size_t position) noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] = (array[i] << position);
    }
    return *this;
}

template<size_t n>
Bitset<n> Bitset<n>::operator>>(size_t position) const noexcept {
    Bitset<n> tmp;
    for (size_t i = 0; i < m_size; i++)
    {
        tmp.array[i] = (array[i] >> position);
    }
    return tmp;
}

template<size_t n>
Bitset<n>& Bitset<n>::operator>>=(size_t position) noexcept {
    for (size_t i = 0; i < m_size; i++)
    {
        array[i] = (array[i] >> position);
    }
    return *this;
}

// **********Element access********* //
template<size_t n>
constexpr bool Bitset<n>::operator[](size_t position) const {
    size_t index = position / n;
    size_t pos = position - index * bits;
    return array[index] & (one_bit << pos);
} 

template<size_t n>
bool Bitset<n>::test(size_t position) const {
    if (position >= n) {
        throw std::out_of_range("Trying to access out of range space\nTerminated\n");
        return EXIT_FAILURE;
    } else {
        return this->operator[](position);
    }
}

template<size_t n>
bool Bitset<n>::all() const noexcept {
    for (size_t i = 0; i < n; i++)
    {
        if (this->operator[](i) != one_bit) { return false; }
    }    
    return true;
}

template<size_t n>
bool Bitset<n>::any() const noexcept {
    for (size_t i = 0; i < n; i++)
    {
        if (this->operator[](i) != zero_bit) { return true; }
    }    
    return false;
}

template<size_t n>
bool Bitset<n>::none() const noexcept {
    for (size_t i = 0; i < n; i++)
    {
        if (this->operator[](i) != zero_bit) { return false; }
    }    
    return true;
}

template<size_t n>
size_t Bitset<n>::count() const noexcept {
    size_t _count{0};
    for (size_t i = 0; i < n; i++)
    {
        if (this->operator[](i) == one_bit) { _count++; }
    }    
    return _count;
}