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
    switch ( v ) {
    case Value::v2: str = "2"; break;
    case Value::v3: str = "3"; break;
    case Value::v4: str = "4"; break;
    case Value::v5: str = "5"; break;
    case Value::v6: str = "6"; break;
    case Value::v7: str = "7"; break;
    case Value::v8: str = "8"; break;
    case Value::v9: str = "9"; break;
    case Value::vT: str = "T"; break;
    case Value::vJ: str = "J"; break;
    case Value::vQ: str = "Q"; break;
    case Value::vK: str = "K"; break;
    case Value::vA: str = "A"; break;
    default:
        throw std::runtime_error(
        "the card::asStr() method is called for a invalid card value" );
    }

    switch ( s ) {
    case Suit::c: str += "c"; break;
    case Suit::h: str += "h"; break;
    case Suit::s: str += "s"; break;
    case Suit::d: str += "d"; break;
    default:
        throw std::runtime_error(
        "the card::asStr() method is called for a invalid card suite" );
    }

    return str;
}   // namespace core::engine

Value Card::getValue() const { return v; }

Suit Card::getSuit() const { return s; }
}   // namespace core::engine
