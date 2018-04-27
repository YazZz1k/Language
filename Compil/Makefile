SOURCES=test.cpp RDP/RDP.cpp tokenator/tokenator.cpp Tree/Tree.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
CC=g++
CFLAGS=-c
EXECUTABLE=test


$(EXECUTABLE):  tokenator/token_struct.o $(OBJECTS)
	$(CC) $^ -o $@

%.o: %.cpp
	$(CC) -std=c++11 -c $< -o  $@

tokenator/token_struct.o: tokenator/token_struct.cpp
	$(CC) -std=c++11 -c tokenator/token_struct.cpp -o tokenator/token_struct.o
