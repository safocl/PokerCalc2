#pragma once

#include <vector>
#include "card.hpp"

namespace core::engine {

class Board final {
public:
    enum class State { PREFLOP, FLOP, TURN, RIVER };

private:
    std::vector< Card > b;
    State               s { State::PREFLOP };

public:
    void                setFlop( Card, Card, Card );
    void                setTurn( Card );
    void                setRiver( Card );
    State               getStreet() const;
    std::vector< Card > getBoard() const;
};
}   // namespace core::engine
