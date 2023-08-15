/**
 *@file range.cpp
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

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <set>
#include <format>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
// #include <type_traits>

#include "range.hpp"
#include "card.hpp"
#include "utils.hpp"

namespace rng  = std::ranges;
namespace rngw = rng::views;

namespace core::engine {

namespace {
constexpr std::size_t forAllArraySize     = 16;
constexpr std::size_t forSuitArraySize    = 4;
constexpr std::size_t forOffsuitArraySize = 12;
constexpr std::size_t forPairArraySize    = 6;

using ArrayForAll     = std::array< Hand, forAllArraySize >;
using ArrayForSuit    = std::array< Hand, forSuitArraySize >;
using ArrayForOffsuit = std::array< Hand, forOffsuitArraySize >;
using ArrayForPair    = std::array< Hand, forPairArraySize >;

using SameWeightHands       = std::unordered_set< Hand >;
using SplitedRangesByWeight = std::vector< std::pair< double, SameWeightHands > >;

constexpr std::string serializeDelimiter { ", " };

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

SplitedRangesByWeight splitRangeByWeight( const Range & r ) {
    std::set< double > uniqueWeights;

    for ( auto & rangeNode : r )
        uniqueWeights.insert( rangeNode.handWeight );

    SplitedRangesByWeight splitedRangeByWeight;

    for ( auto uniqueValue : uniqueWeights ) {
        SameWeightHands uniqueWeightRange;

        auto weightedHands =
        rngw::filter( r,
                      [ uniqueValue ]( auto && el ) {
                          return !std::islessgreater( el.handWeight, uniqueValue );
                      } ) |
        rngw::transform( []( auto && el ) { return el.hand; } );

        rng::copy( weightedHands,
                   std::inserter( uniqueWeightRange, uniqueWeightRange.begin() ) );

        /*
		 * or better range-based for sample?
		 */
        // for ( auto const & rn : r )
        //     if ( !std::islessgreater( rn.handWeight, uniqueValue ) )
        //         uniqueWeightRange.insert( rn.hand );

        splitedRangeByWeight.push_back(
        { uniqueValue, std::move( uniqueWeightRange ) } );
    }

    return splitedRangeByWeight;
}

std::string wrapToWeight( std::string_view handListStr, double handWeight ) {
    handListStr.remove_suffix( serializeDelimiter.size() );
    return std::format( "[{0:.1f}]{1}[/{0:.1f}]", handWeight * 100.0, handListStr );
}

std::pair< std::vector< SameWeightHands::const_iterator >, std::string >
packHands( const SameWeightHands & hands, Value lhs, Value rhs ) {
    std::vector< SameWeightHands::const_iterator > matchedHandsIteratorsOrEmpty;

    std::string packedHandsByWeightStr;

    if ( lhs == rhs ) {
        matchedHandsIteratorsOrEmpty =
        find_all( hands, patternArrayForPairs( lhs ) );

        if ( !matchedHandsIteratorsOrEmpty.empty() ) {
            packedHandsByWeightStr += to_string( lhs ) + to_string( rhs );
        }

    } else {
        matchedHandsIteratorsOrEmpty =
        find_all( hands, patternArrayForAll( lhs, rhs ) );

        if ( !matchedHandsIteratorsOrEmpty.empty() ) {
            packedHandsByWeightStr += to_string( lhs ) + to_string( rhs );
        }

        if ( matchedHandsIteratorsOrEmpty.empty() ) {
            matchedHandsIteratorsOrEmpty =
            find_all( hands, patternArrayForSuit( lhs, rhs ) );

            if ( !matchedHandsIteratorsOrEmpty.empty() ) {
                packedHandsByWeightStr += to_string( lhs ) + to_string( rhs ) + "s";
            }
        } else if ( matchedHandsIteratorsOrEmpty.empty() ) {
            matchedHandsIteratorsOrEmpty =
            find_all( hands, patternArrayForOffsuit( lhs, rhs ) );

            if ( !matchedHandsIteratorsOrEmpty.empty() ) {
                packedHandsByWeightStr += to_string( lhs ) + to_string( rhs ) + "o";
            }
        }
    }

    return { matchedHandsIteratorsOrEmpty, packedHandsByWeightStr };
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
 *
 *
 * algo prototype:
 *	1. split range by hand Weight
 *	2. in the every splited subrange do group the hands in the strings
 *	3. concatenate all the subrange strings
 */
    std::vector< std::string > groupedHandsStr;

    auto splitedRangeByWeight = splitRangeByWeight( r );

    for ( auto & groupedHands : splitedRangeByWeight ) {
        const auto weightOfSplitedRange = groupedHands.first;

        std::string groupedHandsByWeightStr;

        for ( auto curIt = groupedHands.second.begin();
              curIt != groupedHands.second.end(); ) {
            const auto nodeLeftCard  = curIt->left().getValue();
            const auto nodeRightCard = curIt->right().getValue();

            auto [ matchedHandsIteratorsOrEmpty, packedHandsByWeightStr ] =
            packHands( groupedHands.second, nodeLeftCard, nodeRightCard );

            if ( !matchedHandsIteratorsOrEmpty.empty() ) {
                groupedHandsByWeightStr +=
                packedHandsByWeightStr + serializeDelimiter;

                for ( auto & matchHand : matchedHandsIteratorsOrEmpty ) {
                    curIt = groupedHands.second.erase( matchHand );
                }
            } else
                ++curIt;
        }

        for ( auto & nonPackedHand : groupedHands.second )
            groupedHandsByWeightStr += nonPackedHand.asStr() + serializeDelimiter;

        if ( std::isless( weightOfSplitedRange, 1.0 ) ) {
            groupedHandsByWeightStr =
            wrapToWeight( groupedHandsByWeightStr, weightOfSplitedRange );

            groupedHandsByWeightStr += serializeDelimiter;
        }

        groupedHandsStr.push_back( groupedHandsByWeightStr );
    }

    for ( std::string_view packedHandsStr : groupedHandsStr ) {
        s += packedHandsStr;
    }
    auto sv = std::string_view( s );
    sv.remove_suffix( serializeDelimiter.size() );

    return std::string( sv );
}

// Range from_string( std::string_view str ) { return {}; }
}   // namespace core::engine
