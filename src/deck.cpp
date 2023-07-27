/**
 *\file deck.cpp
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

#include "deck.hpp"
#include "board.hpp"
#include "card.hpp"

#include <cassert>
#include <format>
#include <iostream>
#include <stdexcept>

namespace core::engine {
Deck::Deck() { generate(); }

Deck::~Deck() {}

void Deck::generate() {
    for ( auto card = CardTraits::begin; card != CardTraits::sentinel;
          card      = CardTraits::next( card ) )
        deck.insert_or_assign( card, true );

    assert( deck.size() == 52 && "Invalid cards count" );
}

void Deck::zeroing() {
    for ( auto && deckNode : deck )
        deckNode.second = true;
}

Card Deck::takeCard( Card c ) {
    if ( !isAvaibleCard( c ) )
        throw std::runtime_error(
        std::format( "\nIn Deck::takeCard(Card): card [{}] isn't avaible in a deck.",
                     c.asStr() ) );

    deck.at( c ) = false;
    return c;
}

bool Deck::isAvaibleCard( const Card & c ) const { return deck.at( c ); }
}   // namespace core::engine
