#include <iostream>
#include <limits>
using namespace std;

int getYesNo()
{
    char input = 'y', c;
    while(true)
    {
        c = cin.get();
        if(cin.eof() || c == '\n')
            break;
        input = c;
    }
    input = tolower(input);

    if(input != 'y' && input != 'n')
        return -1;

    return input == 'y' ? 1 : 0;
}

bool askHit(const char *name)
{
    cout << "Would the " << name << " like to hit? (y/n): ";
    int retval = getYesNo();

    if(!retval)
        return false;
    
    if(retval < 0)
    {
        if(retval == -2)
            cerr << endl;
        cerr << "You must enter y or n, case insensitive\n";
        return askHit(name);
    }

    return retval;
}

int main()
{
    bool done = false;
    while(!done)
        done = askHit("player");
    return 0;
}


