
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: Battleship

Battleship: $(OBJECTS)
	$(CXX) -g -Wall $(OBJECTS) -o $@

.cpp.o:
	$(CXX) -g -Wall -c $< -o $@

clean:
	rm -f Battleship
	rm -f $(OBJECTS)

