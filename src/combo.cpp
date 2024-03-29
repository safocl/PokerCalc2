/**
 *\file combo.cpp
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

#include "combo.hpp"
#include "board.hpp"
#include <stdexcept>
#include <algorithm>

namespace core::engine {
Combo::Combo( Board b, Hand h ) { set( b, h ); }
void Combo::set( Board b, Hand h ) {
    if ( b.getStreet() != Board::State::FLOP &&
         b.getStreet() != Board::State::TURN &&
         b.getStreet() != Board::State::RIVER )
        throw std::runtime_error( "In Combo::Combo() board is invalid" );

    combo = b.getBoard();
    combo.push_back( h.left() );
    combo.push_back( h.right() );
    std::sort( combo.begin(), combo.end() );
}

const std::vector< Card > & Combo::asSortedVector() const { return combo; }

}   // namespace core::engine
