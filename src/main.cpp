#include <iostream>
#include <cstdlib>
#include <ostream>
#include "board.hpp"
#include "hand.hpp"
#include "deck.hpp"
#include "card.hpp"
#include "strength.hpp"
#include <cassert>

int main() {
    using namespace core::engine;

#include "unittests/card"

    Hand     hero { c2c, cAd };
    Hand     opp { Card { Value::v6, Suit::d },
               Card { Value::v6, Suit::s } };
    Deck     deck;
    Board    board;
    Strength heroStrenght;
    heroStrenght.calc( board, opp );

    std::cout << "Hand: " << hero.hight().asStr()
              << hero.low().asStr() << std::endl
              << ( 1 << 2 ) << std::endl;

    return EXIT_SUCCESS;
}
