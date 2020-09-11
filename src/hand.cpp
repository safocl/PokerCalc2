#include "hand.hpp"
#include <cassert>

namespace core::engine{
Hand::Hand( Card l, Card r ) : h { l, r } {
    assert( l != r && "Cards is equial" );
}
bool Hand::operator==( const Hand & o ) const {
    return ( h.first == o.h.first && h.second == o.h.second ) ||
           ( h.first == o.h.second && h.second == o.h.first );
}
bool Hand::operator<( const Hand & o ) const {
    if ( hight().eqValue( o.hight() ) )
        return low() < o.low();
    return hight() < o.hight();
}
bool Hand::operator>( const Hand & o ) const {
    if ( hight().eqValue( o.hight() ) )
        return low() > o.low();
    return hight() > o.hight();
}
Card Hand::low() const {
    return h.first > h.second ? h.second : h.first;
}
Card Hand::hight() const {
    return h.first < h.second ? h.second : h.first;
}
Card Hand::right() const { return h.second; }
Card Hand::left() const { return h.first; }

HandTraits::HandTraits( const Hand & o ) : h( o ) {}
bool HandTraits::isPair() const {
    return h.hight().eqValue( h.low() );
}
bool HandTraits::isConnector() const {
    Card hi { --h.hight() };
    return h.low() == hi;
}
bool HandTraits::isGupConnector() const {
    Card hi { --h.hight() };
    return h.low() == --hi;
}
bool HandTraits::is2gupConnector() const {
    Card hi { --h.hight() };
    --hi;
    return h.low() == --hi;
}
bool HandTraits::is3gupConnector() const {
    Card hi { --h.hight() };
    --hi;
    --hi;
    return h.low() == --hi;
}
bool HandTraits::isSingleSuit() const {
    if ( isPair() )
        return false;
    return h.hight().eqSuit( h.low() );
}
}
