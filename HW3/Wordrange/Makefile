CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = BST.o wordrange.o

wordrange: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o wordrange BST.o wordrange.o

BST.o: BST.h BST.cpp
	$(CXX) -g $(CXXFLAGS) -c BST.cpp

wordrange.o: wordrange.cpp BST.h BST.cpp
	$(CXX) -g $(CXXFLAGS) -c wordrange.cpp

.PHONY: clean test-simple test-basic test-more

clean: 
	rm -f *.o wordrange

test-simple: wordrange
	timeout 3m ./wordrange Tests/simple-input.txt output.txt && diff output.txt Tests/simple-output.txt

test-basic: wordrange
	timeout 3m ./wordrange Tests/allwords-basic.txt output.txt && diff output.txt Tests/allwords-basic-output.txt

test-more: wordrange
	date
	timeout 10m ./wordrange Tests/allwords-more-range.txt output.txt && diff output.txt Tests/allwords-more-range-output.txt
	date