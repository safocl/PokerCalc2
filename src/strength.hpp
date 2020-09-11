#pragma once

#include "combo.hpp"
#include "board.hpp"
#include "hand.hpp"
#include <bits/stdint-intn.h>

namespace core::engine {
class Strength final {
public:
    enum Strengthes : int16_t {
        HI           = 1,
        PAIR         = ( 1 << 1 ),
        TWO_PAIRS    = ( 1 << 2 ),
        SET          = ( 1 << 3 ),
        STRAIT       = ( 1 << 4 ),
        FLUSH        = ( 1 << 5 ),
        FULL_HOUSE   = ( 1 << 6 ),
        CARE         = ( 1 << 7 ),
        STRAIT_FLUSH = ( 1 << 8 ),
        ONE_OC       = ( 1 << 9 ),
        TWO_OC       = ( 1 << 10 ),
        FD           = ( 1 << 11 ),
        SD           = ( 1 << 12 ),
        GUT_SHOT     = ( 1 << 13 )
    };

private:
    Strengthes currentStrength;

public:
    Strengthes getStrength() const;
    Strengthes calc( const Board &, const Hand & );
};
}   // namespace core::engine
