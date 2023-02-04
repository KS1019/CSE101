CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = sixdegrees.o

sixdegrees: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees sixdegrees.o

sixdegrees.o: sixdegrees.cpp
	$(CXX) -g $(CXXFLAGS) -c sixdegrees.cpp

.PHONY: clean test-simple test-more

clean: 
	rm -f *.o sixdegrees

test-simple: sixdegrees
	timeout 3m ./sixdegrees simple-input.txt output.txt && diff output.txt simple-output.txt

test-more: sixdegrees
	timeout 3m ./sixdegrees Tests/more-input.txt output.txt && diff output.txt Tests/more-output.txt