#pragma once
#include <iostream>
#include "../domain/domain.h"

typedef Tutorial TElem;
//class DynamicVector
//{
//private:
//    int size;
//    int capacity;
//    TElem* elements;
//    static const unsigned int DEFAULT_CAPACITY = 10;
//
//    void resize(double factor = 2);
//
//public:
//    // constructors and destructor
//    DynamicVector();
//    DynamicVector(unsigned int initialCapacity = 2);
//    DynamicVector(const DynamicVector& v);
//    ~DynamicVector();
//
//    // Overloading the [] operator
//    TElem &operator[](int pos);
//
//    // Adds an element to the current DynamicVector.
//    void add(TElem e);
//
//    // Deletes an element from a given position
//    void delete_elem(unsigned int pos);
//
//    // Returns all elements
//    TElem* get_all_elems() const;
//
//    // Returns the size of the dynamic vector
//    int getSize() const;
//};

template <class T>
class DynamicVector
{
private:
    T* elements;
    int size;
    int capacity;
    static const unsigned int DEFAULT_CAPACITY = 10;

    // Resizes the current DynamicVector, multiplying its capacity by a given factor (real number).
    void resize(double factor = 2);

public:
    // constructors and destructor
    DynamicVector();
    DynamicVector(unsigned int initialCapacity);
    DynamicVector(const DynamicVector& v);
    ~DynamicVector();

    // Overloading the [] operator
    T &operator[](int pos);

    // + operator
    DynamicVector<T>& operator+(const T& classObj);

    // Adds an element to the current DynamicVector.
    void add(T e);

    // Deletes an element from a given position
    void delete_elem(unsigned int pos);

    // Returns all elements
    T* get_all_elems() const;

    // Returns the size of the dynamic vector
    int getSize();
};

template<class T>
inline DynamicVector<T>::DynamicVector()
{
    capacity = DEFAULT_CAPACITY;
    size = 0;
    elements = new T[DEFAULT_CAPACITY];

}

template<class T>
DynamicVector<T>::DynamicVector(unsigned int initial_capacity)
{
    elements = new T[initial_capacity];
    size = 0;
    capacity = initial_capacity;
}

template<class T>
DynamicVector<T>::DynamicVector(const DynamicVector<T> &v)
{
    this->size = v.size;
    this->capacity = v.capacity;
    this->elements = new T[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        this->elements[i] = v.elements[i];
    }
}

template<class T>
DynamicVector<T>::~DynamicVector()
{
    delete[] elements;
}


template<class T>
T &DynamicVector<T>::operator[](int pos) {
    return this->elements[pos];  //return array element
}

template<class T>
void DynamicVector<T>::add(T e) {
    if(this->size == this->capacity)
        this->resize();

    this->elements[this->size] = e;
    this->size++;
}

template<class T>
void DynamicVector<T>::resize(double factor) {
    this->capacity *= static_cast<int>(factor);

    T * aux = new T[this->capacity];
    for (int i = 0; i < this->size; ++i) {
        aux[i] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = aux;
}

template<class T>
void DynamicVector<T>::delete_elem(unsigned int pos) {
    if (pos < 0 || pos >= this->size)
        return;

    T* aux = new T[this->capacity];
    for (int i = 0; i < pos; ++i) {
        aux[i] = this->elements[i];
    }

    for (int i = pos + 1; i < this->size; ++i) {
        aux[i - 1] = this->elements[i];
    }
    delete[] this->elements;
    this->elements = aux;
    this->size--;
}

template<class T>
T *DynamicVector<T>::get_all_elems() const {
    return this->elements;
}

template<class T>
int DynamicVector<T>::getSize() {
    return this->size;
}

template <class T>
DynamicVector<T>& DynamicVector<T>::operator+(const T& classObj) {
    this->add(classObj);
    return *this;
}
