/**
 *@file hand.hpp
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
#include <utility>
#include <functional>

namespace core::engine {
class Hand final {
    std::pair< Card, Card > h;

public:
    Hand() = default;
    Hand( Card, Card );

    bool operator==( const Hand & ) const;
    bool operator<( const Hand & ) const;
    bool operator>( const Hand & ) const;

    Card low() const;
    Card hight() const;
    Card right() const;
    Card left() const;

    std::string asStr() const;

    friend struct HandTraits;
};

struct HandTraits final {
    struct Hash final {
        std::size_t operator()( const Hand & h ) const {
            return std::invoke( CardTraits::Hash(), h.h.first ) +
                   std::invoke( CardTraits::Hash(), h.h.second );
        }
    };

    static bool isPair( const Hand & h );
    static bool isConnector( const Hand & h );
    static bool isGupConnector( const Hand & h );
    static bool is2gupConnector( const Hand & h );
    static bool is3gupConnector( const Hand & h );
    static bool isSingleSuit( const Hand & h );
};
}   // namespace core::engine
