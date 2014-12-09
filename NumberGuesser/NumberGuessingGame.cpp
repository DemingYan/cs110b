/* Author: Kevin Morris <kevr@nixcode.us>
 * File: NumberGuesser.h
 * This is the main function module responsible for starting
 * execution of the game and maintaining flow control */
#include "NumberGuesser.h"
#include <map>
#include <iostream>
using namespace std;

int lower(NumberGuesser& tree);
int higher(NumberGuesser& tree);
int found(NumberGuesser& tree);

int main(int argc, char *argv[])
{
    NumberGuesser tree(1, 100);
    int cur;
    string input;
    char choice, again = 'y';

    map<char, int(*)(NumberGuesser&)> cb;
    cb['h'] = &higher;
    cb['l'] = &lower;
    cb['c'] = &found;

    while(again == 'y')
    {
        cur = tree.reset();
        while(cin && cur)
        {
            cout << "Is " << cur << " your number? (h/l/c): ";
            getline(cin, input);

            if(!input.size()
               || cb.find((choice = tolower(input[0]))) == cb.end())
            {
                cout << "You must enter a valid option\n";
                continue;
            }

            int retval = cb[choice](tree);
            if(retval == -1)
            {
                cout << "Your number was not between 1-100, liar\n";
                break;
            }
            else if(retval == 0)
            {
                cout << "Oh! so your number was " << cur << ", cool\n";
                break;
            }

            cur = retval;

        }
        cout << "Do you want to play again? (y/n): ";
        getline(cin, input);
        if(input.size())
            again = tolower(input[0]);

    }

    return 0;
}

int lower(NumberGuesser& tree)
{
    return tree.lower();
}

int higher(NumberGuesser& tree)
{
    return tree.higher();
}

int found(NumberGuesser& tree)
{
    return 0;
}


