/* Author: Kevin Morris
 * File: main.cpp
 * License: GPL2
 * C-String implementation functions */
#include <iostream>
#include <cstring>
#include <iomanip>
#include <deque>
using namespace std;

template<typename T>
void swap(T *p1, T *p2);

int lastIndexOf(char *s, char target);
void reverse(char *s);
int replace(char *s, char target, char repl);
int sumSubstring(char *s, size_t len);
int findSubstring(char *s, char target[]);
bool isPalindrome(char *s);

int main(int argc, char *argv[])
{
    string testStrings[] = {
        "racecar", "hardyharhar", "Good Game, Dude!", "Bro.orB"
    };

    string target = "ro.";

    for(int i = 0; i < 4; ++i)
    {
        bool pld = isPalindrome(&testStrings[i][0]);

        cout << lastIndexOf(&testStrings[i][0], 'a') << endl
             << (pld ? "True\n" : "False\n") << testStrings[i]
             << endl;

        reverse(&testStrings[i][0]);
        cout << testStrings[i] << endl;

        replace(&testStrings[i][0], 'a', 'z');
        cout << testStrings[i] << endl;

        cout << "Substr Idx: "
             << findSubstring(&testStrings[i][0], &target[0])
             << endl;
    }

    return 0;
}

template<typename T>
void swap(T *p1, T *p2)
{
    static T tempInstance;
    tempInstance = *p1;
    *p1 = *p2;
    *p2 = tempInstance;
}

int lastIndexOf(char *s, char target)
{
    for(int i = strlen(s) - 1; i >= 0; --i)
    {
        if(s[i] == target)
            return i;
    }
    return -1;
}

void reverse(char *s)
{
    char *f = s, *e = s + strlen(s) - 1;
    while(f < e)
        swap(f++, e--);
}

int replace(char *s, char target, char repl)
{
    bool found = false;
    for(char *p = s; *p != '\0'; ++p)
    {
        if(*p == target)
        {
            *p = repl;
            found = true;
        }
    }

    return found;
}

int sumSubstring(char *s, size_t len)
{
    int sum = 0;
    for(size_t i = 0; i < len; ++i)
        sum += int(*(s++));
    return sum;
}

int findSubstring(char *s, char target[])
{
    int sum = 0;
    int stringLen = strlen(s);
    int targetLen = strlen(target);

    for(int i = 0; i < targetLen; ++i)
        sum += int(target[i]);

    for(int i = 0; i < stringLen; ++i)
    {
        if(stringLen - i < targetLen)
            break;

        if(sumSubstring(&s[i], targetLen) == sum)
            return i;
    }

    return -1;
}

bool isPalindrome(char *s)
{
    char *f = s, *e;
    for(e = s + strlen(s) - 1; f != e; ++f, --e)
    {
        if(*f != *e)
            return false;
    }

    return true;
}

