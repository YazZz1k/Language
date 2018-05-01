SOURCES=test.cpp RDP/RDP.cpp tokenator/token_struct.cpp tokenator/tokenator.cpp Tree/Tree.cpp Converter/Converter.cpp Pre_Convert/Pre_Convert.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
CC=g++
CFLAGS=-c
EXECUTABLE=test


$(EXECUTABLE):  tokenator/token_struct.o $(OBJECTS)
	$(CC)  -g $^ -o $@

%.o: %.cpp
	$(CC) -g -std=c++11 -c $< -o  $@

tokenator/token_struct.o: tokenator/token_struct.cpp
	$(CC) -std=c++11 -c tokenator/token_struct.cpp -o tokenator/token_struct.o

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) print_DOT
