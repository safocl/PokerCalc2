/**
 *\file strength.cpp
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

#include "utils.hpp"
#include "strength.hpp"
#include "board.hpp"
#include "card.hpp"
#include "combo.hpp"

#include <iostream>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>
#include <algorithm>

namespace core::engine {

Strength::Result Strength::getStrength() const {
    return { mCurrentStrength, { mSignificationCard } };
}

Strength::Result Strength::calc( const Board & board, const Hand & hand ) {
    const Combo combo { board, hand };

    std::underlying_type_t< decltype( mCurrentStrength ) > currentStrengthInt {};

    auto hasStraitFlush = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 4;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto cardItPlus4 = std::next( cardItPlus3 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;
            const auto cardPlus4   = *cardItPlus4;

            if ( card.eqSuit( cardPlus1 ) && card.eqSuit( cardPlus2 ) &&
                 card.eqSuit( cardPlus3 ) && card.eqSuit( cardPlus4 ) )
                if ( ( card == CardTraits::prevValue( cardPlus1 ) &&
                       cardPlus1 == CardTraits::prevValue( cardPlus2 ) &&
                       cardPlus2 == CardTraits::prevValue( cardPlus3 ) &&
                       cardPlus3 == CardTraits::prevValue( cardPlus4 ) ) ||
                     ( card == CardTraits::prevValue( cardPlus1 ) &&
                       cardPlus1 == CardTraits::prevValue( cardPlus2 ) &&
                       cardPlus2 == CardTraits::prevValue( cardPlus3 ) &&
                       card == CardTraits::nextValue( cardPlus4 ) ) ) {
                    mSignificationCard.hi =
                    cardPlus4 > Card( Value::v5, Suit::h ) ? cardPlus4 : cardPlus3;

                    return true;
                }
        }

        return false;
    };

    auto hasCare = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 3;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;

            if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) &&
                 card.eqValue( cardPlus3 ) ) {
                mSignificationCard.hi = card;

                return true;
            }
        }

        return false;
    };

    auto hasFullHouse = [ this, &combo ] {
        auto tmpComboVec = combo.asSortedVector();
        for ( auto cardIt = tmpComboVec.begin(); cardIt != tmpComboVec.end() - 2;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;

            if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) ) {
                mSignificationCard.hi = card;

                tmpComboVec.erase( cardIt, cardItPlus2 );

                for ( auto cardIt = tmpComboVec.begin();
                      cardIt != tmpComboVec.end() - 1;
                      ++cardIt ) {
                    const auto cardItPlus1 = std::next( cardIt );
                    const auto card        = *cardIt;
                    const auto cardPlus1   = *cardItPlus1;

                    if ( card.eqValue( cardPlus1 ) ) {
                        mSignificationCard.low = card;

                        return true;
                    }
                }

                return false;
            }
        }

        return false;
    };

    auto hasFlush = [ this, &combo ] {
        auto tmpComboVec = combo.asSortedVector();
        std::sort( tmpComboVec.begin(),
                   tmpComboVec.end(),
                   []( Card f, Card l ) -> bool { return f.eqSuit( l ); } );

        for ( auto cardIt = tmpComboVec.begin(); cardIt != tmpComboVec.end() - 4;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto cardItPlus4 = std::next( cardItPlus3 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;
            const auto cardPlus4   = *cardItPlus4;

            if ( card.eqSuit( cardPlus4 ) && card.eqSuit( cardPlus3 ) &&
                 card.eqSuit( cardPlus2 ) && card.eqSuit( cardPlus1 ) ) {
                mSignificationCard.hi = card;

                return true;
            }
        }

        return false;
    };

    auto hasStrait = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 4;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto cardItPlus4 = std::next( cardItPlus3 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;
            const auto cardPlus4   = *cardItPlus4;

            if ( ( card.eqValue( CardTraits::prevValue( cardPlus1 ) ) &&
                   cardPlus1.eqValue( CardTraits::prevValue( cardPlus2 ) ) &&
                   cardPlus2.eqValue( CardTraits::prevValue( cardPlus3 ) ) &&
                   cardPlus3.eqValue( CardTraits::prevValue( cardPlus4 ) ) ) ||
                 ( card.eqValue( CardTraits::prevValue( cardPlus1 ) ) &&
                   cardPlus1.eqValue( CardTraits::prevValue( cardPlus2 ) ) &&
                   cardPlus2.eqValue( CardTraits::prevValue( cardPlus3 ) ) &&
                   card.eqValue( CardTraits::nextValue( cardPlus4 ) ) ) ) {
                mSignificationCard.hi =
                cardPlus4 > Card( Value::v5, Suit::h ) ? cardPlus4 : cardPlus3;

                return true;
            }
        }

        return false;
    };

    auto hasSet = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 2;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;

            if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) ) {
                mSignificationCard.hi = card;

                return true;
            }
        }

        return false;
    };

    auto hasTwoPairs = [ this, &combo ] {
        auto tmpComboVec = combo.asSortedVector();
        for ( auto cardIt = tmpComboVec.begin(); cardIt != tmpComboVec.end() - 3;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;

            if ( card.eqValue( cardPlus1 ) ) {
                mSignificationCard.low = card;

                tmpComboVec.erase( cardIt, cardItPlus1 );

                for ( auto cardIt = tmpComboVec.begin();
                      cardIt != tmpComboVec.end() - 1;
                      ++cardIt ) {
                    const auto cardItPlus1 = std::next( cardIt );
                    const auto card        = *cardIt;
                    const auto cardPlus1   = *cardItPlus1;

                    if ( card.eqValue( cardPlus1 ) ) {
                        mSignificationCard.hi = card;

                        return true;
                    }
                }

                return false;
            }
        }

        return false;
    };

    auto hasPair = [ this, &combo ] {
        const auto tmpComboVec = combo.asSortedVector();
        for ( auto cardIt = tmpComboVec.begin(); cardIt != tmpComboVec.end() - 1;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;

            if ( card.eqValue( cardPlus1 ) ) {
                mSignificationCard.hi = card;

                return true;
            }
        }

        return false;
    };

    auto hasFlushDraw = [ this, &combo ] {
        auto tmpComboVec = combo.asSortedVector();
        std::sort( tmpComboVec.begin(),
                   tmpComboVec.end(),
                   []( Card f, Card l ) -> bool { return f.eqSuit( l ); } );

        for ( auto cardIt = tmpComboVec.begin(); cardIt != tmpComboVec.end() - 3;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;

            if ( card.eqSuit( cardPlus3 ) && card.eqSuit( cardPlus2 ) &&
                 card.eqSuit( cardPlus1 ) ) {
                mSignificationCard.hi = *cardIt;
                ++cardIt;

                for ( ; cardIt != std::next( cardItPlus3 ); ++cardIt )
                    if ( *cardIt > mSignificationCard.hi )
                        mSignificationCard.hi = *cardIt;

                return true;
            }
        }

        return false;
    };

    auto hasStraitDraw = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 3;
              ++cardIt ) {
            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;

            if ( card.eqValue( CardTraits::prevValue( cardPlus1 ) ) &&
                 cardPlus1.eqValue( CardTraits::prevValue( cardPlus2 ) ) &&
                 cardPlus2.eqValue( CardTraits::prevValue( cardPlus3 ) ) &&
                 !cardPlus3.eqValue( Card( Value::vA, Suit::h ) ) ) {
                mSignificationCard.hi = cardPlus3;

                return true;
            }
        }

        return false;
    };

    auto hasGutShot = [ this, &combo ] {
        for ( auto cardIt = combo.asSortedVector().begin();
              cardIt != combo.asSortedVector().end() - 3;
              ++cardIt ) {
            /*
			 *GutShot is a draw combo that can turn into a strait with one out.
			 *
			 * A 2 3 4  or J Q K A
			 * [1] [2] [3] [ ] [5] or
			 * [1] [2] [ ] [4] [5] or
			 * [1] [ ] [3] [4] [5] or
			 *
			 */

            const auto cardItPlus1 = std::next( cardIt );
            const auto cardItPlus2 = std::next( cardItPlus1 );
            const auto cardItPlus3 = std::next( cardItPlus2 );
            const auto card        = *cardIt;
            const auto cardPlus1   = *cardItPlus1;
            const auto cardPlus2   = *cardItPlus2;
            const auto cardPlus3   = *cardItPlus3;

            if ( card.getValue() == Value::vJ && cardPlus1.getValue() == Value::vQ &&
                 cardPlus2.getValue() == Value::vK &&
                 cardPlus3.getValue() == Value::vA ) {
                mSignificationCard.hi  = cardPlus3;
                mSignificationCard.low = card;

                return true;
            }

            else if ( card.getValue() == Value::v2 &&
                      cardPlus1.getValue() == Value::v3 &&
                      cardPlus2.getValue() == Value::v4 &&
                      std::prev( combo.asSortedVector().end() )->getValue() ==
                      Value::vA ) {
                mSignificationCard.hi  = cardPlus2;
                mSignificationCard.low = *std::prev( combo.asSortedVector().end() );

                return true;
            }

            else if ( ( CardTraits::nextValue( card ).eqValue( cardPlus1 ) &&
                        CardTraits::nextValue( cardPlus1 ).eqValue( cardPlus2 ) &&
                        CardTraits::nextValue( CardTraits::nextValue( cardPlus2 ) )
                        .eqValue( cardPlus3 ) ) ||

                      ( CardTraits::nextValue( card ).eqValue( cardPlus1 ) &&
                        CardTraits::nextValue( CardTraits::nextValue( cardPlus1 ) )
                        .eqValue( cardPlus2 ) &&
                        CardTraits::nextValue( cardPlus2 ).eqValue( cardPlus3 ) ) ||

                      ( CardTraits::nextValue( CardTraits::nextValue( card ) )
                        .eqValue( cardPlus1 ) &&
                        CardTraits::nextValue( cardPlus1 ).eqValue( cardPlus2 ) &&
                        CardTraits::nextValue( cardPlus2 ).eqValue( cardPlus3 ) )

            ) {
                mSignificationCard.hi  = cardPlus3;
                mSignificationCard.low = card;

                return true;
            }
        }

        return false;
    };

    auto hasTwoOC = [ this, &board, &hand ] {
        for ( const auto card : board.getBoard() )
            if ( !( hand.low() > card ) )
                return false;

        mSignificationCard.hi  = hand.hight();
        mSignificationCard.low = hand.low();

        return true;
    };

    auto hasOneOC = [ this, &board, &hand ] {
        auto tmpCardVec = board.getBoard();
        for ( const auto card : tmpCardVec )
            if ( !( hand.hight() > card ) )
                return false;

        mSignificationCard.hi = hand.hight();

        std::sort( tmpCardVec.begin(), tmpCardVec.end() );

        for ( const auto card : tmpCardVec )
            if ( hand.low() < card ) {
                mSignificationCard.low = card;
                break;
            }

        return true;
    };

    if ( hasStraitFlush() )
        currentStrengthInt = to_underlying( Strengthes::STRAIT_FLUSH );
    else if ( hasCare() )
        currentStrengthInt = to_underlying( Strengthes::CARE );
    else if ( hasFullHouse() )
        currentStrengthInt = to_underlying( Strengthes::FULL_HOUSE );
    else if ( hasFlush() )
        currentStrengthInt = to_underlying( Strengthes::FLUSH );
    else if ( hasStrait() )
        currentStrengthInt = to_underlying( Strengthes::STRAIT );
    else if ( hasSet() )
        currentStrengthInt = to_underlying( Strengthes::SET );
    else if ( hasTwoPairs() )
        currentStrengthInt = to_underlying( Strengthes::TWO_PAIRS );
    else if ( hasPair() )
        currentStrengthInt = to_underlying( Strengthes::PAIR );
    else
        currentStrengthInt = to_underlying( Strengthes::HI );

    if ( board.getStreet() == Board::State::FLOP ||
         board.getStreet() == Board::State::TURN ) {
        if ( hasFlushDraw() )
            currentStrengthInt |= to_underlying( Strengthes::FD );
        if ( hasStraitDraw() )
            currentStrengthInt |= to_underlying( Strengthes::SD );
        if ( hasGutShot() )
            currentStrengthInt |= to_underlying( Strengthes::GUT_SHOT );
        if ( hasTwoOC() )
            currentStrengthInt |= to_underlying( Strengthes::TWO_OC );
        if ( hasOneOC() )
            currentStrengthInt |= to_underlying( Strengthes::ONE_OC );
    }

    mCurrentStrength = static_cast< Strengthes >( currentStrengthInt );

    return getStrength();
}

