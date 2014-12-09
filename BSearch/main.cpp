/* Author: Kevin Morris
 * Assignment 3: Number Guesser
 * This program implements a binary search algorithm
 * for a number between 1 and 100. The human user chooses, and
 * the program attempts to figure out what the number is based on
 * answers given by the user */
#include <iostream>
#include <map>
#include <cassert>
using namespace std;

const int MIN = 1;
const int MAX = 100;

void playOneGame();
bool shouldPlayAgain();

char getUserResponseToGuess(int guess);
int getMidpoint(int low, int high);
int getRandomMidpoint(int low, int high);

bool newGuess(char input);

// Templated structures and functions must be defined before
// any use for instantiation
template<int Min, int Max>
struct Range
{
    int min;
    int mid;
    int max;

    Range() : min(Min), mid(Max / 2), max(Max)
    {
        assert(Min < Max);
    }

    int cutHigh()
    {
        min = mid;
        mid = getMidpoint(min, max);
        return mid;
    }

    int cutLow()
    {
        max = mid;
        mid = getMidpoint(min, max);
        return mid;
    }

    bool end()
    {
        return getMidpoint(min, max) == mid;
    }

};

template<int Min, int Max>
int getHighMidpoint(Range<Min, Max>& range)
{
    return range.cutHigh();
}

template<int Min, int Max>
int getLowMidpoint(Range<Min, Max>& range)
{
    return range.cutLow();
}

template<int Min, int Max>
int targetReached(Range<Min, Max>& range)
{
    return 0;
}

typedef int (*FunctionPtr)(Range<MIN, MAX>&);

struct Singleton
{
    static map<char, FunctionPtr>& getInstance()
    {
        static map<char, FunctionPtr> instance;
        return instance;
    }
};

int main()
{
    // Scope this initialization out, forget having it in main after
    {
        map<char, FunctionPtr>& fn = Singleton::getInstance();
        fn['h'] = &getHighMidpoint;
        fn['l'] = &getLowMidpoint;
        fn['c'] = &targetReached;
    }

    // This line is necessary for a random seed.
    srand(time(NULL));

    do
    {
        playOneGame();
    } while(shouldPlayAgain());

    return 0;
}

void playOneGame()
{
    map<char, FunctionPtr>& fn = Singleton::getInstance();

    // We set mid initially to 50 to begin the game.
    // m = middle, l = low, h = high, c = user's guess
    Range<1, 100> range;
    
    int current = range.mid;
    char choice = getUserResponseToGuess(range.mid);

    do
    {
        current = fn[choice](range);

        cout << "New Low: " << range.min << ", New Midpoint: " << range.mid
             << ", New High: " << range.max << endl;
        choice = getUserResponseToGuess(range.mid);
    }
    while(!range.end() && choice != 'c');

    if(!range.end() && choice == 'c')
        cout << "Finally! Your number is " << range.mid << "\n";
    else
        cout << "You lied to me\n";

    return;
}

bool shouldPlayAgain()
{
    return false;
}

char getUserResponseToGuess(int guess)
{
    string input;

    cout << "Is it " << guess << "? (h/l/c): ";
    getline(cin, input);

    char choice = tolower(input[0]);

    if(choice != 'h' && choice != 'l' && choice != 'c')
    {
        cout << "You must choose either h, l, or c; Try again\n";
        return getUserResponseToGuess(guess);
    }

    return choice;
}

int getMidpoint(int low, int high)
{
    return (low + high) / 2;
}

// In this function, we subtract 1 from high and add 1 to low
// in order to achieve a random number _between_ low and high.
int getRandomMidpoint(int low, int high)
{
    int randomRange = (--high) + (++low);
    return rand() % randomRange;
}

bool newGuess(char input)
{
    map<char, FunctionPtr>& fn = Singleton::getInstance();
    return !(fn.find(input) == fn.end());
}


