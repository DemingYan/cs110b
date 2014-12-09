// IntCollection class header
// CS 110B Max Luttrell
#ifndef INTCOLLECTION_H
#define INTCOLLECTION_H

const int CHUNK_SIZE = 5;	// allocate memory in chunks of ints of this size

class IntCollection
{
private:
    int size;
    int capacity;
    int *data;

public:
  	IntCollection();
	IntCollection(const IntCollection &c);
    ~IntCollection();
    
	IntCollection& add(int value);
	int get(int index) const;
	int getSize() const;

	IntCollection& operator=(const IntCollection &c);
	bool operator==(const IntCollection &c);
	IntCollection& operator<<(int value);
};

#endif /* INTCOLLECTION_H */

