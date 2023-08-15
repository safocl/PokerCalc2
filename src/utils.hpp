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

#include <concepts>
#include <iterator>
#include <ranges>
#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>

using std::to_underlying;

namespace core {
// template < class Enum >
// constexpr std::underlying_type_t< Enum > to_underlying( Enum e ) noexcept {
//     return static_cast< std::underlying_type_t< Enum > >( e );
// }

template < class R, class U >
concept hasFindMethod = requires( R r, U u ) { r.find( u ); };

/*
 * @brief Algorithm returns range of the R1 constant iterators
 * which points to all matching elements with R2 range or std::nullopt.
 */
template < std::ranges::forward_range R1, std::ranges::input_range R2 >
    requires std::equality_comparable_with< std::ranges::range_value_t< R1 >,
                                            std::ranges::range_value_t< R2 > >
constexpr std::vector< std::ranges::iterator_t< R1 > > find_all( R1 && r,
                                                                 R2 && patterns ) {
    using resultItType = std::ranges::iterator_t< R1 >;

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

    auto isAllMatched = std::ranges::all_of(
    patterns, [ &matchedElements, &r ]( [[maybe_unused]] auto && el ) {
        resultItType findedIt;

        if constexpr ( requires { r.find( el ); }
                       /* hasFindMethod< R1, decltype( el ) > */ )
            findedIt = r.find( el );
        else
            findedIt = std::ranges::find( r, el );

        if ( findedIt == std::ranges::end( r ) )
            return false;

        matchedElements.push_back( findedIt );

        return true;
    } );

    return isAllMatched ? std::move( matchedElements )
                        : std::vector< resultItType >();
}

}   // namespace core
