/* Author: Kevin Morris
 * Task: Assignment 2: Blackjack
 * File: blackjack.cpp
 * Description: A blackjack game made with high entropy read from
 * /dev/urandom which is part of the Linux kernel.
 * Extra challenge: Add a dealer. */
#include "entropy.h"
#include <map>
#include <vector>
#include <limits>
#include <iostream>
using namespace std;

typedef map<int, string> FaceMap;

template<typename T>
struct Singleton
{
    static T& getInstance()
    {
        static T instance;
        return instance;
    }
};

/* A single playing card of value A-K
_value: The actual value of the card
_face: The face of the card, i.e. A, 5, 9, Q, K */
class Card
{
    int _value;
    string _face;

public:
    Card() {}

    Card(int value, const string& face)
        : _value(value), _face(face)
    {
        // Just used to initialize _value and _face
    }

    const int value() const
    {
        return _value;
    }

    const string& face() const
    {
        return _face;
    }

};

class Deck
{
    const int DECK_SIZE = 52;
    const int SHAPE_MAX = 4;

    map<int, Card> _deck;
    Seed _seed;

public:
    Deck()
    {
        buildDeck();
        shuffle();
    }

    Card draw()
    {
        int randomCard = rand() % 52 + 1;
        while(!exists(randomCard))
            randomCard = rand() % 52 + 1;

        map<int, Card>::iterator i = _deck.find(randomCard);
        Card card = i->second;
        _deck.erase(i);

        return card;
    }

    Deck& rebuild()
    {
        FaceMap& faces = Singleton<FaceMap>::getInstance();
        for(int i = 0; i < 52; ++i)
        {
            if(!exists(i))
            {
                int num = i / 4 + 1;
                _deck[i] = Card(num > 10 ? 10 : num, faces[num]);
            }
        }
        return *this;
    }

    /* It is possible to pass a functor to this function of
    void parameter to output a possible message if desired */
    template<typename F>
    Deck& shuffle(F functor)
    {
        functor();
        srand(_seed.generate());
        return *this;
    }

    Deck& shuffle()
    {
        srand(_seed.generate());
        return *this;
    }

private:

    /* This function builds a clean standard deck of size 52 */
    void buildDeck()
    {
        FaceMap& faces = Singleton<FaceMap>::getInstance();
        for(int i = 0; i < 52; ++i)
            _deck[i] = Card(i / 4 + 1 > 10 ? 10 : i / 4 + 1, faces[i / 4 + 1]);
    }

    bool exists(const int key)
    {
        try
        {
            _deck.at(key);
        }
        catch(...)
        {
            return false;
        }
        return true;
    }
};

class Player
{

protected:
    vector<Card> _hand;
    int _total;

public:
    Player() : _total(0) {}

    void give(const Card& card)
    {
        _total += card.value();
        _hand.push_back(card);
    }

    const vector<Card>& show() const
    {
        return _hand;
    }

    map<int, int> total() const
    {
        map<int, int> totals;
        totals[0] = 0;
        totals[1] = 0;

        vector<Card>::const_iterator card;
        for(card = _hand.cbegin(); card != _hand.cend(); ++card)
        {
            for(int i = 0; i < 2; ++i)
            {
                if(i && card->value() == 1)
                    totals[i] += 11;
                else
                    totals[i] += card->value();
            }
        }

        return totals;
    }

    void clear()
    {
        _hand.clear();
        _total = 0;
    }

};

class Dealer : public Player
{
    Deck _deck;

private:

    struct Shuffle
    {
        void operator()()
        {
            cout << "The dealer shuffles the deck...\n";
        }
    };

public:
    Dealer() : Player()
    {
        _deck.shuffle(Shuffle());
    }

    void deal(Player& player)
    {
        player.give(_deck.draw());
    }

    void rebuildDeck()
    {
        _deck.rebuild();
    }

    void shuffle()
    {
        _deck.shuffle(Shuffle());
    }

};

int getYesNo()
{
    char input = 'y', c;
    while(true)
    {
        c = cin.get();
        if(cin.eof())
        {
            cin.clear();
            c = '\n';
            input = 'n';
            cout << 'n' << endl;
        }

        if(c == '\n')
            break;

        input = c;
    }
    input = tolower(input);

    if(input != 'y' && input != 'n')
        return -1;

    return input == 'y' ? 1 : 0;
}

class Table
{
    Dealer _dealer;
    Player _player;

    map<int, string> _faces;

public:

    Table()
    {
    }

    Table& play()
    {
        for(int i = 0; i < 2; ++i)
        {
            _dealer.deal(_player);
            _dealer.deal(_dealer);
        }

        displayHand("Dealer", _dealer);
        displayHand("Player", _player);

        bool done = false;
        bool dHit = true, pHit = true;
        while(!done)
        {
            if(dHit)
            {
                if((dHit = askHit("Dealer", _dealer)))
                    _dealer.deal(_dealer);

                map<int, int> totals = _dealer.total();

                if(totals[0] > 21)
                {
                    cout << "Dealer broke with "
                         << totals[0] << "!\n";
                    break;
                }
            }

            if(pHit)
            {
                if((pHit = askHit("Player", _player)))
                    _dealer.deal(_player);

                map<int, int> totals = _player.total();

                if(totals[0] > 21)
                {
                    cout << "Player broke with "
                         << totals[0] << "!\n";
                    break;
                }
            }

            if(!dHit && !pHit)
                done = true;
        }

        return *this;
    }

    Table& reset()
    {
        _player.clear();
        _dealer.clear();
        _dealer.rebuildDeck();
        _dealer.shuffle();
        return *this;
    }

private:

    bool askHit(const char *name, Player& player)
    {
        cout << "Would the " << name << " like to hit? (y/n): ";
        int retval = getYesNo();

        if(!retval)
            return false;
        
        if(retval == -1)
        {
            cerr << "You must enter y or n, case insensitive\n";
            return askHit(name, player);
        }

        return retval;
    }

    void displayHand(const char *name, Player& player)
    {
        FaceMap& faces = Singleton<FaceMap>::getInstance();
        cout << name << "'s hand: ";

        const vector<Card>& hand = player.show();
        vector<Card>::const_iterator iter;

        map<int, int> totals = player.total();

        for(iter = hand.cbegin(); iter != hand.cend(); ++iter)
            cout << iter->face() << ' ';
        cout << "(Total: " << totals[0] << ")";
        if(totals[1] > totals[0])
            cout << " (Ace High: " << totals[1] << ")";
        cout << endl;
    }

    bool check(int total)
    {
        return !(total > 21);
    }

};

int main(int argc, char *argv[])
{
    FaceMap& faces = Singleton<FaceMap>::getInstance();
    // Initialize face int -> string table
    faces[1] = "A";
    faces[2] = "2";
    faces[3] = "3";
    faces[4] = "4";
    faces[5] = "5";
    faces[6] = "6";
    faces[7] = "7";
    faces[8] = "8";
    faces[9] = "9";
    faces[10] = "10";
    faces[11] = "J";
    faces[12] = "Q";
    faces[13] = "K";

    Table table;
    bool done = false;
    int quit = 0;

    while(!done)
    {
        table.play().reset();
        cout << "Would you like to play again? (y/n): ";
        quit = !getYesNo();
        while(quit == -1)
        {
            cerr << "You must enter y or n, case insensitive\n";
            cout << "Would you like to play again? (y/n): ";
            quit = !getYesNo();
        }

        if(quit)
            done = true;
    }

    cout << "Thanks for coming to the casino!\n";

    return 0;
}


