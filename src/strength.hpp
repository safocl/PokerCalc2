/**
 *@file strength.hpp
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

#include "combo.hpp"
#include "board.hpp"
#include "hand.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <optional>
#include <cstdint>

namespace core::engine {

class Strength final {
public:
    /// @brief The hand strength with bitmask support.
    /// It have one main hand strangth (from hi card to strait flush)
    /// and zero or more draw combos.
    ///
    /// In the Texas Holdem Poker a strength sort is (from hi to low):
    ///		Strait Flash \> Four of a kind \> Full House \>
    ///		Flush \> Strait \> Set \> Two Pairs \> Pair \> Hi card.
    enum class Strengthes : u16 {
        HI           = 1,
        PAIR         = ( 1 << 1 ),
        TWO_PAIRS    = ( 1 << 2 ),
        SET          = ( 1 << 3 ),
        STRAIT       = ( 1 << 4 ),
        FLUSH        = ( 1 << 5 ),
        FULL_HOUSE   = ( 1 << 6 ),
        CARE         = ( 1 << 7 ),
        STRAIT_FLUSH = ( 1 << 8 ),
        ONE_OC       = ( 1 << 9 ),
        TWO_OC       = ( 1 << 10 ),
        FD           = ( 1 << 11 ),
        SD           = ( 1 << 12 ),
        GUT_SHOT     = ( 1 << 13 ),

        COMPLITED_HAND_MASK = HI | PAIR | TWO_PAIRS | SET | STRAIT | FLUSH |
                              FULL_HOUSE | CARE | STRAIT_FLUSH,

        DRAW_HAND_MASK = ONE_OC | TWO_OC | FD | SD | GUT_SHOT
    };

    using enum Strengthes;

    struct SignificationCards {
        std::optional< Card > hi, low;
    };

    struct Result {
        Strengthes         value;
        SignificationCards significationCard;
    };

private:
    Strengthes         mCurrentStrength {};
    SignificationCards mSignificationCard {};

public:
    Result      getStrength() const;
    Result      calc( const Board &, const Hand & );
    std::string asStr() const;
};

std::string to_string( Strength::Strengthes );

inline auto operator&( Strength::Strengthes lhs, Strength::Strengthes rhs )
-> decltype( to_underlying( lhs ) ) {
    return to_underlying( lhs ) & to_underlying( rhs );
}
}   // namespace core::engine
