// IntCollection class implementation
// CS 110B Max Luttrell
#include "IntCollection.h"
#include <stdexcept>
#include <cstdlib>
using namespace std;

// Initializes data int array with first chunk size and set defaults
IntCollection::IntCollection()
    : data((int*)malloc(CHUNK_SIZE * sizeof(int)))
{
    size = 0;
    capacity = CHUNK_SIZE;
}

IntCollection::IntCollection(const IntCollection& c) : data(NULL)
{
    operator=(c);
}

IntCollection::~IntCollection()
{
    if(data)
        free(data);
}

IntCollection&
IntCollection::add(int value)
{
    // Allocate a chunk of memory and copy array if needed
    if((size > 0) && (size % CHUNK_SIZE == 0))
    {
        capacity += CHUNK_SIZE;
        data = (int*)realloc(data, capacity);
    }

    data[size++] = value;

    return *this;
}

// Throw an exception if we go out of bounds
int
IntCollection::get(int index) const
{  
    if(index < 0 || index >= size)
        throw domain_error("IntCollection.get() accessing index out of range");

    return data[index];
}

// Get current size of collection
int IntCollection::getSize() const
{
	return size;
}

IntCollection&
IntCollection::operator=(const IntCollection &c)
{
    size = c.size;
    capacity = c.capacity;

    // Free up current data chunk
    if(data)
    {
        free(data);
        data = NULL;
    }

    // malloc and copy over data
    data = (int*)malloc(capacity * sizeof(int));
    for(int i = 0; i < size; ++i)
        data[i] = c.data[i];

    return *this;
}

bool
IntCollection::operator==(const IntCollection &c)
{
    // Compare sizes of array,
    // quit out instantly if it's not the same
    if(size != c.size)
        return false;

    // Compare entire array side by side
    for(int i = 0; i < size; ++i)
    {
        if(data[i] != c.data[i])
            return false;
    }

    return true;
}

// Just delegate this function over to add
IntCollection&
IntCollection::operator<<(int value)
{
    return add(value);
}


