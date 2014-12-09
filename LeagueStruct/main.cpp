/* Author: Kevin Morris
 * File: main.cpp
 * Assignment 8: Baseball League with Structs
 * Write a version of the previous league program with
 * structured data */
#include <iostream>
#include <string>
#include <cstring>
#include <limits>
using namespace std;

struct winRecord
{
    char *name;
    int wins;

    winRecord() : name(NULL) { /* Default constructor */ }

    winRecord(const winRecord& other)
        : name(NULL)
    {
        this->operator=(other);
    }

    winRecord(const char *teamName, const int teamWins)
        : name(new char[strlen(teamName) + 1])
        , wins(teamWins)
    {
        strncpy(name, teamName, strlen(teamName));
    }

    ~winRecord()
    {
        if(name)
            delete [] name;
    }

    winRecord& operator=(const winRecord& other)
    {
        if(name)
        {
            delete [] name;
            name = NULL;
        }

        name = new char[strlen(other.name) + 1];
        strncpy(name, other.name, strlen(other.name));

        wins = other.wins;

        return *this;
    }

};

bool getInput(istream& is, int& data);
int prompt(const char *message);

void allocate(winRecord *& standings, int size);
void initializeData(winRecord *& standings, int size);

template<typename T>
void swap(T *p1, T *p2);

void sortData(winRecord *standings, int size);
void displayData(winRecord *standings, int size);

int main()
{
    winRecord *records = NULL;

    int size = prompt("Enter the number of teams in the league: ");
    if(size <= 0)
    {
        cout << "You did not enter any teams, you don't "
             << "even have a league. Good bye.\n";
        return 1;
    }

    // Allocate memory for records.
    allocate(records, size);

    initializeData(records, size);
    sortData(records, size);
    displayData(records, size);

    delete [] records;
    return 0;
}

bool getInput(istream& is, int& data)
{
    if(!(is >> data))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

bool getInput(istream& is, string& data)
{
    // Ignore stream so we can getline properly
    getline(is, data);
    return data.size();
}

int prompt(const char *message)
{
    int data;
    cout << message;
    while(!getInput(cin, data))
        cout << "You entered an invalid number, try again\n" << message;
    return data;
}

void allocate(winRecord *& standings, int size)
{
    if(!standings)
        standings = new winRecord[size];
}

void initializeData(winRecord *& standings, int size)
{
    string temp;
    for(int i = 0; i < size; ++i)
    {
        cout << "Enter team name #" << i + 1 << ": ";
        if(!getInput(cin, temp))
        {
            cout << "You did not enter a valid team name, try again.\n";
            --i;
            continue;
        }
        standings[i] = winRecord(temp.c_str(), 0);

        cout << "Enter the " << standings[i].name << " team score: ";
        while(!getInput(cin, standings[i].wins) || standings[i].wins < 0)
        {
            cout << "You did not enter a positive score, try again.\n"
                 << "Enter the " << standings[i].name << " team score: ";
        }

    }
}

template<typename T>
void swap(T *p1, T *p2)
{
    T temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

// Selection sort, O(n^2) complexity
void sortData(winRecord *standings, int size)
{
    int i = 0, j = 0, idx = 0;
    for(; i < size - 1; ++i)
    {
        idx = i;
        for(j = i + 1; j < size; ++j)
        {
            if(standings[j].wins > standings[idx].wins)
                idx = j;
        }

        if(idx != i)
            swap(&standings[i], &standings[idx]);
    }
}

void displayData(winRecord *standings, int size)
{
    cout << "\nLeague Standings\n";
    for(int i = 0; i < size; ++i)
        cout << standings[i].name << ": " << standings[i].wins << endl;
    cout << endl;
}


