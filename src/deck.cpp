#include "deck.hpp"
#include "board.hpp"
#include <cassert>

namespace core::engine {
Deck::Deck() : deck() { generate(); }
Deck::~Deck() {}
void Deck::generate() {
    for ( int v = Card::VALUE_MIN; v != Card::VALUE_MAX; ++v )
        for ( int s = Card::SUIT_MIN; s != Card::SUIT_MAX; ++s )
            deck.insert_or_assign( Card( static_cast< Value >( v ),
                                         static_cast< Suit >( s ) )
                                   .asStr(),
                                   true );
    assert( deck.size() == 52 && "Invalid cards count" );
}

void Deck::zeroing() {
    for ( auto && deckNode : deck )
        deckNode.second = true;
}

void Deck::update( const Board & board,
                   const Card &  l,
                   const Card &  r ) {
    zeroing();
    deck.at( l.asStr() ) = false;
    deck.at( r.asStr() ) = false;
    for ( auto card : board.getBoard() )
        deck.at( card.asStr() ) = false;
}

void Deck::update( const Board & board, const Card & c ) {
    zeroing();
    deck.at( c.asStr() ) = false;
    for ( auto card : board.getBoard() )
        deck.at( card.asStr() ) = false;
}

bool Deck::isAvaibleCard( const Card & c ) {
    return deck.at( c.asStr() );
}
}   // namespace core::engine
