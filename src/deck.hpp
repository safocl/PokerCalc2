#include <array>
#include "card.hpp"

class Deck final {
    struct DeckNode final {
        DeckNode(Value, Suit);
        Card card;
        bool isAvaible;
    };
    std::array< DeckNode, 52 > deck;

public:
    Deck();
    ~Deck();
    Deck( const Deck & ) = delete;
    void generate( const Card &, const Card & );
    void generate( const Card & );
    bool isAvaibleCard( const Card & );
};
