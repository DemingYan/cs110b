/* Author: Kevin Morris
 * File: main.cpp
 * This program is meant to demonstrate the IntCollection module
 * from CS110B, Assignment 11
 * Copyright (C) 2014 Kevin Morris */
#include "IntCollection.h"
#include <iostream>
using namespace std;

void print_collection(const string&, const IntCollection&);

int main()
{
    IntCollection a;
    a << 34 << 64 << 72;
    print_collection("a", a);

    IntCollection b(a);
    print_collection("b", b);
    cout << "(a == b): " << (a == b) << endl;

    IntCollection c;
    c << 92 << 81;
    print_collection("c", c);
    cout << "(b == c): " << (b == c) << endl;

    c = b;
    print_collection("c", c);
    cout << "(a == c): " << (a == c) <<  endl;

    return 0;
}

void print_collection(const string& name, const IntCollection& c)
{
    cout << name << ": ";
    for(int i = 0; i < c.getSize(); ++i)
    {
        cout << c.get(i);
        if(i < c.getSize() - 1)
            cout << ", ";
    }
    cout << endl;
}



