#pragma once

#include "board.hpp"
#include "hand.hpp"

namespace core::engine{
class Equity final {
public:
    struct Eq final {
        float hero, opp, tie;
    };

private:
    Eq eq;

public:
    void calculate( Board, Hand, Hand);
    Eq   getEq() const;
};
}
