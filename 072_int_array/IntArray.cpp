#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray(): data(NULL), numElements(0) {

}
IntArray::IntArray(int n): numElements(n) {
    data = new int[numElements] ();
}

IntArray::IntArray(const IntArray & rhs): numElements(rhs.numElements) {
    data = new int[numElements] ();
    for (int i=0; i<numElements; i++)
        data[i] = rhs.data[i];
}

IntArray::~IntArray() {
    delete [] data;
    data = NULL;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
    if (this == &rhs)
        return *this;

    numElements = rhs.numElements;
    delete [] data;

    data = new int[numElements] ();
    for (int i=0; i<numElements; i++)
        data[i] = rhs.data[i];

    return *this;
}

const int & IntArray::operator[](int index) const {
    return data[index];
}

int & IntArray::operator[](int index) {
    return data[index];
}

int IntArray::size() const {
    return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
    if (numElements != rhs.numElements)
        return false;
    
    for (int i=0; i<numElements; i++)
        if (data[i] != rhs.data[i])
            return false;

    return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
    return !(*this == rhs);
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
    s << "{";
    int size = rhs.size();
    for (int i=0; i<size; i++)
    {
        s << rhs[i]; 
        if (i != size - 1)
            s << ", ";
    }
    s << "}";
    return s;
}

