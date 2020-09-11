#include "strength.hpp"
#include "board.hpp"
#include "card.hpp"
#include "combo.hpp"
#include <bits/stdint-intn.h>
#include <iterator>
#include <stdexcept>
#include <vector>

namespace core::engine {
static bool hasStraitFlush( const Combo & );
static bool hasCare( const Combo & );
static bool hasFullHouse( const Combo & );
static bool hasFlush( const Combo & );
static bool hasStrait( const Combo & );
static bool hasSet( const Combo & );
static bool hasTwoPairs( const Combo & );
static bool hasPair( const Combo & );
static bool hasFlushDraw( const Combo & );
static bool hasStraitDraw( const Combo & );
static bool hasGutShot( const Combo & );
static bool hasTwoOC( const Board &, const Hand & );
static bool hasOneOC( const Board &, const Hand & );

Strength::Strengthes Strength::getStrength() const {
    return currentStrength;
}

Strength::Strengthes Strength::calc( const Board & board,
                                     const Hand &  hand ) {
    const Combo combo { board, hand };

    int currentStrengthInt { static_cast< int >( currentStrength ) };

    if ( hasStraitFlush( combo ) )
        currentStrengthInt += Strengthes::STRAIT_FLUSH;
    else if ( hasCare( combo ) )
        currentStrengthInt += Strengthes::CARE;
    else if ( hasFullHouse( combo ) )
        currentStrengthInt += Strengthes::FULL_HOUSE;
    else if ( hasFlush( combo ) )
        currentStrengthInt += Strengthes::FLUSH;
    else if ( hasStrait( combo ) )
        currentStrengthInt += Strengthes::STRAIT;
    else if ( hasSet( combo ) )
        currentStrengthInt += Strengthes::SET;
    else if ( hasTwoPairs( combo ) )
        currentStrengthInt += Strengthes::TWO_PAIRS;
    else if ( hasPair( combo ) )
        currentStrengthInt += Strengthes::PAIR;

    if ( hasFlushDraw( combo ) )
        currentStrengthInt += Strengthes::FD;
    if ( hasStraitDraw( combo ) )
        currentStrengthInt += Strengthes::SD;
    if ( hasGutShot( combo ) )
        currentStrengthInt += Strengthes::GUT_SHOT;
    if ( hasTwoOC( board, hand ) )
        currentStrengthInt += Strengthes::TWO_OC;
    if ( hasOneOC( board, hand ) )
        currentStrengthInt += Strengthes::ONE_OC;

    currentStrength = static_cast< Strengthes >( currentStrengthInt );
    return currentStrength;
}

static bool hasStraitFlush( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 4;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto cardItPlus4 = std::next( cardItPlus3 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;
        auto cardPlus4   = *cardItPlus4;

        for ( int8_t i = 0; i < 4; ++i )
            ++card;
        for ( int8_t i = 0; i < 3; ++i )
            ++cardPlus1;
        for ( int8_t i = 0; i < 2; ++i )
            ++cardPlus2;
        for ( int8_t i = 0; i < 1; ++i )
            ++cardPlus3;
        if ( card == cardPlus1 && card == cardPlus2 &&
             card == cardPlus3 && card == cardPlus4 )
            return true;
    }

    return false;
}

static bool hasCare( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 3;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;

        if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) &&
             card.eqValue( cardPlus3 ) )
            return true;
    }

    return false;
}

static bool hasFullHouse( const Combo & combo ) {
    auto tmpComboVec = combo.asSortedVector();
    for ( auto cardIt = tmpComboVec.begin();
          cardIt != tmpComboVec.end() - 2;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;

        if ( card.eqValue( cardPlus1 ) &&
             card.eqValue( cardPlus2 ) ) {
            tmpComboVec.erase( cardIt, cardItPlus2 );
            for ( auto cardIt = tmpComboVec.begin();
                  cardIt != tmpComboVec.end() - 1;
                  ++cardIt ) {
                auto cardItPlus1 = std::next( cardIt );
                auto card        = *cardIt;
                auto cardPlus1   = *cardItPlus1;

                if ( card.eqValue( cardPlus1 ) )
                    return true;
            }
        }
    }

    return false;
}

