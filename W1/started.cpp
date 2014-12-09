/* Assignment 1: Kevin Morris
 * This is a program that reimplements the example main function
 * another way and with multiple functions. */
#include <iostream>
#include <limits>
using namespace std;

int clearInput(istream& is); // 'Resets' an input stream
int getAsterisks(); // Asks the user for a number of asterisks recursively
bool getQuit(); // Asks the user if they'd like to quit or not

int main()
{
    int asterisks = 0;
    bool quit = false;

    while(!quit)
    {
        asterisks = getAsterisks();

        for(int i = 0; i < asterisks; ++i)
            cout << '*';
        cout << '\n';

        quit = getQuit();
    }

    return 0;
}

int clearInput(istream& is)
{
    is.clear();
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    return 0;
}

int getAsterisks()
{
    int count = 0;

    cout << "Enter the number of count to display: ";
    if(!(cin >> count))
    {
        count = clearInput(cin);
        cout << "You must enter a valid integer\n";
        return getAsterisks();
    }

    return count;
}

bool getQuit()
{
    char quit;

    cout << "Would you like to quit? (y/n): ";
    if(!(cin >> quit) || (quit != 'y' && quit != 'n'))
    {
        quit = static_cast<char>(clearInput(cin));
        cout << "You must enter a valid option\n";
        return getQuit();
    }

    return quit == 'y';
}



