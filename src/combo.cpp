#include "combo.hpp"
#include "board.hpp"
#include <stdexcept>

namespace core::engine {
Combo::Combo( Board b, Hand h ) { set( b, h ); }
void Combo::set( Board b, Hand h ) {
    if ( b.getStreet() != Board::State::FLOP ||
         b.getStreet() != Board::State::TURN ||
         b.getStreet() != Board::State::RIVER )
        throw std::runtime_error(
        "In Strength::getStrength() board is invalid" );

    combo = b.getBoard();
    combo.push_back( h.left() );
    combo.push_back( h.right() );
    std::sort( combo.begin(), combo.end() );
}
std::vector< Card > Combo::asVector() const { return combo; }

}   // namespace core::engine
