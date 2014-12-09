#include "RandomNumberGuesser.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int main()
{
    srand(time(NULL));

    NumberGuesser *rng = new RandomNumberGuesser(1, 10);

    int guess = rng->getCurrentGuess();
    bool miss = false;
    char c = '\0';

    while((c != 'c'))
    {
        cout << "Is " << guess << " your number? (h/l/c): ";
        cin >> c;

        if(c == 'h')
            rng->higher();
        else if(c == 'l')
            rng->lower();

        if(rng->getCurrentGuess() == guess && (miss = true))
            break;

        guess = rng->getCurrentGuess();
    }

    if(!miss)
        cout << "Ok, so your number is " << guess << endl;
    else
        cout << "You lied, your number is not here\n";

    delete rng;
    return 0;
}

