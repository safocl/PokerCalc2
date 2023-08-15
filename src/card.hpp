/**
 *@file card.hpp
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

#include "types.hpp"
#include "utils.hpp"

#include <format>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <concepts>

namespace core::engine {

enum class Suit : u8 {
    UNINITIALIZE = 0,
    d            = 1,
    s            = 2,
    c            = 3,
    h            = 4,
    MAX          = 4,
    MIN          = 1
};

inline std::string to_string( Suit s ) {
    std::string str;

    switch ( s ) {
    case Suit::c: str = "c"; break;
    case Suit::h: str = "h"; break;
    case Suit::s: str = "s"; break;
    case Suit::d: str = "d"; break;
    default:
        throw std::runtime_error(
        "the card::asStr() method is called for a invalid card suite" );
    }

    return str;
}

enum class Value : u16 {
    UNINITIALIZE = 0,
    v2           = /*1 <<*/ 1,
    v3           = /*1 <<*/ 2,
    v4           = /*1 <<*/ 3,
    v5           = /*1 <<*/ 4,
    v6           = /*1 <<*/ 5,
    v7           = /*1 <<*/ 6,
    v8           = /*1 <<*/ 7,
    v9           = /*1 <<*/ 8,
    vT           = /*1 <<*/ 9,
    vJ           = /*1 <<*/ 10,
    vQ           = /*1 <<*/ 11,
    vK           = /*1 <<*/ 12,
    vA           = /*1 <<*/ 13,
    MAX          = 13,
    MIN          = 1
};

inline std::string to_string( Value v ) {
    std::string str;

    switch ( v ) {
    case Value::v2: str = "2"; break;
    case Value::v3: str = "3"; break;
    case Value::v4: str = "4"; break;
    case Value::v5: str = "5"; break;
    case Value::v6: str = "6"; break;
    case Value::v7: str = "7"; break;
    case Value::v8: str = "8"; break;
    case Value::v9: str = "9"; break;
    case Value::vT: str = "T"; break;
    case Value::vJ: str = "J"; break;
    case Value::vQ: str = "Q"; break;
    case Value::vK: str = "K"; break;
    case Value::vA: str = "A"; break;
    default:
        throw std::runtime_error(
        "the card::asStr() method is called for a invalid card value" );
    }

    return str;
}

constexpr auto operator<=>( Value lhs, Value rhs ) {
    return to_underlying( lhs ) <=> to_underlying( rhs );
}

constexpr auto operator<=>( Suit lhs, Suit rhs ) {
    return to_underlying( lhs ) <=> to_underlying( rhs );
}

constexpr auto operator+( Suit lhs, std::underlying_type_t< Suit > rhs ) {
    return static_cast< Suit >( to_underlying( lhs ) + rhs );
}

constexpr auto operator-( Suit lhs, std::underlying_type_t< Suit > rhs ) {
    return static_cast< Suit >( to_underlying( lhs ) - rhs );
}

constexpr auto operator+( Value lhs, std::underlying_type_t< Value > rhs ) {
    return static_cast< Value >( to_underlying( lhs ) + rhs );
}

constexpr auto operator-( Value lhs, std::underlying_type_t< Value > rhs ) {
    return static_cast< Value >( to_underlying( lhs ) - rhs );
}

class Card final {
    Value v { Value::UNINITIALIZE };
    Suit  s { Suit::UNINITIALIZE };

public:
    constexpr Card() = default;
    constexpr Card( Value v, Suit s ) :
    v( [ v ] {
        if ( v > Value::MAX || v < Value::MIN )
            throw std::invalid_argument( std::format(
            "Card initialized with invalid Value.\nDon't use this card object!!!"
            "\nValue is [{}] but min value is [{}] and max value is [{}]"
            "\n*************************************************************************\n\n",

            to_underlying( v ),
            to_underlying( Value::MIN ),
            to_underlying( Value::MAX ) ) );
        return v;
    }() ),
    s( [ s ] {
        if ( s > Suit::MAX || s < Suit::MIN )
            throw std::invalid_argument( std::format(
            "Card initialized with invalid Suit."
            "\nDon't use this card object!!!\nSuit is [{}] but min value is [{}] and max value is [{}]"
            "\n*************************************************************************\n\n",

            to_underlying( s ),
            to_underlying( Suit::MIN ),
            to_underlying( Suit::MAX ) ) );
        return s;
    }() ) {}

