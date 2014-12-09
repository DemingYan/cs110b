/* Author: Kevin Morris <kevr@nixcode.us>
 * File: NumberGuesser.h
 * This module is responsible for the guesser data structure
 * involved in this assignment */
#ifndef NUMBER_GUESSER_H
#define NUMBER_GUESSER_H

class Range
{
    int _min, _mid, _max;

public:
    Range(int min, int max);

    Range cutLow() const;
    Range cutHigh() const;

    const int min() const { return _min; }
    const int mid() const { return _mid; }
    const int max() const { return _max; }

};

class NumberGuesser
{
private:
    struct Node
    {
        int value;
        Node *left;
        Node *right;

        Node(int newValue);
        ~Node();
    };

    Node *root;
    Node *current;

public:
    NumberGuesser(int min, int max);
    ~NumberGuesser();

    void insert(int newValue);
    int reset();
    int higher();
    int lower();

    void populate(int min, int max);

private:
    void insert(Node *& node, int newValue);
    void populate(const Range& range);

};

#endif /* NUMBER_GUESSER_H */
 
