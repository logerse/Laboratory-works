#ifndef MALLOC_H
#define MALLOC_H
#include <malloc.h>
#endif

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

template<typename T>
class Vector {
private:
	size_t size;
	size_t capasity;

	T *array;
public:
	Vector(size_t, const T&);
	~Vector(void);

	T& at(size_t) const;
	T& Insert(size_t i, const T value);
	T  Erase(size_t i);
	T operator[] (const int) const;

	size_t Size(void) const {return size;};
	void ListAll(void);
	void PushBack(const T& value);
};



template<typename T>
Vector<T>::Vector(size_t sz, const T& value)
{
        if(sz <= 0) {
                std::cerr << "Incorrect size of vector. Size should be greater than 0." << std::endl;
                throw "Incorrect initialization size.";
        };

        size = 0;
        capasity = sz;

        array = (T *) malloc(sz * sizeof(T));
        this->PushBack(value);
};


template<typename T>
Vector<T>::~Vector(void)
{
        free(array);
};



#define DELTA 10
template<typename T>
void Vector<T>::PushBack(const T& val) {
	size++;

	if(size >= capasity) {
		capasity = size + DELTA;
		array = (T*) realloc(array, capasity * sizeof(T));
	};

	array[size - 1] = val;
};


template<typename T>
T Vector<T>::operator[] (const int indx) const {
	return at(indx);
};



template<typename T>
T& Vector<T>::at(size_t indx) const {
	if(indx > size || indx < 0) {
		std::cerr << "Incorrect index of element. [0 <= Index < " << size << "]." << std::endl;
		throw "Incorrect index";
	};
	return array[indx];
};



template<typename T>
T& Vector<T>::Insert(size_t i, const T value) {
	size++;
	this->at(i) = value;
	return this->at(i);
};



template<typename T>
T Vector<T>::Erase(size_t i) {
	size--;
	T val = this->at(i);
	this->at(i) = 0;
	return val;
}; 



template<typename T>
void Vector<T>::ListAll(void) {
	std::cout << "[Size: " << this->Size() << "] ";
	for(int i=0; i<Size(); i++) {
		std::cout << at(i) << " ";
	};
	std::cout << std::endl;
};
