// Bitset implementation

#ifndef BITSET_H_
#define BITSET_H_

#include <iostream>

template<size_t n>
class Bitset {
private:
    static const unsigned long size_correcter = 1ul;
    static const unsigned long one_bit = 1ul;
    static const unsigned long zero_bit = 0ul;
    static const unsigned long bits = 8ul * sizeof(unsigned long);
    const unsigned long  m_size = n / bits + size_correcter;
    unsigned long array[n / bits + size_correcter];
public: 
    // *********Constructors******** //
    constexpr Bitset() noexcept;
    constexpr Bitset(long) noexcept;
    explicit Bitset(std::string);

    // ********CMP operator*********//
    bool operator==(const Bitset& rhs) const noexcept;

    //********* Capacity ******* //
    constexpr size_t size() const noexcept;

    //******** Modifiers **********//
    Bitset& set() noexcept;
    Bitset& set(size_t);
    Bitset& reset() noexcept;
    Bitset& reset(size_t);
    Bitset& flip() noexcept;
    Bitset& flip(size_t); 

    Bitset& operator&=(const Bitset& other) noexcept;
    Bitset& operator|=(const Bitset& other) noexcept;
    Bitset& operator^=(const Bitset& other) noexcept;
    Bitset operator~() const noexcept;

    Bitset operator<<(size_t) const noexcept;
    Bitset& operator<<=(size_t) noexcept;
    Bitset operator>>(size_t) const noexcept;
    Bitset& operator>>=(size_t) noexcept;

    //********** Element access********//
    constexpr bool operator[](size_t) const;
    bool test(size_t) const;
    bool all() const noexcept;
    bool any() const noexcept;
    bool none() const noexcept;
    size_t count() const noexcept;

    // ***********Non-member functions ********* //
    friend std::ostream& operator<<(std::ostream& os, const Bitset<n>& b)
    {
        for (size_t i = 0; i < n; ++i)
        {
            os << ((b.array[(n - i) / b.bits] >> (n - i - size_correcter)) & 1); 
        }
        return os;
    }
};


#endif