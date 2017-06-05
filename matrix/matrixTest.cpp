#include <iostream>
#include "matrix.hpp"

using namespace std;

int main() {
    matrix<double> mat(4, 4);
    for(int i = 1; i <= mat.getRow(); ++i) {
        for(int j = 1; j <= mat.getCol(); ++j) {
            mat(i, j) = 1;
        }
    }

    auto tp2 = mat;
    tp2 *= 3;
    for(int i = 1; i <= tp2.getRow(); ++i) {
        for(int j = 1; j <= tp2.getCol(); ++j) {
            printf("%f ", tp2(i, j));
        }
        puts("");
    }
    return 0;
}
