/* Author: Kevin Morris
 * Assignment 5: Baseball League
 * This program stores a baseball league in memory
 * based on a count given from the command line */
#include <iostream>
#include <limits>
#include <cstdlib>
#include <map>
using namespace std;

template<typename T>
void swap(T *p1, T *p2);

void initializeData(string n[], int s[], int size);
void sortData(string n[], int s[], int size);
void displayData(string n[], int s[], int size);
bool searchTeam(string n[], int size, const string& target);

string getTeam();
int getInput();

int main(int argc, char *argv[])
{
    int teamCount;
    cout << "How many teams will you enter?: ";
    cin >> teamCount;

    string *teamName = new string[teamCount];
    int *teamScore = new int[teamCount];

    initializeData(teamName, teamScore, teamCount);
    sortData(teamName, teamScore, teamCount);
    displayData(teamName, teamScore, teamCount);

    delete[] teamScore;
    delete[] teamName;

    return 0;
}

template<typename T>
void swap(T *p1, T *p2)
{
    T temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void initializeData(string n[], int s[], int size)
{
    for(int i = 0; i < size; ++i)
    {
        cout << "Enter team #" << i + 1 << ": ";
        string team;
        while(searchTeam(n, size, (team = getTeam())))
        {
            cerr << "That team already exists!\n";
            cout << "Enter team #" << i + 1 << ": ";
        }

        n[i] = team;

        cout << "Enter the wins for team #" << i + 1 << ": ";
        while((s[i] = getInput()) < 0)
        {
            cerr << "You must input a score >= 0\n";
            cout << "Enter the wins for team #" << i + 1 << ": ";
        }
    }
}

void sortData(string n[], int s[], int size)
{
    int idx, val;
    for(int i = 0; i < size - 1; ++i)
    {
        idx = i;
        val = s[idx];
        for(int j = i + 1; j < size; ++j)
        {
            if(s[j] > val)
            {
                idx = j;
                val = s[j];
            }
        }
        swap(&s[i], &s[idx]);
        swap(&n[i], &n[idx]);
    }
}

void displayData(string n[], int s[], int size)
{
    cout << "League Standings:\n";
    for(int i = 0; i < size; ++i)
        cout << n[i] << ": " << s[i] << endl;
}

bool searchTeam(string n[], int size, const string& target)
{
    for(int i = 0; i < size; ++i)
        if(n[i] == target)
            return true;
    return false;
}

string getTeam()
{
    string temp;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    getline(cin, temp);

    return temp;
}

int getInput()
{
    int value;
    if(!(cin >> value))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }

    return value;
}


