/**
 *@file range.hpp
 *@copyright GPL-3.0-or-later
 *@author safocl (megaSafocl)
 *@date 2023
 *
 *@detail \"Copyright safocl (megaSafocl) 2023\"
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

#pragma once

#include "card.hpp"
#include "hand.hpp"
#include "utils.hpp"

#include <iostream>
#include <cmath>
#include <unordered_set>

namespace core::engine {

/*
 * Range should represent a hand set (container) with the weights of every hands.
 *
 * range string for serilize-deserialize has view:
 *		[percent]handRepresentation[/percent]
 *
 *	where a percent is weight and both the values must be are equial, and a
 *	handRepresentation is tring representation of a hand or a hand group
 *	or the list of a hand the list of the hand groups.
 *
 *	if a handRepresentation weight is 100% then a percent must not be specified.
 *
 *	examples:
 *		[50]AsKh, KK[/50], 55, Jh3s
*/

struct RangeNode {
    Hand   hand {};
    double handWeight { 0.0 };
};

inline bool operator==( const RangeNode & lhs, const RangeNode & rhs ) {
    return lhs.hand == rhs.hand;
}

using Range = std::unordered_set< RangeNode >;

std::string to_string( const Range & r );
Range       from_string( std::string_view str );
}   // namespace core::engine

namespace std {
template <> struct hash< core::engine::RangeNode > {
    std::size_t operator()( const core::engine::RangeNode & r ) const noexcept {
        return std::invoke( hash< core::engine::Hand >(), r.hand );
    }
};
}   // namespace std
