CXX = g++
CXX-FLAGS = -std=c++11 -Wall
OBJECTS = main.o

main: $(OBJECTS)
	$(CXX) $(CXX-FLAGS) -o main $(OBJECTS)

main.o: 
	$(CXX) $(CXX-FLAGS) -c -o main.o main.cpp

.PHONY: clean
clean:
	-rm main $(OBJECTS)
