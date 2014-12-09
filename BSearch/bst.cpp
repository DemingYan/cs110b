/* Author: Kevin Morris
   Assignment 3: Number Guesser
   This program guesses numbers in a both psuedo random and
   standard binary fashion. The user thinks of a number
   between 1-100, and the program attempts to find out what
   it is. The extra credit part of this program was not
   implemented with the getRandomMidpoint function. A minimal
   binary search tree was implemented and nodes are traversed
   to the next numbers it uses to ask until it reaches a leaf node */
#include <cstdlib>
#include <ctime>
#include <map>
#include <iostream>
using namespace std;

const int MIN = 1;
const int MAX = 100;

/* A set of forward declarations, so we can prototype
our helper functions for the tree */
template<typename T>
class BinarySearchTree;

struct Range;

// Bounces off of a boolean test to playGame() or playRandomGame()
void playOneGame(); 
void playGame(); // Play a single, non-random game
void playRandomGame();

bool shouldPlayAgain();

char getUserResponseToGuess(int guess);
int getMidpoint(int low, int high);

// Insert a static recursive set of ranges to distribute in
// binary nodes
void insertRange(BinarySearchTree<int>& tree, Range range);

// Insert a pseudo random range of bst nodes
void insertRandomRange(BinarySearchTree<int>& tree);

// Each Range stores a min, max and middle value, giving the ability
// to create new Range objects for the lower half and upper half of
// the range.
class Range
{
    int _min;
    int _mid;
    int _max;

public:

    Range(int minimum, int maximum)
        : _min(minimum)
        , _mid(getMidpoint(minimum, maximum))
        , _max(maximum)
    {
        // Defined as an initialization constructor
    }

    Range cutLow()
    {
        return Range(_min, _mid);
    }

    Range cutHigh()
    {
        return Range(_mid, _max);
    }

    const int min() const
    {
        return _min;
    }

    const int mid() const
    {
        return _mid;
    }

    const int max() const
    {
        return _max;
    }

};

// A half-way implemented Binary Search Tree to use for
// the decisions in this program. If we hit a leaf, the user's
// number has not been found in the BST.
template<typename T>
class BinarySearchTree
{
    struct Node
    {
        T value;
        Node *left;
        Node *right;

        Node(const T& value) : value(value)
        {
            left = right = NULL;
        }

        ~Node()
        {
            if(left)
                delete left;
            if(right)
                delete right;
        }

    };

    Node *root;

public:
    Node *current;

public:

    BinarySearchTree()
        : root(NULL), current(root)
    {
        // Default initialization constructor
    }

    ~BinarySearchTree()
    {
        if(root)
            delete root;
    }

    BinarySearchTree& insert(const T& value)
    {
        insert(root, value);
        return *this;
    }

    int left()
    {
        current = current->left;
        if(!current)
            return 0;
        return current->value;
    }

    int right()
    {
        current = current->right;
        if(!current)
            return 0;
        return current->value;
    }

    void reset()
    {
        current = root;
    }

private:

    void insert(Node *& node, const T& value)
    {
        if(!node)
            node = new Node(value);
        else if(value < node->value)
            insert(node->left, value);
        else
            insert(node->right, value);
    }

};

// A boolean value that statically stores whether or not
// the game should be a random one.
static bool& randomGame()
{
    static bool value = false;
    return value;
}

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        string arg(argv[1]);
        if(arg == "-r")
            randomGame() = true;
        else
        {
            cerr << "usage: " << argv[0] << " [-r]\n"
                 << "\t-r | Random guesses\n";
            return 1;
        }
    }

    if(randomGame())
        srand(time(NULL));

    do
    {
        playOneGame();
    } while(shouldPlayAgain());

    return 0;
}

// Insert a non-random set of ranges into a BST of integers
void insertRange(BinarySearchTree<int>& tree, Range range)
{
    int mid = range.mid();

    if(mid == range.min() || mid == range.max())
        return;

    tree.insert(mid);

    insertRange(tree, range.cutLow());
    insertRange(tree, range.cutHigh());
}

// Insert a random set of ranges into a BST of integers
// with a blacklist map.
void insertRandomRange(BinarySearchTree<int>& tree)
{
    map<int, bool> n;

    while(n.size() != 100)
    {
        int randomNumber = rand() % MAX + MIN;
        if(n.find(randomNumber) == n.end())
        {
            tree.insert(randomNumber);
            n[randomNumber] = true;
        }
    }
}

void playOneGame()
{
    cout << "Think of a number between 1 and 100!\n";

    if(randomGame())
        playRandomGame();
    else
        playGame();
}

void playGame()
{
    BinarySearchTree<int> tree;
    // Insert initial ranges 1-100, then add 1 and 100 in at the tail
    // since our Range structure does not cover min/max
    insertRange(tree, Range(1, 100));
    tree.insert(1);
    tree.insert(100);
    
    // Reset the current node to root
    tree.reset();

    int current = tree.current->value;
    char choice;

    while(current)
    {
        choice = getUserResponseToGuess(current);

        if(choice == 'h')
            current = tree.right();
        else if(choice == 'l')
            current = tree.left();
        else
            break;
    }

    cout << endl;
    if(!current)
        cout << "You lied to me, your number is not here!\n";
    else
        cout << "Nice, so your number is " << current << endl;
    cout << endl;

}

void playRandomGame()
{
    cout << "[Random Mode]\n";
    BinarySearchTree<int> tree;
    insertRandomRange(tree);
    tree.reset();

    int current = tree.current->value;
    char choice;

    while(current)
    {
        choice = getUserResponseToGuess(current);

        if(choice == 'h')
            current = tree.right();
        else if(choice == 'l')
            current = tree.left();
        else
            break;
    }

    cout << endl;
    if(!current)
        cout << "You lied to me, your number is not here!\n";
    else
        cout << "Nice, so your number is " << current << endl;
    cout << endl;
}

bool shouldPlayAgain()
{
    string input;

    cout << "Would you like to play again? (y/n): ";
    getline(cin, input);

    char choice = tolower(input[0]);
    if(choice != 'y' && choice != 'n')
    {
        cerr << "You have entered an invalid choice, try again\n";
        return shouldPlayAgain();
    }

    return choice == 'y';
}

char getUserResponseToGuess(int guess)
{
    string input;

    cout << "Is it " << guess << "? (h/l/c): ";
    getline(cin, input);

    char choice = tolower(input[0]);

    if(choice != 'h' && choice != 'l' && choice != 'c')
    {
        cout << "You must choose either h, l, or c; Try again\n";
        return getUserResponseToGuess(guess);
    }

    return choice;
}

int getMidpoint(int low, int high)
{
    return (low + high) / 2;
}


