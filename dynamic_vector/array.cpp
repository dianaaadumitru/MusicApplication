//
//#include "array.h"
//
////inline DynamicVector::DynamicVector() {
////    capacity = DEFAULT_CAPACITY;
////    size = 0;
////    elements = new TElem[DEFAULT_CAPACITY];
////}
//
//DynamicVector::DynamicVector(unsigned int initial_capacity)
/////constructor
//{
//    elements = new TElem[initial_capacity];
//    size = 0;
//    capacity = initial_capacity;
//}
//
//DynamicVector::DynamicVector(const DynamicVector &v)
/////constructor
//{
//    this->size = v.size;
//    this->capacity = v.capacity;
//    this->elements = new TElem[this->capacity];
//    for (int i = 0; i < this->size; ++i) {
//        this->elements[i] = v.elements[i];
//    }
//}
//
//DynamicVector::~DynamicVector()
/////destructor
//{
//    delete[] elements;
//}
//
//TElem &DynamicVector::operator[](int pos)
///// Overloading the [] operator
//{
//    return this->elements[pos];  //return array element
//}
//
//void DynamicVector::add(TElem e)
///// Adds an element to the current DynamicVector
//{
//    if(this->size == this->capacity)
//        this->resize();
//
//    this->elements[this->size] = e;
//    this->size++;
//}
//
//void DynamicVector::resize(double factor)
//
//{
//    this->capacity *= factor;
//    TElem * aux = new TElem[this->capacity];
//    for (int i = 0; i < this->size; ++i) {
//        aux[i] = this->elements[i];
//    }
//    delete[] this->elements;
//    this->elements = aux;
//}
//
//void DynamicVector::delete_elem(unsigned int pos)
///// Deletes an element from a given position
//{
//    if (pos < 0 || pos >= this->size)
//        return;
//
//    TElem* aux = new TElem[this->capacity];
//    for (int i = 0; i < pos; ++i) {
//        aux[i] = this->elements[i];
//    }
//
//    for (int i = pos + 1; i < this->size; ++i) {
//        aux[i - 1] = this->elements[i];
//    }
//    delete[] this->elements;
//    this->elements = aux;
//    this->size--;
//}
//
//TElem *DynamicVector::get_all_elems() const
///// Returns all elements
//{
//    return this->elements;
//}
//
//int DynamicVector::getSize() const
///// Returns the size of the dynamic vector
//{
//    return this->size;
//}
//
//
//
