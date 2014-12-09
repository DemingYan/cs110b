/* Author: Kevin Morris
 * Task: Assignment 2
 * File: main.cpp
 * This file is the main source file for a Blackjack clone
 * which is playable on the command line interface. */
#include "deck.h"
#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

template<typename T1, typename T2, typename T3>
T2 double_cast(T3 original)
{
    return static_cast<T2>(static_cast<T1>(original));
}

int randomBytes()
{
    ifstream ifs("/dev/urandom", ios::binary);
    if(!ifs)
        return 0;

    int bytes = 0;
    ifs.read(double_cast<void*, char*>(&bytes), sizeof(int));
    ifs.close();

    return bytes;
}

int main()
{
    // Seed random generator with /dev/urandom and the current time
    srand(randomBytes() | time(NULL));

    return 0;
}

