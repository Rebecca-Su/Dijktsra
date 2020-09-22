all: undirectedGraphdriver
  
undirectedGraphdriver: undirectedGraph.cpp undirectedGraph.h undirectedGraphtest.cpp
	g++ -std=c++11 -o undirectedGraphdriver undirectedGraphtest.cpp undirectedGraph.cpp

clean:
	rm -f undirectedGraphdriver
