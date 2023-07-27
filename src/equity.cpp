/**
 *\file equity.hpp
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

#include "equity.hpp"
#include "combo.hpp"
#include "range.hpp"
#include "strength.hpp"

#include <format>
#include <algorithm>
#include <functional>
#include <iterator>
#include <vector>

namespace core::engine {

namespace {

Equity::Eq calcPreflop( Board board [[maybe_unused]],
                        Hand  hero [[maybe_unused]],
                        Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

Equity::Eq calcFlop( Board board [[maybe_unused]],
                     Hand  hero [[maybe_unused]],
                     Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

Equity::Eq calcTurn( Board board [[maybe_unused]],
                     Hand  hero [[maybe_unused]],
                     Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

Equity::Eq calcRiver( Board board, Hand hero, Hand opp ) {
    Strength heroStrength;
    heroStrength.calc( board, hero );

    Strength oppStrength;
    oppStrength.calc( board, opp );

    Equity::Eq eq {};

    auto sameStraitFlushEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameCareEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameFullHouseEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };
        else if ( heroStrength.getStrength().significationCard.low >
                  oppStrength.getStrength().significationCard.low )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.low <
                  oppStrength.getStrength().significationCard.low )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameFlushEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameStraitEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameSetEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto sameTwoPairsEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };
        else if ( heroStrength.getStrength().significationCard.low >
                  oppStrength.getStrength().significationCard.low )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.low <
                  oppStrength.getStrength().significationCard.low )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto samePairEq = [ & ]() {
        if ( heroStrength.getStrength().significationCard.hi >
             oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroStrength.getStrength().significationCard.hi <
                  oppStrength.getStrength().significationCard.hi )
            return Equity::Eq { 0, 1, 0 };

        return Equity::Eq { 0.5, 0.5, 1 };
    };

    auto const heroStrengthVal = heroStrength.getStrength().value;
    auto const oppStrengthVal  = oppStrength.getStrength().value;

    if ( heroStrengthVal & Strength::STRAIT_FLUSH ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH )
            eq = sameStraitFlushEq();
        else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::CARE ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::CARE ) {
            eq = sameCareEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::FULL_HOUSE ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::FULL_HOUSE ) {
            eq = sameFullHouseEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::FLUSH ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ||
             oppStrengthVal & Strength::FULL_HOUSE ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::FLUSH ) {
            eq = sameFlushEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::STRAIT ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ||
             oppStrengthVal & Strength::FULL_HOUSE ||
             oppStrengthVal & Strength::FLUSH ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::STRAIT ) {
            eq = sameStraitEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::SET ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ||
             oppStrengthVal & Strength::FULL_HOUSE ||
             oppStrengthVal & Strength::FLUSH ||
             oppStrengthVal & Strength::STRAIT ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::SET ) {
            eq = sameSetEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::TWO_PAIRS ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ||
             oppStrengthVal & Strength::FULL_HOUSE ||
             oppStrengthVal & Strength::FLUSH || oppStrengthVal & Strength::STRAIT ||
             oppStrengthVal & Strength::SET ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::TWO_PAIRS ) {
            eq = sameTwoPairsEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else if ( heroStrengthVal & Strength::PAIR ) {
        if ( oppStrengthVal & Strength::STRAIT_FLUSH ||
             oppStrengthVal & Strength::CARE ||
             oppStrengthVal & Strength::FULL_HOUSE ||
             oppStrengthVal & Strength::FLUSH || oppStrengthVal & Strength::STRAIT ||
             oppStrengthVal & Strength::SET ||
             oppStrengthVal & Strength::TWO_PAIRS ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        } else if ( oppStrengthVal & Strength::PAIR ) {
            eq = samePairEq();
        } else {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
    }

    else {
        Combo heroCombo { board, hero };
        Combo oppCombo { board, opp };

        if ( heroCombo.asSortedVector().back() > oppCombo.asSortedVector().back() ) {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }

        else if ( heroCombo.asSortedVector().back() <
                  oppCombo.asSortedVector().back() ) {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
        }

        else {
            eq.hero = 1.0;
            eq.opp  = 1.0;
            eq.tie  = 1.0;
        }
    }

    return eq;
}
}   // namespace

void Equity::calculate( const Hand & hero, const Hand & opp, const Board & board ) {
    switch ( board.getStreet() ) {
    case Board::State::PREFLOP: eq = calcPreflop( board, hero, opp ); break;
    case Board::State::FLOP: eq = calcFlop( board, hero, opp ); break;
    case Board::State::TURN: eq = calcTurn( board, hero, opp ); break;
    case Board::State::RIVER: eq = calcRiver( board, hero, opp ); break;
    }
}

namespace {
struct EvaluateReult final {
    double lhs {}, rhs {}, tie {}, sampleDeposit {};
};

struct ForEachEq final {
    double hand {}, range {}, tie {};
};

inline EvaluateReult evalHandVsHandWithWeight(
const RangeNode &                                  lhs,
const RangeNode &                                  rhs,
const Board &                                      board,
std::function< Equity::Eq( Board, Hand, Hand ) > & evaluateFunc ) {
    const Equity::Eq tmpEq = evaluateFunc( board, lhs.hand, rhs.hand );

    const auto sampleDeposit = lhs.handWeight * rhs.handWeight;

    return EvaluateReult { tmpEq.hero * sampleDeposit,
                           tmpEq.opp * sampleDeposit,
                           tmpEq.tie * sampleDeposit,
                           sampleDeposit };
}

inline ForEachEq forEachRangeVsHand(
const RangeNode &                                  hand,
const Range &                                      handRange,
const Board &                                      board,
std::function< Equity::Eq( Board, Hand, Hand ) > & evaluateFunc ) {
    ForEachEq totalEq { 0, 0, 0 };

    double samplesCount { 0.0 };

    for ( auto & oppNode : handRange ) {
        const auto result =
        evalHandVsHandWithWeight( hand, oppNode, board, evaluateFunc );

        totalEq.hand += result.lhs;
        totalEq.range += result.rhs;
        totalEq.tie += result.tie;

        samplesCount += result.sampleDeposit;
    }

    return { .hand  = totalEq.hand / samplesCount,
             .range = totalEq.range / samplesCount,
             .tie   = totalEq.tie / samplesCount };
}
}   // namespace

void Equity::calculate( const Range & hero,
                        const Range & opp,
                        const Board & board ) {
    /*
	 * Range equity is arithmetic average.
	 * e.g.:
	 * 0 1 1 = (0+1+1)/3 = 2/3
	 *
	 * with weights range equity is eq*sampleDeposit,
	 * where sampleDeposit is a multiply hero weight and opp weight.
	 *
	 * max hand number is 1326 ([52 cards] * [51 cards] / 2)
	 *
	 * 100% range vs 100% range is 1326*1325 = 1756950 max number samples
	 */

    std::function< Eq( Board, Hand, Hand ) > evaluateFunc;
    switch ( board.getStreet() ) {
    case Board::State::PREFLOP: evaluateFunc = calcPreflop; break;
    case Board::State::FLOP: evaluateFunc = calcFlop; break;
    case Board::State::TURN: evaluateFunc = calcTurn; break;
    case Board::State::RIVER: evaluateFunc = calcRiver; break;
    }

    /*
	 * total equity keep summaries of equity for every hands hero and opponent in the ranges.
	 * total equity need to increment by multiply of equity and sample deposit.
	 *
	 * tie value is multiply sample deposit and sample tie value.
	 */
    Eq totalEq { 0, 0, 0 };

    /*
	 * samples count need to increment by multiply of a hero hand weight
	 * and a opponent hand weight.
	 */
    double samplesCount { 0.0 };

    for ( auto & heroNode : hero )
        for ( auto & oppNode : opp ) {
            const auto result =
            evalHandVsHandWithWeight( heroNode, oppNode, board, evaluateFunc );

            totalEq.hero += result.lhs;
            totalEq.opp += result.rhs;
            totalEq.tie += result.tie;

            samplesCount += result.sampleDeposit;
        }

    eq.hero = totalEq.hero / samplesCount;
    eq.opp  = totalEq.opp / samplesCount;
    eq.tie  = totalEq.tie / samplesCount;
}

