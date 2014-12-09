/* Author: Kevin Morris
 * Task: Assignment 2
 * File: deck.h
 * This file is the main source file for a Blackjack clone
 * which is playable on the command line interface. */
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include <map>

// Number of cards in a standard playing card deck
const int DECK_MAX = 52;

class Faces : public std::map<int, std::string>
{
public:
    static Faces& getInstance()
    {
        static Faces instance;
        return instance;
    }
};

class Deck
{
    std::map<int, Card> deck;

public:
    Deck()
    {
        Faces& faces = Faces::getInstance();

        if(faces.empty())
        {
            faces[1]  = "A";
            faces[2]  = "2";
            faces[3]  = "3";
            faces[4]  = "4";
            faces[5]  = "5";
            faces[6]  = "6";
            faces[7]  = "7";
            faces[8]  = "8";
            faces[9]  = "9";
            faces[10] = "10";
            faces[11] = "J";
            faces[12] = "Q";
            faces[13] = "K";
        }
    }

    Card& draw()
    {
        Card card;
        return card;
    }

private:

    void buildDeck()
    {
        Faces& faces = Faces::getInstance();

        // In this loop, we do math on our iterations from 0..51
        // in order to grab the current 'card' value that we use
        // for the card's face, if card is > face 10, we give 10 as
        // value, since J = Q = K = 10
        for(int i = 0; i < DECK_MAX; ++i)
        {
            int current = i / 4 + 1;
            deck[i] = Card(i, current > 10 ? 10 : current, faces[current]);
        }
    }

};

#endif /* DECK_H */

