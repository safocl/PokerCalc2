#pragma once

#include <bits/stdint-intn.h>
#include <string_view>

namespace core::engine {

enum class Suit : int8_t {
    UNINITIALIZE = 0,
    d            = 1,
    s            = 2,
    c            = 3,
    h            = 4
};

enum class Value : int16_t {
    UNINITIALIZE = 0,
    v2           = 1 << 1,
    v3           = 1 << 2,
    v4           = 1 << 3,
    v5           = 1 << 4,
    v6           = 1 << 5,
    v7           = 1 << 6,
    v8           = 1 << 7,
    v9           = 1 << 8,
    vT           = 1 << 9,
    vJ           = 1 << 10,
    vQ           = 1 << 11,
    vK           = 1 << 12,
    vA           = 1 << 13
};

class Card final {
    Value v;
    Suit  s;

public:
    Card();
    Card( Value, Suit );
    //    Card(const Card &) = delete;
    void        print() const;
    bool        operator==( const Card & ) const;
    bool        operator<( const Card & ) const;
    bool        operator>( const Card & ) const;
    Card        operator++();
    Card        operator++( int );
    Card        operator--();
    Card        operator--( int );
    bool        eqValue( const Card & ) const;
    bool        eqSuit( const Card & ) const;
    std::string asStr() const;

    static constexpr int VALUE_MIN = static_cast< int >( Value::v2 );
    static constexpr int VALUE_MAX = static_cast< int >( Value::vA );
    static constexpr int SUIT_MIN  = static_cast< int >( Suit::d );
    static constexpr int SUIT_MAX  = static_cast< int >( Suit::h );
};
}   // namespace core::engine
