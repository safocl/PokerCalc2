/**
 *\file hand.cpp
 *\copyright GPL-3.0-or-later
 *\author safocl (megaSafocl)
 *\date 2023
 *
 * \detail \"Copyright safocl (megaSafocl) 2023\"
 This file is part of PokerCalc2.

 PokerCalc2 is free software: you can redistribute it and/or modify it under
 the terms of the GNU General Public License as published by the Free Software
 Foundation, either version 3 of the License, or any later version.

 PokerCalc2 is distributed in the hope that it will be useful, but
 WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 more details.

 You should have received a copy of the GNU General Public License along with
 PokerCalc2. If not, see <https://www.gnu.org/licenses/>.
 */

#include "hand.hpp"
#include "card.hpp"
#include <cassert>

namespace core::engine {
Hand::Hand( Card l, Card r ) : h { l, r } { assert( l != r && "Cards is equial" ); }

bool Hand::operator==( const Hand & o ) const {
    return ( h.first == o.h.first && h.second == o.h.second ) &&
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

Card Hand::low() const { return h.first > h.second ? h.second : h.first; }

Card Hand::hight() const { return h.first < h.second ? h.second : h.first; }

Card Hand::right() const { return h.second; }

Card Hand::left() const { return h.first; }

std::string Hand::asStr() const { return { left().asStr() + right().asStr() }; }

bool HandTraits::isPair( const Hand & h ) { return h.hight().eqValue( h.low() ); }

bool HandTraits::isConnector( const Hand & h ) {
    return h.low() == CardTraits::prevValue( h.hight() );
}

bool HandTraits::isGupConnector( const Hand & h ) {
    return h.low() == CardTraits::prevValue( CardTraits::prevValue( h.hight() ) );
}

bool HandTraits::is2gupConnector( const Hand & h ) {
    return h.low() == CardTraits::prevValue(
                      CardTraits::prevValue( CardTraits::prevValue( h.hight() ) ) );
}

bool HandTraits::is3gupConnector( const Hand & h ) {
    return h.low() ==
           CardTraits::prevValue( CardTraits::prevValue(
           CardTraits::prevValue( CardTraits::prevValue( h.hight() ) ) ) );
}

bool HandTraits::isSingleSuit( const Hand & h ) {
    if ( isPair( h ) )
        return false;
    return h.hight().eqSuit( h.low() );
}

}   // namespace core::engine
