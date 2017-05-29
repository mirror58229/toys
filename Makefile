CXX = g++
CXX-FLAGS = -std=c++1y -Wall
OBJECTS = main.o

main: $(OBJECTS)
	$(CXX) $(CXX-FLAGS) -o main $(OBJECTS)

main.o:

.PHONY: clean
clean:
	-rm main $(OBJECTS)
