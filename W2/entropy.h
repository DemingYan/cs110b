/* Author: Kevin Morris
 * Task: Assignment 2: Blackjack
 * File: blackjack.cpp
 * Description: A blackjack game made with high entropy read from
 * /dev/urandom which is part of the Linux kernel.
 * Extra challenge: Add a dealer. */
#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdexcept>
#include <string>
#include <fstream>
#include <ctime>

const char *const URANDOM_PATH = "/dev/urandom";

/* A templated combination of two static_casts, for shorter
 * notational T3 -> T -> T2 calling */
template<typename T, typename T2, typename T3>
T2 double_cast(T3 origin)
{
    return static_cast<T2>(static_cast<T>(origin));
}

/* _chunk: A chunk of memory allocated with sizeof(int) bytes
 * _value: An integer pointer to _chunk for integer dereference */
class EntropyStream
{
    std::ifstream _ifs;
    int *_value;
    char *_chunk;
    
    const size_t CHUNK_SIZE = sizeof(int);

public:
    /* Attempt to initalize _ifs and throw an error if path
    could not be read */
    EntropyStream(const std::string& path)
        : _ifs(path.c_str(), std::ios::binary)
    {
        if(!_ifs)
            throw std::domain_error(path + " couldn't be open for reading");

        _chunk = new char[CHUNK_SIZE];
        _value = double_cast<void*, int*>(_chunk);
    }

    /* A default constructor setup to delegate EntropyStream(path)
    with a default /dev/urandom path, a high entropy device node
    which we'll read CHUNK_SIZE bytes of random data at a time from to
    generate better seeds by XORing them with the current time */
    EntropyStream() : EntropyStream(URANDOM_PATH) {}

    ~EntropyStream()
    {
        delete _value;

        if(_ifs.is_open())
            _ifs.close();
    }

    /* Generate one random seed by reading CHUNK_SIZE bytes from
    _ifs into _chunk and accessing it via _value deref */
    int generate()
    {
        if(!_ifs)
            return 0;

        _ifs.read(_chunk, CHUNK_SIZE);

        return *_value | time(0);
    }

};

class Seed
{
    EntropyStream _entropy;
    int _value;

public:
    Seed() : _value(generate()) {}

    operator int()
    {
        return _value;
    }

    int generate()
    {
        _value = _entropy.generate();
        return _value;
    }

};

#endif /* ENTROPY_H */

