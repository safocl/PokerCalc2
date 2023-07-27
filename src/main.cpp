/**
 *\file main.cpp
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

#include <array>
#include <format>
#include <iostream>
#include <cstdlib>
#include <ostream>
#include <cassert>

#include "board.hpp"
#include "equity.hpp"
#include "hand.hpp"
#include "deck.hpp"
#include "card.hpp"
#include "strength.hpp"

int main() {
    using namespace core::engine;

    Deck deck;

    //#include "unittests/card"
    constexpr Card c8c { Value::v7, Suit::c };
    constexpr Card cAd { Value::v7, Suit::d };
    Hand           hero { deck.takeCard( c8c ), deck.takeCard( cAd ) };

    Hand opp { deck.takeCard( { Value::v2, Suit::h } ),
               deck.takeCard( { Value::v6, Suit::s } ) };

    const std::array cards = { deck.takeCard( { Value::v8, Suit::d } ),
                               deck.takeCard( { Value::v9, Suit::s } ),
                               deck.takeCard( { Value::v7, Suit::h } ),
                               deck.takeCard( { Value::vQ, Suit::d } ),
                               deck.takeCard( { Value::vK, Suit::s } ) };

    Board board;

    board.setFlop( cards[ 0 ], cards[ 1 ], cards[ 2 ] );
    board.setTurn( cards[ 3 ] );
    board.setRiver( cards[ 4 ] );

    Equity eq;
    eq.calculate( hero, opp, board );

    std::cout << std::format(
    "Board {}\nHero: {}\tstrength is {}\nOpp: {}\tstrength is {}\nEquity is {}\n",
    board.asStr(),
    hero.asStr(),
    to_string( Strength().calc( board, hero ).value ),
    opp.asStr(),
    to_string( Strength().calc( board, opp ).value ),
    eq.getEqAsStr() );

    return EXIT_SUCCESS;
}
