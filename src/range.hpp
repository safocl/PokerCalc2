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

#include "hand.hpp"

#include <unordered_set>

namespace core::engine {

/*
 * Range should represent a hand set (container) with the weights of every hands.
*/

struct RangeNode {
    Hand   hand {};
    double handWeight { 0.0 };
};

struct RangeNodeTraits {
    struct Hash {
        std::size_t operator()( const RangeNode & r ) const noexcept {
            return std::invoke( HandTraits::Hash {}, r.hand );
        }
    };
};

using Range = std::unordered_set< RangeNode, RangeNodeTraits::Hash >;
}   // namespace core::engine
