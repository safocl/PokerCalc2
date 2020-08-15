#include <string_view>

enum class Suit { d, s, c, h };
enum class Value {
    v2,
    v3,
    v4,
    v5,
    v6,
    v7,
    v8,
    v9,
    vT,
    vJ,
    vQ,
    vK,
    vA
};

class Card final {
    Value v;
    Suit  s;

public:
    Card( Value, Suit );
    void print() const;
    bool operator==(const Card&) const;
    bool operator<(const Card&) const;
    bool operator>(const Card&) const;
    Card operator++();
    Card operator++(int);
    Card operator--();
    Card operator--(int);
    bool eqValue(const Card&) const;
    bool eqSuit(const Card&) const;
    std::string_view asStr() const;

};