    //    Card(const Card &) = delete;

    constexpr bool operator==( const Card & c ) const {
        return eqValue( c ) && eqSuit( c );
    }

    constexpr bool operator<( const Card & c ) const { return v < c.v; }

    constexpr bool operator>( const Card & c ) const { return c < *this; }

    constexpr bool eqValue( const Card & c ) const { return v == c.v; }

    constexpr bool eqSuit( const Card & c ) const { return s == c.s; }

    std::string asStr() const;
    void        print() const;

    constexpr Value getValue() const { return v; }
    constexpr Suit  getSuit() const { return s; }

    friend struct CardTraits;

private:
    constexpr Card( std::underlying_type_t< Value > v,
                    std::underlying_type_t< Suit >  s ) :
    v( Value { v } ),
    s( Suit { s } ) {}
};

/// @brief Common traits for Cards
struct CardTraits {
    static constexpr auto VALUE_MIN = to_underlying( Value::MIN );
    static constexpr auto VALUE_MAX = to_underlying( Value::MAX );
    static constexpr auto SUIT_MIN  = to_underlying( Suit::MIN );
    static constexpr auto SUIT_MAX  = to_underlying( Suit::MAX );

    static constexpr Card sentinel { to_underlying( Value::MAX ) + 1,
                                     to_underlying( Suit::MAX ) + 1 };
    static constexpr Card begin { Value::MIN, Suit::MIN };

    /// @brief Comparator for the std::map like contaners.
    struct CompareLess {
        constexpr bool operator()( const Card & lhs, const Card & rhs ) const {
            return lhs.v == rhs.v ? lhs.s < rhs.s : lhs.v < rhs.v;
        }
    };

    /// @brief Cyclic next value for new card
    static constexpr Card nextValue( Card card ) {
        if ( card.v == Value::MAX ) {
            card.v = Value::MIN;
            return card;
        }

        const auto intv = static_cast< int >( card.v ) + 1;
        card.v          = static_cast< Value >( intv );

        return card;
    }

    /// @brief Cyclic preview value for new card
    static constexpr Card prevValue( Card card ) {
        if ( card.v == Value::MIN ) {
            card.v = Value::MAX;
            return card;
        }

        const auto intv = static_cast< int >( card.v ) - 1;
        card.v          = static_cast< Value >( intv );

        return card;
    }

    /// @brief Cyclic next suit for new card
    static constexpr Card nextSuit( Card card ) {
        if ( card.s == Suit::MAX ) {
            card.s = Suit::MIN;
            return card;
        }

        const auto ints = static_cast< int >( card.s ) + 1;
        card.s          = static_cast< Suit >( ints );

        return card;
    }

    /// @brief Cyclic preview value for new card
    static constexpr Card prevSuit( Card card ) {
        if ( card.s == Suit::MIN ) {
            card.s = Suit::MAX;
            return card;
        }

        const auto ints = static_cast< int >( card.s ) - 1;
        card.s          = static_cast< Suit >( ints );

        return card;
    }

    /// @brief NON-CYCLED Preview card
    /// @details The order of the cards is undefined.
    /// If card is { Value::MIN, Suit::MIN } then returned sentinel.
    static constexpr Card prev( Card card ) {
        if ( card.v == Value::MIN && card.s == Suit::MIN )
            return sentinel;

        card.v = card.v - 1;

        if ( card.v < Value::MIN ) {
            card   = prevSuit( card );
            card.v = Value::MAX;
        }

        return card;
    }

    /// @brief NON-CYCLED Next card
    /// @details The order of the cards is undefined.
    /// If card is { Value::MAX, Suit::MAX } then returned sentinel.
    static constexpr Card next( Card card ) {
        if ( card.v == Value::MAX && card.s == Suit::MAX )
            return sentinel;

        card.v = card.v + 1;

        if ( card.v > Value::MAX ) {
            card   = nextSuit( card );
            card.v = Value::MIN;
        }

        return card;
    }
};
}   // namespace core::engine

namespace std {
/// @brief Hash function (functor) for the std::unordered_map like contaners.
template <> struct hash< core::engine::Card > {
    constexpr std::size_t operator()( const core::engine::Card & c ) const {
        return to_underlying( c.getValue() ) + to_underlying( c.getSuit() ) * 100;
    }
};

}   // namespace std
