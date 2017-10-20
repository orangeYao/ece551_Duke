#include "Matrix.h"
#include <assert.h>
#include <iostream>
#include <vector>

template <typename T>
Matrix<T>::Matrix(): numRows(0), numColumns(0), rows(NULL){
}

template <typename T>
Matrix<T>::Matrix(int r, int c): numRows(r), numColumns(c){
    rows = new vector<T> * [numRows]();  
    for (int i=0; i<numRows; i++)
        rows[i] = new vector<T>(numColumns);
}

template <typename T>
Matrix<T>::Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns)  {
    rows = new vector<T> * [numRows]();
    for (int i=0; i<numRows; i++)
        rows[i] = new vector<T>(rhs[i]); // row[i] points to IntAttay
}

template <typename T>
Matrix<T>::~Matrix() {
    for (int i=0; i<numRows; i++)
        delete rows[i]; 
    delete[] rows;
}


template <typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
    if (this == &rhs)
        return *this;

    for (int i=0; i<numRows; i++)
        delete rows[i]; 
    delete[] rows;

    numRows = rhs.numRows;
    numColumns = rhs.numColumns;

    rows = new vector<T> * [numRows]();
    for (int i=0; i<numRows; i++)
        rows[i] = new vector<T>(rhs[i]); // row[i] points to IntAttay

    return *this;
}

template <typename T>
int Matrix<T>::getRows() const {
    return numRows;
}

template <typename T>
int Matrix<T>::getColumns() const {
    return numColumns;
}

template <typename T>
const vector<T> & Matrix<T>::operator[](int index) const {
    assert(index < numRows);
    return *rows[index];
}

template <typename T>
vector<T> & Matrix<T>::operator[](int index){
    assert(index < numRows);
    return *rows[index];
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
    if (numRows != rhs.numRows || numColumns != rhs.numColumns)
        return false;

    for (int i=0; i<numRows; i++)
        if(*rows[i] != *rhs.rows[i])
            return false;

    return true;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
    assert(numRows == rhs.numRows && numColumns == rhs.numColumns);    

    typename Matrix<T>::Matrix cpy = Matrix<T>::Matrix(*this); 

    for (int i=0; i<numRows; i++)
        for (int j=0; j<numColumns; j++)
            (*cpy.rows[i])[j] += (*rhs.rows[i])[j];

    return cpy;
}


template<typename T>
ostream & operator<<(ostream & s, const vector<T> & rhs) {
//    for (typename vector<T>::iterator it = rhs.begin(); it < rhs.end(); ++it)
//        s << *it  << " ";
    s << "{";
    int numC = rhs.size();
    for (int i=0; i<numC; i++)
    {
        s << rhs[i];
        if (i != numC - 1)    
            s << ", ";
    }
    s << "}";
    return s;
}

template<typename T>
ostream & operator<<(ostream & s, const Matrix<T> & rhs) {
    s << "[ ";
    int numR = rhs.getRows();

    for (int i=0; i<numR; i++)
    {
       s << rhs[i]; 
       if (i != numR - 1)
           s << ",\n";
    }
    s << " ]";
    return s;
}


typedef Matrix<int> IntMatrix;

int main(void) {
  IntMatrix a(4,5);
  for (int i = 0; i < a.getRows(); i++) {
    for (int j = 0; j < a.getColumns(); j++) {
      a[i][j] = i+j;
    }
  }
  std::cout << "a is:\n" << a << std::endl;
}


