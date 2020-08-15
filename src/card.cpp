#include <iostream>
#include <string>
#include <string_view>
#include "card.hpp"

Card::Card( Value v, Suit s ) : v { v }, s { s } {}

void Card::print() const { std::cout << asStr().data() << std::endl; }

bool Card::operator==( const Card & c ) const {
    return eqValue( c ) && eqSuit( c );
}

bool Card::operator<( const Card & c ) const { return v < c.v; }

bool Card::operator>( const Card & c ) const { return v > c.v; }
Card Card::operator++() {
    if ( v == Value::vA )
        return Card( *this );
    auto tmp  = v;
    auto intv = static_cast< int >( v ) + 1;
    v         = static_cast< Value >( intv );
    return Card( tmp, s );
}
Card Card::operator++( int ) {
    if ( v == Value::vA )
        return Card( *this );
    auto intv = static_cast< int >( v ) + 1;
    v         = static_cast< Value >( intv );
    return Card( *this );
}
Card Card::operator--() {
    if ( v == Value::v2 )
        return Card( *this );
    auto tmp  = v;
    auto intv = static_cast< int >( v ) - 1;
    v         = static_cast< Value >( intv );
    return Card( tmp, s );
}
Card Card::operator--( int ) {
    if ( v == Value::v2 )
        return Card( *this );
    auto intv = static_cast< int >( v ) - 1;
    v         = static_cast< Value >( intv );
    return Card( *this );
}

bool Card::eqValue( const Card & c ) const { return v == c.v; }

bool Card::eqSuit( const Card & c ) const { return s == c.s; }

std::string_view Card::asStr() const {
    std::string str;
    switch ( v ) {
    case Value::v2: str = '2'; break;
    case Value::v3: str = '3'; break;
    case Value::v4: str = '4'; break;
    case Value::v5: str = '5'; break;
    case Value::v6: str = '6'; break;
    case Value::v7: str = '7'; break;
    case Value::v8: str = '8'; break;
    case Value::v9: str = '9'; break;
    case Value::vT: str = 'T'; break;
    case Value::vJ: str = 'J'; break;
    case Value::vQ: str = 'Q'; break;
    case Value::vK: str = 'K'; break;
    case Value::vA: str = 'A'; break;
    }
    switch ( s ) {
    case Suit::c: str += 'c'; break;
    case Suit::h: str += 'h'; break;
    case Suit::s: str += 's'; break;
    case Suit::d: str += 'd'; break;
    }
    return std::string_view { str };
}