std::string Strength::asStr() const { return to_string( mCurrentStrength ); }

std::string to_string( Strength::Strengthes handStrength ) {
    std::string result;

    if ( to_underlying( handStrength ) &
         to_underlying( Strength::Strengthes::STRAIT_FLUSH ) )
        result += "STRAIT_FLUSH ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::CARE ) )
        result += "CARE ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::FULL_HOUSE ) )
        result += "FULL_HOUSE ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::FLUSH ) )
        result += "FLUSH ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::STRAIT ) )
        result += "STRAIT ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::SET ) )
        result += "SET ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::TWO_PAIRS ) )
        result += "TWO_PAIRS ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::PAIR ) )
        result += "PAIR ";

    else if ( to_underlying( handStrength ) &
              to_underlying( Strength::Strengthes::HI ) )
        result += "HI ";

    if ( to_underlying( handStrength ) &
         to_underlying( Strength::Strengthes::ONE_OC ) )
        result += "ONE_OC ";

    if ( to_underlying( handStrength ) &
         to_underlying( Strength::Strengthes::TWO_OC ) )
        result += "TWO_OC ";

    if ( to_underlying( handStrength ) & to_underlying( Strength::Strengthes::FD ) )
        result += "FD ";

    if ( to_underlying( handStrength ) & to_underlying( Strength::Strengthes::SD ) )
        result += "SD ";

    if ( to_underlying( handStrength ) &
         to_underlying( Strength::Strengthes::GUT_SHOT ) )
        result += "GUT_SHOT ";

    return std::format( "[ {}]", result );
}
}   // namespace core::engine
