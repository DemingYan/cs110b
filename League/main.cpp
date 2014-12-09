/* Author: Kevin Morris
 * Assignment 5: Baseball League
 * This program stores a baseball league in memory
 * based on a count given from the command line */
#include <iostream>
#include <limits>
#include <cstdlib>
#include <map>
using namespace std;

const int NUM_TEAMS = 5;

void initializeData(string n[], int s[], int size);
void sortData(string n[], int s[], int size);
void displayData(string n[], int s[], int size);
bool searchTeam(string n[], int size, const string& target);

string getTeam();
int getInput();

int main(int argc, char *argv[])
{
    string teamName[NUM_TEAMS];
    int teamScore[NUM_TEAMS];   

    initializeData(teamName, teamScore, NUM_TEAMS);
    sortData(teamName, teamScore, NUM_TEAMS);
    displayData(teamName, teamScore, NUM_TEAMS);

    return 0;
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
    map<int, int> count;

    for(int i = 0; i < size; ++i)
        count[s[i]] += 1;

    map<int, int>::iterator it;
    int i = 0;
    for(it = count.begin(); it != count.end(); ++it)
    {
        for(int j = 0; j < it->second; ++i, ++j)
            s[i] = it->first;
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
    cin >> temp;
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


