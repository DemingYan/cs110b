/* Author: Kevin Morris
 * Assignment 4: Poker Hands
 * This program takes a hand of values 2-9 from the user
 * and shows the most important hand availabile from it. */
#include <iostream>
#include <limits>
#include <map>
#include <list>
using namespace std;

const int HAND_SIZE = 5;
const int BASE = 10; // Base 10; Decimal

/* These two functions are responsible for getting and
persistantly storing a static referenced count of cards */
map<int, int> getCount(int hand[]);
map<int, int>& count();
bool checkCount(int target);

typedef map<int, int>::iterator TableIter;

/* These two functions are used to sort the hand before
determining if it turns out to be a straight */
int max(int values[], int sz);
void radixSort(int values[], int sz, int max);

bool containsFourOfaKind(int hand[]);
bool containsFullHouse(int hand[]);
bool containsStraight(int hand[]);
bool containsThreeOfaKind(int hand[]);
bool containsTwoPair(int hand[]);
bool containsPair(int hand[]);
bool containsNothing(int hand[]);

bool inputError(istream& is, int& n);

/* Main function */
int main()
{
    /* This variable is used to represent a constant number
    of possibilities in this program, for array construction */
    const int NUM_POSSIBLE = 7;

    int hand[HAND_SIZE];

    /* Create function pointer array, we'll cycle through these
    and test them one by one via iteration */
    bool (*fn[NUM_POSSIBLE])(int[]) = {
        &containsFourOfaKind, &containsFullHouse, &containsStraight,
        &containsThreeOfaKind, &containsTwoPair, &containsPair,
        &containsNothing
    };

    // then create messages to match the function pointers
    const char *message[NUM_POSSIBLE] = {
        "Four Of a Kind!", "Full House!", "Straight!",
        "Three Of a Kind!", "Two Pair!", "Pair!",
        "High card!"
    };

    cout << "Welcome to Easy Poker, where you get to choose all your "
         << "cards!\nEnter five numeric cards, ranged 2 - 9.\n\n";

    for(int i = 0; i < HAND_SIZE; ++i)
    {
        cout << "Card " << i + 1 << ": ";

        while(inputError(cin, hand[i]))
        {
            cerr << "Please enter a value 2-9 as instructed, thank you\n";
            cout << "Card " << i + 1 << ": ";
        }

    }

    // Scope singleton initialization out
    {
        map<int, int>& cardCount = count();
        cardCount = getCount(hand);
    }

    int i;
    for(i = 0; i < 7 && !fn[i](hand); ++i);
    cout << message[i] << endl;

    cout << "\nThank you for your playing at Choose Your "
         << "Outcome casino!\nGood bye.\n";

    return 0;
}

/* This function gets a count of same cards in the hand
and returns it as a copy */
map<int, int> getCount(int hand[])
{
    map<int, int> same;

    // Initialize all to 0
    for(int i = 0; i < HAND_SIZE; ++i)
        same[hand[i]] = 0;

    // Increase each card in map by 1 for each one found
    for(int i = 0; i < HAND_SIZE; ++i)
        same[hand[i]] += 1;

    return same;
}

/* This function returns a singleton of a map<int, int> instance
and is initialized and built with getCount on lines 82-83 */
map<int, int>& count()
{
    static map<int, int> table;
    return table;
}

bool checkCount(int target)
{
    map<int, int>& same = count();

    for(TableIter it = same.begin(); it != same.end(); ++it)
    {
        if(it->second == target)
            return true;
    }

    return false;
}

/* Grabs the maximum integer value in an array */
int max(int values[], int sz)
{
    int highest = values[0];
    for(int i = 1; i < sz; ++i)
    {
        if(values[i] > highest)
            highest = values[i];
    }

    return highest;
}

// Modeled off of the example given on wikipedia at
// http://en.wikipedia.org/wiki/Radix_sort#Example_in_C.2B.2B
void radixSort(int values[], int sz, int max)
{
    list<int> bucket[BASE];
    list<int>::iterator iter;

    for(int n = 1; n < max; n *= BASE)
    {
        for(int i = 0; i < sz; ++i)
            bucket[(values[i]/n) % BASE].push_back(values[i]);

        for(int k = 0, i = 0; i < BASE; bucket[i++].clear())
        {
            for(iter = bucket[i].begin(); iter != bucket[i].end(); ++iter)
                values[k++] = *iter;
        }

    }
}

template<typename T>
void radixSort(T values[], int sz, int max)
{
    list<T> bucket[BASE];
    typename list<T>::iterator iter;

    for(int n = 1; n < max; n *= BASE)
    {
        for(int i = 0; i < sz; ++i)
            bucket[(values[i]/n) % BASE].push_back(values[i]);

        for(int k = 0, i = 0; i < BASE; bucket[i++].clear())
        {
            for(iter = bucket[i].begin(); iter != bucket[i].end(); ++iter)
                values[k++] = *iter;
        }

    }
}

// containsThreeofaKind is defined on line 180.
// count() is defined on line 
bool containsFourOfaKind(int hand[])
{
    return checkCount(4);
}

/* If we get get this far, all we need to do is find out
if the number of unique cards is equal to 2 to determine four of a kind */
bool containsFullHouse(int hand[])
{
    return count().size() == 2;
}

/* When we get to this function in the pointer list, we use
Radix sort to order the elements and check if they're sequential */
bool containsStraight(int hand[])
{
    radixSort(hand, HAND_SIZE, max(hand, HAND_SIZE));
    map<int, int>& same = count();

    for(int i = 1, j = hand[0]; i < HAND_SIZE; ++i, j = hand[i - 1])
    {
        if(hand[i] != j + 1)
            return false;
    }

    return true;
}

bool containsThreeOfaKind(int hand[])
{
    return checkCount(3);
}

bool containsTwoPair(int hand[])
{
    int pairs = 0;
    map<int, int>& same = count();

    for(TableIter it = same.begin(); it != same.end(); ++it)
    {
        if(it->second == 2)
            pairs += 1;
    }

    return pairs == 2;
}

// All of these contains functions are called in reverse order
bool containsPair(int hand[])
{
    return checkCount(2);
}

// If we hit this function, we've already tried to match
// every other type of hand possible, return true to succeed
bool containsNothing(int hand[])
{
    return true;
}

bool inputError(istream& is, int& n)
{
    if(!(is >> n))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return true;
    }

    return n < 2 || n > 9;
}


