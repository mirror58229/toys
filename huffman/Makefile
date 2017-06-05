CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

main: compress.o huffman.o main.o
	$(CXX) $(CXXFLAGS) -o main main.o huffman.o

main.o: huffman.h
	$(CXX) $(CXXFLAGS) -c -o main.o main.cpp

huffman.o: huffman.h
	$(CXX) $(CXXFLAGS) -c -o huffman.o huffman.cpp

compress.o: compress.h
	$(CXX) $(CXXFLAGS) -c -o compress.o compress.cpp

clean:
	-rm -rf *.o *.gch
