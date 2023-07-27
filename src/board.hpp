/**
 *@file board.hpp
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

#include <string>
#include <vector>
#include "card.hpp"

namespace core::engine {

class Board final {
public:
    enum class State { PREFLOP, FLOP, TURN, RIVER };

private:
    std::vector< Card > b { 5 };
    State               s { State::PREFLOP };

public:
    void                setFlop( Card, Card, Card );
    void                setTurn( Card );
    void                setRiver( Card );
    State               getStreet() const;
    std::vector< Card > getBoard() const;
    std::string         asStr() const;
};
}   // namespace core::engine
