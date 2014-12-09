/* Author: Kevin Morris
 * Task: Assignment 2
 * File: card.h
 * This file is the main source file for a Blackjack clone
 * which is playable on the command line interface. */
#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
    int _index, _value;
    std::string _face;

public:
    Card() { }

    Card(int cardIndex, int cardValue, const std::string& cardFace)
        : _index(cardIndex), _value(cardValue), _face(cardFace) { }

    const int index() const
    {
        return _index;
    }

    const int value() const
    {
        return _value;
    }

    const std::string& face()
    {
        return _face;
    }

};

#endif /* CARD_H */

