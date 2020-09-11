#pragma once

#include "card.hpp"
#include <utility>

namespace core::engine{
class Hand final {
    std::pair< Card, Card > h;

public:
    Hand( Card, Card );
    bool operator==( const Hand & ) const;
    bool operator<( const Hand & ) const;
    bool operator>( const Hand & ) const;
    Card low() const;
    Card hight() const;
    Card right() const;
    Card left() const;
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
}
