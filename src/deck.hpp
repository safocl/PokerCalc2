#pragma once

#include "board.hpp"
#include <map>
#include <string>
#include <string_view>
#include "card.hpp"

namespace core::engine {
class Deck final {
    std::map< std::string_view, bool > deck;

    void generate();
    void zeroing();

public:
    Deck();
    ~Deck();
    Deck( const Deck & ) = delete;
    Deck( Deck && )      = delete;
    void update( const Board &, const Card &, const Card & );
    void update( const Board &, const Card & );
    bool isAvaibleCard( const Card & );
};
}   // namespace core::engine
