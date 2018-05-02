SOURCES=main.cpp Compil/RDP/RDP.cpp Compil/tokenator/token_struct.cpp Compil/tokenator/tokenator.cpp Compil/Tree/Tree.cpp Compil/Converter/Converter.cpp Compil/Pre_Convert/Pre_Convert.cpp Compil/Compiler/Compiler.cpp Processor/Processor.cpp Processor/Stack/stack.cpp
OBJECTS=$(SOURCES:.cpp=.o) 
CC=g++
CFLAGS=-c
EXECUTABLE=kir--


$(EXECUTABLE):  $(OBJECTS)
	$(CC)  -g $^ -o $@

%.o: %.cpp
	$(CC) -g -std=c++11 -c $< -o  $@

tokenator/token_struct.o: tokenator/token_struct.cpp
	$(CC) -std=c++11 -c tokenator/token_struct.cpp -o tokenator/token_struct.o

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS) print_DOT
