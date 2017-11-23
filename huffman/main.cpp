#include "compress.h"
#include "huffman.h"
#include <cstdio>

using namespace std;

int main() {
    compress::zip("td.txt", "td.dat");
    compress::unzip("td.dat", "tdout.txt");
    return 0;
}
