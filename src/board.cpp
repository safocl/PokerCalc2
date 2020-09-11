#include "board.hpp"
#include <stdexcept>
#include <vector>

namespace core::engine {

void Board::setFlop( Card first, Card second, Card third ) {
    if ( s == State::PREFLOP ) {
        s         = State::FLOP;
        b.at( 0 ) = first;
        b.at( 1 ) = second;
        b.at( 2 ) = third;
    } else
        throw std::runtime_error( "Board did been is not PREFLOP" );
}
void Board::setTurn( Card c ) {
    if ( s == State::FLOP ) {
        s         = State::TURN;
        b.at( 3 ) = c;
    } else
        throw std::runtime_error( "Board did been is not FLOP" );
}
void Board::setRiver( Card c ) {
    if ( s == State::TURN ) {
        s         = State::RIVER;
        b.at( 4 ) = c;
    } else
        throw std::runtime_error( "Board did been is not TURN" );
}
Board::State Board::getStreet() const { return s; }

std::vector< Card > Board::getBoard() const {
    switch ( s ) {
    case State::PREFLOP:
        throw std::runtime_error( "Logic error -- board is null" );
    case State::FLOP:
        return std::vector< Card > { b.begin(), b.begin() + 3 };
    case State::TURN:
        return std::vector< Card > { b.begin(), b.begin() + 4 };
    case State::RIVER:
        return std::vector< Card > { b.begin(), b.begin() + 5 };
    default: throw std::runtime_error( "Invalid board street" );
    }
}
}   // namespace core::engine
