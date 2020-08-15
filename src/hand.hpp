#include "card.hpp"
#include <utility>

class Hand final {
    std::pair< Card, Card > h;

public:
    Hand( Card, Card );
    bool operator==( const Hand & ) const;
    bool operator<( const Hand & ) const;
    bool operator>( const Hand & ) const;
    Card low() const;
    Card hight() const;
};

class HandTraits final {
    Hand h;

public:
    HandTraits( const Hand & );
    bool isPair() const;
    bool isConnector() const;
    bool isGupConnector() const;
    bool is2gupConnector() const;
    bool is3gupConnector() const;
    bool isSingleSuit() const;
};
