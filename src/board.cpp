/**
 *\file board.cpp
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

#include "board.hpp"
#include <stdexcept>
#include <vector>
#include <format>

namespace core::engine {

void Board::setFlop( Card first, Card second, Card third ) {
    if ( s == State::PREFLOP )
        s = State::FLOP;

    b.at( 0 ) = first;
    b.at( 1 ) = second;
    b.at( 2 ) = third;
}

void Board::setTurn( Card c ) {
    if ( s == State::PREFLOP )
        throw std::runtime_error( "Board was not FLOP or TURN" );

    if ( s == State::FLOP )
        s = State::TURN;

    b.at( 3 ) = c;
}

void Board::setRiver( Card c ) {
    if ( s == State::PREFLOP || s == State::FLOP )
        throw std::runtime_error( "Board was not TURN or RIVER" );

    if ( s == State::TURN )
        s = State::RIVER;

    b.at( 4 ) = c;
}

Board::State Board::getStreet() const { return s; }

std::vector< Card > Board::getBoard() const {
    switch ( s ) {
    case State::PREFLOP: throw std::runtime_error( "Logic error -- board is null" );
    case State::FLOP: return std::vector< Card > { b.begin(), b.begin() + 3 };
    case State::TURN: return std::vector< Card > { b.begin(), b.begin() + 4 };
    case State::RIVER: return std::vector< Card > { b.begin(), b.begin() + 5 };
    default: throw std::runtime_error( "Invalid board street" );
    }
}

std::string Board::asStr() const {
    switch ( s ) {
    case State::PREFLOP: throw std::runtime_error( "Logic error -- board is null" );
    case State::FLOP:
        return std::format(
        "[{}] [{}] [{}]", b.at( 0 ).asStr(), b.at( 1 ).asStr(), b.at( 2 ).asStr() );
    case State::TURN:
        return std::format( "[{}] [{}] [{}] [{}]",
                            b.at( 0 ).asStr(),
                            b.at( 1 ).asStr(),
                            b.at( 2 ).asStr(),
                            b.at( 3 ).asStr() );
    case State::RIVER:
        return std::format( "[{}] [{}] [{}] [{}] [{}]",
                            b.at( 0 ).asStr(),
                            b.at( 1 ).asStr(),
                            b.at( 2 ).asStr(),
                            b.at( 3 ).asStr(),
                            b.at( 4 ).asStr() );
    default: throw std::runtime_error( "Invalid board street" );
    }
}
}   // namespace core::engine
