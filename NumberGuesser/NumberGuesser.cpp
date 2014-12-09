/* Author: Kevin Morris <kevr@nixcode.us>
 * File: NumberGuesser.h
 * This module is responsible for the guesser data structure
 * involved in this assignment */
#include "NumberGuesser.h"
#include <cstdlib>
using namespace std;

// Range class definitions
Range::Range(int min, int max)
    : _min(min)
    , _mid((min + max) / 2.0)
    , _max(max)
{
    // min/max constructor
}

Range
Range::cutLow() const
{
    return Range(_min, _mid);
}

Range
Range::cutHigh() const
{
    return Range(_mid, _max);
}
// End Range class

// NumberGuesser Node class definitions
NumberGuesser::Node::Node(int newValue)
    : value(newValue)
    , left(NULL)
    , right(NULL)
{
    /* default constructor */
}

NumberGuesser::Node::~Node()
{
    if(left)
        delete left;
    if(right)
        delete right;
}
// End NumberGuesser Node class definitions

// NumberGuesser class definitions
NumberGuesser::NumberGuesser(int min, int max)
    : root(NULL)
    , current(NULL)
{
    populate(min, max);
    /* Initialize all the things */
}

NumberGuesser::~NumberGuesser()
{
    if(root)
        delete root;
}

void NumberGuesser::insert(int newValue)
{
    insert(root, newValue);
}

/* private insert bouncer */
void NumberGuesser::insert(Node *& node, int newValue)
{
    if(!node)
        node = new Node(newValue);
    else if(newValue < node->value)
        insert(node->left, newValue);
    else if(newValue > node->value)
        insert(node->right, newValue);
}

int NumberGuesser::reset()
{
    current = root;
    return current ? current->value : -1;
}

int NumberGuesser::higher()
{
    current = current->right;
    return current ? current->value : -1;
}

int NumberGuesser::lower()
{
    current = current->left;
    return current ? current->value : -1;
}

void NumberGuesser::populate(int min, int max)
{
    populate(Range(min, max));
    current = root;
}

#ifdef EBUG
#include <iostream>
#endif

void NumberGuesser::populate(const Range& range)
{
    insert(range.mid());

    if(range.mid() == range.min())
        return;
    else if(range.mid() + 1 == range.max())
    {
        insert(range.max());
        return;
    }

    populate(range.cutLow());
    populate(range.cutHigh());
}

