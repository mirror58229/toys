#ifndef _MATRIX_H
#define _MATRIX_H

#include "matrix.hpp"
#include <cstdlib>
#include <cstdio>

template<typename T>
class matrix {
public:
    matrix(int row, int col);
    matrix(const matrix& rhs);

    ~matrix();
    
    const matrix<T>& operator=(const matrix<T>& rhs);
    matrix<T> operator+(const matrix<T>& rhs) const;
    const matrix<T>& operator+=(const matrix<T>& rhs);
    matrix<T> operator-(const matrix<T>& rhs) const;
    const matrix<T>& operator-=(const matrix<T>& rhs);
    matrix<T> operator*(int k) const;
    const matrix<T>& operator*=(int k);

    T& operator()(int row, int col);

    int getRow() const {
        return row;
    }

    int getCol() const {
        return col;
    }

private:
    T** data = nullptr;
    int row;
    int col;
};

template<typename T>
matrix<T>::matrix(int row, int col) {
    this->row = row;
    this->col = col;
    data = (T**)malloc(row * sizeof(T*));
    T* tmp = (T*)malloc(row * col * sizeof(T));
    
    for(int i = 0; i != row; ++i) {
        data[i] = tmp + i * col;
    }
}

template<typename T>
matrix<T>::matrix(const matrix& rhs) {
    matrix(rhs.row, rhs.col);
    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            data[i][j] = rhs.data[i][j];
        }
    }
}

template<typename T>
matrix<T>::~matrix() {
    free(data[0]);
    free(data);
}

template<typename T>
const matrix<T>& matrix<T>::operator=(const matrix<T>& rhs) {
    if(row != rhs.row || col != rhs.col) {
        this->~matrix();
        this->row = rhs.row;
        this->col = rhs.col;
        data = (T**)malloc(row * sizeof(T*));
        T* tmp = (T*)malloc(row * col * sizeof(T));
        for(int i = 0; i != row; ++i) {
            data[i] = tmp + i * col;
        }
    }
    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            data[i][j] = rhs.data[i][j];
        }
    }
    return *this;
}

template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& rhs) const {
    matrix<T> mat(*this);
    mat += rhs;
    return mat;
}

template<typename T>
const matrix<T>& matrix<T>::operator+=(const matrix<T>& rhs) {
    if(this->row != rhs.row || this->col != rhs.col) {
        fprintf(stderr, "not match in add function!\n");
        throw 0;
    }

    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            data[i][j] += rhs.data[i][j];
        }
    }
    return *this;
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& rhs) const {
    matrix<T> mat(*this);
    mat += rhs;
    return mat;
}

template<typename T>
const matrix<T>& matrix<T>::operator-=(const matrix<T>& rhs) {
    if(this->row != rhs.row || this->col != rhs.col) {
        fprintf(stderr, "not match in minus function!\n");
        throw 0;
    }

    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            data[i][j] -= rhs.data[i][j];
        }
    }
    return *this;
}

template<typename T>
matrix<T> matrix<T>::operator*(int k) const {
    matrix<T> mat(*this);
    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            mat.data[i][j] *= k;
        }
    }
    return mat;
}

template<typename T>
const matrix<T>& matrix<T>::operator*=(int k) {
    for(int i = 0; i != row; ++i) {
        for(int j = 0; j != col; ++j) {
            data[i][j] *= k;
        }
    }
    return *this;
}

template<typename T>
T& matrix<T>::operator()(int row, int col) {
    if(row <= 0 || row > this->row || col <= 0 || col > this->col) {
        fprintf(stderr, "get element operator out of bound!\n");
        throw 0;
    }

    return data[row - 1][col - 1];
}

#endif
