#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

//YOUR CODE GOES HERE!
template <typename T>
class Matrix {

  private: 
    int numRows;
    int numColumns;
    vector<T> * rows;

  public:
    Matrix();

    Matrix(int r, int c);

    Matrix(const Matrix<T> & rhs);

    ~Matrix();

    Matrix<T> &operator=(const Matrix<T> & rhs); 

    int getRows() const;

    int getColumns() const;

    const vector<T> & operator[](int index) const; 

    vector<T> & operator[](int index);

    bool operator==(const Matrix<T> & rhs) const;

    Matrix operator+(const Matrix<T> & rhs) const;
};

template<typename T>
ostream & operator<<(ostream & s, const vector<T> & rhs);

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs);


#endif
