CXX = g++
CXXFLAGS = -Wall -std=c++11
OBJECTS = LinkedList.o bard.o

bard: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o bard LinkedList.o bard.o

LinkedList.o: LinkedList.h LinkedList.cpp
	$(CXX) -g $(CXXFLAGS) -c LinkedList.cpp

bard.o: LinkedList.cpp LinkedList.h bard.cpp
	$(CXX) -g $(CXXFLAGS) -c bard.cpp

.PHONY: clean
clean:
	rm -f *.o
	rm bard