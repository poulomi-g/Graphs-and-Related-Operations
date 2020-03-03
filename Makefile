CC=g++
CFLAGS=-c -Wall -O2 -std=c++11
LFLAGS=
PROGS= digraph_test digraph_builder reachability breadthfirstsearch depthfirstsearch
OBJS= digraph.o graph_concepts.o digraph_test.o 

# executable targets
all: graph_concepts

graph_concepts: graph_concepts.o digraph.o
	$(CC) graph_concepts.o digraph.o -o graph_concepts $(LFLAGS)

# object targets
graph_concepts.o: graph_concepts.cpp digraph.h
	$(CC) graph_concepts.cpp -o graph_concepts.o $(CFLAGS)

digraph.o: digraph.cpp digraph.h
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)

clean:
	@rm $(OBJS) $(PROGS)
