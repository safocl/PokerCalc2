/**
 *@file utils.hpp
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

#include <iterator>
#include <type_traits>
#include <ranges>
#include <algorithm>
#include <utility>
#include <vector>

using std::to_underlying;

namespace core {
// template < class Enum >
// constexpr std::underlying_type_t< Enum > to_underlying( Enum e ) noexcept {
//     return static_cast< std::underlying_type_t< Enum > >( e );
// }

/*
 * @brief Algorithm returns range of the R1 constant iterators
 * which points to all matching elements with R2 range or std::nullopt.
 */
template < std::ranges::input_range R1, std::ranges::forward_range R2 >
constexpr std::vector< typename std::decay_t< R1 >::const_iterator >
find_all( R1 && r, R2 && patterns ) {
    using resultItType = typename std::decay_t< R1 >::const_iterator;

    std::vector< resultItType > matchedElements;

    // auto resView = std::ranges::views::filter( r, [ &patterns ]( auto && el ) {
    //     return std::ranges::any_of(
    //     patterns, [ &el1 = el ]( auto && el2 ) { return el1 == el2; } );
    // } );
    //
    // for ( auto it = resView.begin(); it != resView.end(); ++it )
    //     matchedElements.push_back( it );

    /*
	 * general cycle
	 */
    // for ( const auto & matchHand : patterns ) {
    //     matchedElements.push_back( r.find( matchHand ) );
    //
    //     if ( matchedElements.back() == r.end() )
    //         break;
    // }

    auto isAllMatched =
    std::ranges::all_of( patterns, [ &matchedElements, &r ]( auto && el ) {
        auto findedIt = r.find( el );
        if ( findedIt == r.end() )
            return false;

        matchedElements.push_back( findedIt );

        return true;
    } );

    return isAllMatched ? std::move( matchedElements )
                        : std::vector< resultItType >();
}

}   // namespace core
