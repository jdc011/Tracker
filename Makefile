CXXFLAGS = -g -Wall -std=c++11

list:
	g++ -g Entry.hpp Entry.cpp List.cpp List.hpp LNode.cpp LNode.hpp -o list

clean:
	rm *.gch *.o list
