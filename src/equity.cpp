#include "equity.hpp"
#include "combo.hpp"
#include "strength.hpp"
#include <iterator>
#include <vector>

namespace core::engine {

static Equity::Eq calcPreflop( Board board [[maybe_unused]],
                               Hand  hero [[maybe_unused]],
                               Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

static Equity::Eq calcFlop( Board board [[maybe_unused]],
                            Hand  hero [[maybe_unused]],
                            Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

static Equity::Eq calcTurn( Board board [[maybe_unused]],
                            Hand  hero [[maybe_unused]],
                            Hand  opp [[maybe_unused]] ) {
    return Equity::Eq { 1.0, 1.0, 1.0 };
}

static Equity::Eq calcRiver( Board board [[maybe_unused]],
                             Hand  hero [[maybe_unused]],
                             Hand  opp [[maybe_unused]] ) {
    Strength heroStrength;
    heroStrength.calc( board, hero );

    Strength oppStrength;
    oppStrength.calc( board, opp );

    Equity::Eq eq {};

    auto sameStraitFlushEq = [ & ]() {
        Combo heroCombo { board, hero };
        Combo oppCombo { board, opp };

        Card heroHiCard;
        for ( auto heroIt = heroCombo.asSortedVector().rbegin();
              heroIt != heroCombo.asSortedVector().rend() - 4;
              ++heroIt ) {
            auto heroItPlus1 = std::next( heroIt );
            auto heroItPlus2 = std::next( heroItPlus1 );
            auto heroItPlus3 = std::next( heroItPlus2 );
            auto heroItPlus4 = std::next( heroItPlus3 );

            auto heroCard      = *heroIt;
            auto heroCardPlus1 = *heroItPlus1;
            auto heroCardPlus2 = *heroItPlus2;
            auto heroCardPlus3 = *heroItPlus3;
            auto heroCardPlus4 = *heroItPlus4;

            for ( int i = 0; i < 4; ++i )
                ++heroCardPlus4;
            for ( int i = 0; i < 3; ++i )
                ++heroCardPlus3;
            for ( int i = 0; i < 2; ++i )
                ++heroCardPlus2;
            ++heroCardPlus1;

            if ( heroCard == heroCardPlus1 &&
                 heroCard == heroCardPlus2 &&
                 heroCard == heroCardPlus3 &&
                 heroCard == heroCardPlus4 )
                heroHiCard = heroCard;
        }

        Card oppHiCard;
        for ( auto oppIt = oppCombo.asSortedVector().rbegin();
              oppIt != heroCombo.asSortedVector().rend() - 4;
              ++oppIt ) {
            auto oppItPlus1 = std::next( oppIt );
            auto oppItPlus2 = std::next( oppItPlus1 );
            auto oppItPlus3 = std::next( oppItPlus2 );
            auto oppItPlus4 = std::next( oppItPlus3 );

            auto oppCard      = *oppIt;
            auto oppCardPlus1 = *oppItPlus1;
            auto oppCardPlus2 = *oppItPlus2;
            auto oppCardPlus3 = *oppItPlus3;
            auto oppCardPlus4 = *oppItPlus4;

            for ( int i = 0; i < 4; ++i )
                ++oppCardPlus4;
            for ( int i = 0; i < 3; ++i )
                ++oppCardPlus3;
            for ( int i = 0; i < 2; ++i )
                ++oppCardPlus2;
            ++oppCardPlus1;

            if ( oppCard == oppCardPlus1 && oppCard == oppCardPlus2 &&
                 oppCard == oppCardPlus3 && oppCard == oppCardPlus4 )
                oppHiCard = oppCard;
        }
        if ( heroHiCard > oppHiCard )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroHiCard < oppHiCard )
            return Equity::Eq { 0, 1, 0 };
        return Equity::Eq { 0, 0, 1 };
    };

    auto sameCareEq = [ & ]() {
        Combo heroCombo { board, hero };
        Combo oppCombo { board, opp };

        Card heroHiCard;
        for ( auto heroIt = heroCombo.asSortedVector().rbegin();
              heroIt != heroCombo.asSortedVector().rend() - 3;
              ++heroIt ) {
            auto heroItPlus1 = std::next( heroIt );
            auto heroItPlus2 = std::next( heroItPlus1 );
            auto heroItPlus3 = std::next( heroItPlus2 );

            auto heroCard      = *heroIt;
            auto heroCardPlus1 = *heroItPlus1;
            auto heroCardPlus2 = *heroItPlus2;
            auto heroCardPlus3 = *heroItPlus3;

            if ( heroCard.eqValue( heroCardPlus1 ) &&
                 heroCard.eqValue( heroCardPlus2 ) &&
                 heroCard.eqValue( heroCardPlus3 ) )
                heroHiCard = heroCard;
        }

        Card oppHiCard;
        for ( auto oppIt = oppCombo.asSortedVector().rbegin();
              oppIt != heroCombo.asSortedVector().rend() - 4;
              ++oppIt ) {
            auto oppItPlus1 = std::next( oppIt );
            auto oppItPlus2 = std::next( oppItPlus1 );
            auto oppItPlus3 = std::next( oppItPlus2 );

            auto oppCard      = *oppIt;
            auto oppCardPlus1 = *oppItPlus1;
            auto oppCardPlus2 = *oppItPlus2;
            auto oppCardPlus3 = *oppItPlus3;

            if ( oppCard.eqValue( oppCardPlus1 ) &&
                 oppCard.eqValue( oppCardPlus2 ) &&
                 oppCard.eqValue( oppCardPlus3 ) )
                oppHiCard = oppCard;
        }
        if ( heroHiCard > oppHiCard )
            return Equity::Eq { 1, 0, 0 };
        else if ( heroHiCard < oppHiCard )
            return Equity::Eq { 0, 1, 0 };
        return Equity::Eq { 0, 0, 1 };
    };

    switch ( heroStrength.getStrength() ) {
    case Strength::STRAIT_FLUSH: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq = sameStraitFlushEq();
            break;
        }
        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::CARE: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::FULL_HOUSE: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::FLUSH: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FLUSH: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::STRAIT: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::STRAIT: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::SET: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::STRAIT: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::SET: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::TWO_PAIRS: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::STRAIT: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::SET: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::TWO_PAIRS: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    case Strength::PAIR: {
        switch ( oppStrength.getStrength() ) {
        case Strength::STRAIT_FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::CARE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FULL_HOUSE: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::FLUSH: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::STRAIT: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::SET: {
            eq.hero = 0.0;
            eq.opp  = 1.0;
            eq.tie  = 0.0;
            break;
        }

        case Strength::PAIR: {
            break;
        }

        default: {
            eq.hero = 1.0;
            eq.opp  = 0.0;
            eq.tie  = 0.0;
        }
        }
        break;
    }

    default: {
    }
    }

    return Equity::Eq { 1.0, 1.0, 1.0 };
}

void Equity::calculate( Board board, Hand hero, Hand opp ) {
    if ( board.getStreet() == Board::State::PREFLOP )
        eq = calcPreflop( board, hero, opp );
    if ( board.getStreet() == Board::State::FLOP )
        eq = calcFlop( board, hero, opp );
    if ( board.getStreet() == Board::State::TURN )
        eq = calcTurn( board, hero, opp );
    if ( board.getStreet() == Board::State::RIVER )
        eq = calcRiver( board, hero, opp );
}

Equity::Eq Equity::getEq() const { return eq; }
}   // namespace core::engine
