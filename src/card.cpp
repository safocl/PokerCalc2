/**
 *\file card.cpp
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

#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include "card.hpp"

namespace core::engine {
// Card::Card() = default;

void Card::print() const { std::cout << asStr().data() << std::endl; }

std::string Card::asStr() const {
    std::string str;

    str = to_string( v );

    str += to_string( s );

    return str;
}   // namespace core::engine

Value Card::getValue() const { return v; }

Suit Card::getSuit() const { return s; }
}   // namespace core::engine
