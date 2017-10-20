//#include "vector.cpp"
#include <assert.h>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

template<typename T>

class Matrix {

 private:
  int numRows;
  int numColumns;
  vector<T> ** rows;

 public:

    Matrix(): numRows(0), numColumns(0), rows(NULL){
    }

    Matrix(int r, int c): numRows(r), numColumns(c){
        rows = new vector<T> * [numRows]();  
        for (int i=0; i<numRows; i++)
            rows[i] = new vector<T>(numColumns);
    }

    Matrix(const Matrix & rhs): numRows(rhs.numRows), numColumns(rhs.numColumns)  {
        rows = new vector<T> * [numRows]();
        for (int i=0; i<numRows; i++)
            rows[i] = new vector<T>(rhs[i]); // row[i] points to IntAttay
    }

    ~Matrix() {
        for (int i=0; i<numRows; i++)
            delete rows[i]; 
        delete[] rows;
    }


    Matrix &operator=(const Matrix & rhs) {
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

    int getRows() const {
        return numRows;
    }

    int getColumns() const {
        return numColumns;
    }

    const vector<T> & operator[](int index) const {
        assert(index < numRows);
        return *rows[index];
    }

    vector<T> & operator[](int index){
        assert(index < numRows);
        return *rows[index];
    }

    bool operator==(const Matrix & rhs) const {
        if (numRows != rhs.numRows || numColumns != rhs.numColumns)
            return false;

        for (int i=0; i<numRows; i++)
            if(*rows[i] != *rhs.rows[i])
                return false;

        return true;
    }

    Matrix operator+(const Matrix & rhs) const {
        assert(numRows == rhs.numRows && numColumns == rhs.numColumns);    

        Matrix cpy = Matrix(*this); 

        for (int i=0; i<numRows; i++)
            for (int j=0; j<numColumns; j++)
                (*cpy.rows[i])[j] += (*rhs.rows[i])[j];

        return cpy;
    }

};

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

