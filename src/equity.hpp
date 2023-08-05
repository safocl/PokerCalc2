/**
 *@file equity.hpp
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

#include "board.hpp"
#include "hand.hpp"
#include "range.hpp"

namespace core::engine {
class Equity final {
public:
    struct Eq final {
        double hero {}, opp {}, tie {};
    };

private:
    Eq eq;

public:
    void calculate( const Hand & hero, const Hand & opp, const Board & board );

    void calculate( const Range & hero, const Range & opp, const Board & board );

    void calculate( const RangeNode & hero, const Range & opp, const Board & board );

    void calculate( const Range & hero, const RangeNode & opp, const Board & board );

    Eq          getEq() const;
    std::string getEqAsStr() const;
};
}   // namespace core::engine