void Equity::calculate( const RangeNode & hero,
                        const Range &     opp,
                        const Board &     board ) {
    std::function< Eq( Board, Hand, Hand ) > evaluateFunc;
    switch ( board.getStreet() ) {
    case Board::State::PREFLOP: evaluateFunc = calcPreflop; break;
    case Board::State::FLOP: evaluateFunc = calcFlop; break;
    case Board::State::TURN: evaluateFunc = calcTurn; break;
    case Board::State::RIVER: evaluateFunc = calcRiver; break;
    }

    const auto forEachEq = forEachRangeVsHand( hero, opp, board, evaluateFunc );

    eq.hero = forEachEq.hand;
    eq.opp  = forEachEq.range;
    eq.tie  = forEachEq.tie;
}

void Equity::calculate( const Range &     hero,
                        const RangeNode & opp,
                        const Board &     board ) {
    std::function< Eq( Board, Hand, Hand ) > evaluateFunc;
    switch ( board.getStreet() ) {
    case Board::State::PREFLOP: evaluateFunc = calcPreflop; break;
    case Board::State::FLOP: evaluateFunc = calcFlop; break;
    case Board::State::TURN: evaluateFunc = calcTurn; break;
    case Board::State::RIVER: evaluateFunc = calcRiver; break;
    }

    const auto forEachEq = forEachRangeVsHand( opp, hero, board, evaluateFunc );

    eq.hero = forEachEq.range;
    eq.opp  = forEachEq.hand;
    eq.tie  = forEachEq.tie;
}

Equity::Eq Equity::getEq() const { return eq; }

std::string Equity::getEqAsStr() const {
    return std::format(
    "Hero eq = {}\tOpp eq = {}\t Tie = {}", eq.hero, eq.opp, eq.tie );
}
}   // namespace core::engine