static bool hasFlush( const Combo & combo ) {
    auto tmpComboVec = combo.asSortedVector();
    std::sort(
    tmpComboVec.begin(),
    tmpComboVec.end(),
    []( Card f, Card l ) -> bool { return f.eqSuit( l ); } );

    for ( auto cardIt = tmpComboVec.begin();
          cardIt != tmpComboVec.end() - 4;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto cardItPlus4 = std::next( cardItPlus3 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;
        auto cardPlus4   = *cardItPlus4;

        if ( card.eqSuit( cardPlus4 ) && card.eqSuit( cardPlus3 ) &&
             card.eqSuit( cardPlus2 ) && card.eqSuit( cardPlus1 ) )
            return true;
    }

    return false;
}

static bool hasStrait( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 4;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto cardItPlus4 = std::next( cardItPlus3 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;
        auto cardPlus4   = *cardItPlus4;

        for ( int8_t i = 0; i < 4; ++i )
            ++card;
        for ( int8_t i = 0; i < 3; ++i )
            ++cardPlus1;
        for ( int8_t i = 0; i < 2; ++i )
            ++cardPlus2;
        for ( int8_t i = 0; i < 1; ++i )
            ++cardPlus3;
        if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) &&
             card.eqValue( cardPlus3 ) && card.eqValue( cardPlus4 ) )
            return true;
    }

    return false;
}

static bool hasSet( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 2;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;

        if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) )
            return true;
    }

    return false;
}

static bool hasTwoPairs( const Combo & combo ) {
    auto tmpComboVec = combo.asSortedVector();
    for ( auto cardIt = tmpComboVec.begin();
          cardIt != tmpComboVec.end() - 3;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;

        if ( card.eqValue( cardPlus1 ) ) {
            tmpComboVec.erase( cardIt, cardItPlus1 );
            for ( auto cardIt = tmpComboVec.begin();
                  cardIt != tmpComboVec.end() - 1;
                  ++cardIt ) {
                auto cardItPlus1 = std::next( cardIt );
                auto card        = *cardIt;
                auto cardPlus1   = *cardItPlus1;

                if ( card.eqValue( cardPlus1 ) )
                    return true;
            }
        }
    }

    return false;
}

static bool hasPair( const Combo & combo ) {
    auto tmpComboVec = combo.asSortedVector();
    for ( auto cardIt = tmpComboVec.begin();
          cardIt != tmpComboVec.end() - 1;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;

        if ( card.eqValue( cardPlus1 ) )
            return true;
    }

    return false;
}

static bool hasFlushDraw( const Combo & combo ) {
    auto tmpComboVec = combo.asSortedVector();
    std::sort(
    tmpComboVec.begin(),
    tmpComboVec.end(),
    []( Card f, Card l ) -> bool { return f.eqSuit( l ); } );

    for ( auto cardIt = tmpComboVec.begin();
          cardIt != tmpComboVec.end() - 3;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;

        if ( card.eqSuit( cardPlus3 ) && card.eqSuit( cardPlus2 ) &&
             card.eqSuit( cardPlus1 ) )
            return true;
    }
    return false;
}

static bool hasStraitDraw( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 3;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;

        for ( int8_t i = 0; i < 3; ++i )
            ++card;
        for ( int8_t i = 0; i < 2; ++i )
            ++cardPlus1;
        for ( int8_t i = 0; i < 1; ++i )
            ++cardPlus2;
        if ( card.eqValue( cardPlus1 ) && card.eqValue( cardPlus2 ) &&
             card.eqValue( cardPlus3 ) )
            return true;
    }

    return false;
}

static bool hasGutShot( const Combo & combo ) {
    for ( auto cardIt = combo.asSortedVector().begin();
          cardIt != combo.asSortedVector().end() - 3;
          ++cardIt ) {
        auto cardItPlus1 = std::next( cardIt );
        auto cardItPlus2 = std::next( cardItPlus1 );
        auto cardItPlus3 = std::next( cardItPlus2 );
        auto card        = *cardIt;
        auto cardPlus1   = *cardItPlus1;
        auto cardPlus2   = *cardItPlus2;
        auto cardPlus3   = *cardItPlus3;

        for ( int8_t i = 0; i < 3; ++i )
            ++card;
        for ( int8_t i = 0; i < 2; ++i )
            ++cardPlus1;
        for ( int8_t i = 0; i < 1; ++i )
            ++cardPlus2;
        if ( ( card.eqValue( cardPlus1 ) &&
               card.eqValue( cardPlus2 ) &&
               card.eqValue( ++Card { cardPlus3 } ) ) ||

             ( card.eqValue( cardPlus1 ) &&
               card.eqValue( ++Card { cardPlus2 } ) &&
               card.eqValue( ++Card { cardPlus3 } ) ) ||

             ( card.eqValue( ++Card { cardPlus1 } ) &&
               card.eqValue( ++Card { cardPlus2 } ) &&
               card.eqValue( ++Card { cardPlus3 } ) )

        )
            return true;
    }
    return false;
}

static bool hasTwoOC( const Board & board, const Hand & hand ) {
    for ( auto card : board.getBoard() )
        if ( !( hand.low() > card ) )
            return false;

    return true;
}

static bool hasOneOC( const Board & board, const Hand & hand ) {
    for ( auto card : board.getBoard() )
        if ( !( hand.hight() > card ) )
            return false;

    return true;
}
}   // namespace core::engine
