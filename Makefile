CXXFLAGS = -g -Wall -std=c++11

list:
	g++ -g Entry.cpp List.cpp LNode.cpp -o list

clean:
	rm *.gch *.o list
	clear
