#pragma once

#include "board.hpp"
#include "card.hpp"
#include "hand.hpp"
#include <vector>

namespace core::engine {

class Combo final {
    std::vector< Card > combo;

public:
    Combo( Board, Hand );
    void                        set( Board, Hand );
    const std::vector< Card > & asSortedVector() const;
};
}   // namespace core::engine
