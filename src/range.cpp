/**
 *\file range.cpp
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

#include <array>
#include <cmath>
#include <cstddef>
#include <format>
#include <optional>
#include <ranges>
#include <string>

#include "range.hpp"

namespace core::engine {

constexpr std::size_t forAllArraySize     = 16;
constexpr std::size_t forSuitArraySize    = 4;
constexpr std::size_t forOffsuitArraySize = 12;
constexpr std::size_t forPairArraySize    = 6;

using ArrayForAll     = std::array< Hand, forAllArraySize >;
using ArrayForSuit    = std::array< Hand, forSuitArraySize >;
using ArrayForOffsuit = std::array< Hand, forOffsuitArraySize >;
using ArrayForPair    = std::array< Hand, forPairArraySize >;

namespace {
inline ArrayForAll patternArrayForAll( Value lhs, Value rhs ) {
    return ArrayForAll { Hand( { lhs, Suit::s }, { rhs, Suit::d } ),
                         Hand( { lhs, Suit::s }, { rhs, Suit::s } ),
                         Hand( { lhs, Suit::s }, { rhs, Suit::h } ),
                         Hand( { lhs, Suit::s }, { rhs, Suit::c } ),
                         Hand( { lhs, Suit::d }, { rhs, Suit::d } ),
                         Hand( { lhs, Suit::d }, { rhs, Suit::s } ),
                         Hand( { lhs, Suit::d }, { rhs, Suit::h } ),
                         Hand( { lhs, Suit::d }, { rhs, Suit::c } ),
                         Hand( { lhs, Suit::h }, { rhs, Suit::d } ),
                         Hand( { lhs, Suit::h }, { rhs, Suit::s } ),
                         Hand( { lhs, Suit::h }, { rhs, Suit::h } ),
                         Hand( { lhs, Suit::h }, { rhs, Suit::c } ),
                         Hand( { lhs, Suit::c }, { rhs, Suit::d } ),
                         Hand( { lhs, Suit::c }, { rhs, Suit::s } ),
                         Hand( { lhs, Suit::c }, { rhs, Suit::h } ),
                         Hand( { lhs, Suit::c }, { rhs, Suit::c } ) };
}

[[maybe_unused]] inline ArrayForSuit patternArrayForSuit( Value lhs, Value rhs ) {
    return ArrayForSuit { Hand( { lhs, Suit::d }, { rhs, Suit::d } ),
                          Hand( { lhs, Suit::s }, { rhs, Suit::s } ),
                          Hand( { lhs, Suit::h }, { rhs, Suit::h } ),
                          Hand( { lhs, Suit::c }, { rhs, Suit::c } ) };
}

[[maybe_unused]] inline ArrayForOffsuit patternArrayForOffsuit( Value lhs,
                                                                Value rhs ) {
    return ArrayForOffsuit { Hand( { lhs, Suit::s }, { rhs, Suit::d } ),
                             Hand( { lhs, Suit::s }, { rhs, Suit::h } ),
                             Hand( { lhs, Suit::s }, { rhs, Suit::c } ),
                             Hand( { lhs, Suit::d }, { rhs, Suit::s } ),
                             Hand( { lhs, Suit::d }, { rhs, Suit::h } ),
                             Hand( { lhs, Suit::d }, { rhs, Suit::c } ),
                             Hand( { lhs, Suit::h }, { rhs, Suit::d } ),
                             Hand( { lhs, Suit::h }, { rhs, Suit::s } ),
                             Hand( { lhs, Suit::h }, { rhs, Suit::c } ),
                             Hand( { lhs, Suit::c }, { rhs, Suit::d } ),
                             Hand( { lhs, Suit::c }, { rhs, Suit::s } ),
                             Hand( { lhs, Suit::c }, { rhs, Suit::h } ) };
}

[[maybe_unused]] inline ArrayForPair patternArrayForPairs( Value v ) {
    return ArrayForPair {
        Hand( { v, Suit::s }, { v, Suit::d } ),
        Hand( { v, Suit::s }, { v, Suit::h } ),
        Hand( { v, Suit::s }, { v, Suit::c } ),
        Hand( { v, Suit::h }, { v, Suit::c } ),
        Hand( { v, Suit::d }, { v, Suit::h } ),
        Hand( { v, Suit::d }, { v, Suit::c } ),
    };
}

template < std::size_t PatternArraySize >
std::optional< std::vector< Range::const_iterator > >
matchPatternArrayHandsInRange( const Range &                           r,
                               std::array< Hand, PatternArraySize > && patternArray,
                               double                                  handWeight ) {
    std::vector< Range::const_iterator > matchedElements;

    bool isMatched = true;

    for ( const auto & matchHand : patternArray ) {
        matchedElements.push_back( r.find( RangeNode { matchHand, handWeight } ) );

        if ( matchedElements.back() == r.end() ) {
            isMatched = false;
            std::cout << "NOT CONTAIN\n\n";
            break;
        }
    }

    if ( !isMatched )
        return {};

    return { matchedElements };
}
}   // namespace

std::string to_string( const Range & r ) {
    std::string s;

    /*
 * the range string elements are one of
 * { [CARD + CARD] , [CARD_VALUE + CARD_VALUE] , [CARD_VALUE + CARD_VALUE + s], [CARD_VALUE + CARD_VALUE + o]  }
 *
 *
 * example : KhQs, KQ, KQs, KQo,
 */
    Range                      groupedHands { r };
    std::vector< std::string > groupedHandsStr;

    for ( auto curIt = groupedHands.begin(); curIt != groupedHands.end(); ) {
        const auto nodeLeftCard  = curIt->hand.left().getValue();
        const auto nodeRightCard = curIt->hand.right().getValue();

        std::optional< std::vector< Range::const_iterator > >
        matchedHandsIteraorsOrNull;

        if ( nodeLeftCard == nodeRightCard ) {
            matchedHandsIteraorsOrNull = matchPatternArrayHandsInRange(
            groupedHands, patternArrayForPairs( nodeLeftCard ), curIt->handWeight );

            if ( matchedHandsIteraorsOrNull ) {
                std::string tmpStr( to_string( nodeLeftCard ) +
                                    to_string( nodeRightCard ) );

                if ( std::isless( curIt->handWeight, 1.0 ) )
                    tmpStr +=
                    "[" + std::format( "{:.1f}", curIt->handWeight * 100.0 ) + "]";

                groupedHandsStr.push_back( tmpStr );
            }

        } else {
            matchedHandsIteraorsOrNull = matchPatternArrayHandsInRange(
            groupedHands,
            patternArrayForAll( nodeLeftCard, nodeRightCard ),
            curIt->handWeight );

            if ( matchedHandsIteraorsOrNull ) {
                std::string tmpStr( to_string( nodeLeftCard ) +
                                    to_string( nodeRightCard ) );

                if ( std::isless( curIt->handWeight, 1.0 ) )
                    tmpStr +=
                    "[" + std::format( "{:.1f}", curIt->handWeight * 100.0 ) + "]";

                groupedHandsStr.push_back( tmpStr );
            }

            if ( !matchedHandsIteraorsOrNull ) {
                matchedHandsIteraorsOrNull = matchPatternArrayHandsInRange(
                groupedHands,
                patternArrayForSuit( nodeLeftCard, nodeRightCard ),
                curIt->handWeight );

                if ( matchedHandsIteraorsOrNull ) {
                    std::string tmpStr( to_string( nodeLeftCard ) +
                                        to_string( nodeRightCard ) + "s" );

                    if ( std::isless( curIt->handWeight, 1.0 ) )
                        tmpStr +=
                        "[" + std::format( "{:.1f}", curIt->handWeight * 100.0 ) +
                        "]";

                    groupedHandsStr.push_back( tmpStr );
                }
            }

            if ( !matchedHandsIteraorsOrNull ) {
                matchedHandsIteraorsOrNull = matchPatternArrayHandsInRange(
                groupedHands,
                patternArrayForOffsuit( nodeLeftCard, nodeRightCard ),
                curIt->handWeight );

                if ( matchedHandsIteraorsOrNull ) {
                    std::string tmpStr( to_string( nodeLeftCard ) +
                                        to_string( nodeRightCard ) + "o" );

                    if ( std::isless( curIt->handWeight, 1.0 ) )
                        tmpStr +=
                        "[" + std::format( "{:.1f}", curIt->handWeight * 100.0 ) +
                        "]";

                    groupedHandsStr.push_back( tmpStr );
                }
            }
        }

        if ( matchedHandsIteraorsOrNull )
            for ( auto & matchHand : matchedHandsIteraorsOrNull.value() ) {
                curIt = groupedHands.erase( matchHand );
            }
        else
            ++curIt;
    }

    for ( auto const & groupedStr : groupedHandsStr )
        s += groupedStr + ", ";

    for ( auto & rnode : groupedHands )
        s += rnode.hand.asStr() + ", ";

    return s;
}
}   // namespace core::engine
