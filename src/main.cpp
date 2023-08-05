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
#include "range.hpp"

int main() {
    using namespace core::engine;

    Deck deck;

    auto handsForRanges = std::array {
        Hand( { Value::vK, Suit::s }, { Value::vQ, Suit::d } ),
        Hand( { Value::v4, Suit::s }, { Value::vQ, Suit::s } ),
        Hand( { Value::vK, Suit::s }, { Value::vQ, Suit::h } ),
        Hand( { Value::vK, Suit::s }, { Value::vQ, Suit::c } ),
        Hand( { Value::v3, Suit::d }, { Value::vQ, Suit::d } ),
        Hand( { Value::vK, Suit::d }, { Value::vQ, Suit::s } ),
        Hand( { Value::vK, Suit::d }, { Value::vQ, Suit::h } ),
        Hand( { Value::vK, Suit::d }, { Value::vQ, Suit::c } ),
        Hand( { Value::vK, Suit::h }, { Value::vQ, Suit::d } ),
        Hand( { Value::vK, Suit::h }, { Value::vQ, Suit::s } ),
        Hand( { Value::v3, Suit::h }, { Value::vQ, Suit::h } ),
        Hand( { Value::vK, Suit::h }, { Value::vQ, Suit::c } ),
        Hand( { Value::vK, Suit::c }, { Value::vQ, Suit::d } ),
        Hand( { Value::vK, Suit::c }, { Value::vQ, Suit::s } ),
        Hand( { Value::vK, Suit::c }, { Value::vQ, Suit::h } ),
        Hand( { Value::v8, Suit::c }, { Value::vQ, Suit::c } ),
        Hand( { Value::vQ, Suit::d }, { Value::vT, Suit::d } ),
        Hand( { Value::vQ, Suit::s }, { Value::vT, Suit::s } ),
        Hand( { Value::vQ, Suit::h }, { Value::vT, Suit::h } ),
        Hand( { Value::vQ, Suit::c }, { Value::vT, Suit::c } ),
        Hand( { Value::vT, Suit::d }, { Value::vT, Suit::c } ),
        Hand( { Value::vT, Suit::d }, { Value::vT, Suit::s } ),
        Hand( { Value::vT, Suit::d }, { Value::vT, Suit::h } ),
        Hand( { Value::vT, Suit::s }, { Value::vT, Suit::c } ),
        Hand( { Value::vT, Suit::s }, { Value::vT, Suit::h } ),
        Hand( { Value::vT, Suit::h }, { Value::vT, Suit::c } ),
    };

    Range hero {
        RangeNode { .hand = handsForRanges[ 0 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 1 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 2 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 3 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 4 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 5 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 6 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 7 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 8 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 9 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 10 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 11 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 12 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 13 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 14 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 15 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 16 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 17 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 18 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 19 ], .handWeight = 1.0 },
        RangeNode { .hand = handsForRanges[ 20 ], .handWeight = 0.5 },
        RangeNode { .hand = handsForRanges[ 21 ], .handWeight = 0.5 },
        RangeNode { .hand = handsForRanges[ 22 ], .handWeight = 0.5 },
        RangeNode { .hand = handsForRanges[ 23 ], .handWeight = 0.5 },
        RangeNode { .hand = handsForRanges[ 24 ], .handWeight = 0.5 },
        RangeNode { .hand = handsForRanges[ 25 ], .handWeight = 0.5 },
    };
    std::cout << to_string( hero ) << std::endl;

    /*
    Range opp {
        // RangeNode { .hand = handsForRanges[ 12 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 13 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 14 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 15 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 16 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 17 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 18 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 19 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 20 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 21 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 22 ], .handWeight = 1.0 },
        // RangeNode { .hand = handsForRanges[ 23 ], .handWeight = 1.0 },
        RangeNode { .hand = Hand( { Value::vK, Suit::d }, { Value::vA, Suit::s } ),
                    .handWeight = 1.0 },

    };

    const std::array boardCards = { deck.takeCard( { Value::v8, Suit::d } ),
                                    deck.takeCard( { Value::v9, Suit::s } ),
                                    deck.takeCard( { Value::v7, Suit::h } ),
                                    deck.takeCard( { Value::vQ, Suit::d } ),
                                    deck.takeCard( { Value::vK, Suit::s } ) };

    Board board;

    board.setFlop( boardCards[ 0 ], boardCards[ 1 ], boardCards[ 2 ] );
    board.setTurn( boardCards[ 3 ] );
    board.setRiver( boardCards[ 4 ] );

    Equity eq;
    eq.calculate( hero, opp, board );

    std::cout << std::format(
    "Board {}\nHero range is: [{}]\nOpp range is: [{}]\nEquity is {}\n",
    board.asStr(),
    to_string( hero ),
    to_string( opp ),
    eq.getEqAsStr() );
 */
    return EXIT_SUCCESS;
}
