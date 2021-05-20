#ifndef MYVECTOR_H
#define MYVECTOR_H

/**
 * MyVector.h
 * A simple dynamic vector implementation
 **/

#include <iostream>
#include <string>

using namespace std;

template <class T>
class MyVector{
	private:
		T *arr;
		int size;
		int cap;
		void resize(int s);
	public:
		MyVector();
		MyVector(int s);
		~MyVector();
		void print();
		void push(T t);
		T pop();
		int getSize();
		int getCap();
		T operator[](int i);
		bool isEmpty();
		void copy(MyVector<T> *vec);
		void assign(int i, T t);	
};

/**
 * Default constructor
 * Creates an empty vector with capactiy 2
 **/
template <class T>
MyVector<T>::MyVector(){
	arr = new T[2];
	size = 0;
	cap = 2;
}

/**
 * Constructor
 * Creates an empty vector with capacity s
 **/
template <class T>
MyVector<T>::MyVector(int s){
	arr = new T[s];
	size = 0;
	cap = s;
}

/**
 * Overloading of the [] operator
 * Allows user to access items in the vector at index i
 **/
template <class T>
T MyVector<T>::operator[] (const int i){return arr[i];}

/**
 * Modify the vector to be of capacity and copy its previous values
 * @param
 * int s, the new capacity the vector should be
 * @return
 * Nothing
 **/
template <class T>
void MyVector<T>::resize(int s){
	cap = s;
	T *new_arr = new T[cap];
       for(int i = 0; i < size; i++){
		new_arr[i] = arr[i];
       }
	delete [] arr;
	arr = new_arr;
}

/**
 * Adds the template value t to the end of the vector
 * Modifies and resizes the array if its at capacity
 * @param
 * Template value t, the value to add
 * @return
 * Nothing
 **/
template <class T>
void MyVector<T>::push(T t){
	if(size >= cap - 1){
		resize(cap*2);
				
	}
	arr[size++] = t;
	
}

/**
 * Removes the value at the end of the vector
 * Modifies and resizes the array if its less than or equal
 * to half of the vector's capacity
 * @param
 * @return
 * The value at the end of the vector
 **/
template <class T>
T MyVector<T>::pop(){
	if(size < cap/4){
		resize(cap/2);
	}
	return arr[--size];
	
}

/**
 * Gets the size of the vector
 * @param
 * @return
 * An int representing the size of the vector
 **/
template <class T>
int MyVector<T>::getSize(){ return size;}

/**
 * Gets the capacity of the vector
 * @param
 * @return
 * An int representing the capacity of the vector
 **/
template <class T>
int MyVector<T>::getCap(){return cap;}

/**
 * Display the contents of the vector
 * @param
 * @return
 **/
template <class T>
void MyVector<T>::print(){
	cout << "[";
	for(int i = 0; i < size; i++){
		cout << arr[i] << ",";
	}
	cout << "]" << endl;
}

/**
 * Checks if the vector is empty
 * @param
 * @return
 * True if the vector is empty and false otherwise
 **/
template <class T>
bool MyVector<T>::isEmpty(){
	return size == 0;
}

/**
 * Copies the values in vector vec to the current vector
 * Also modifies the size and capacity to match
 * @param
 * MyVector<T> *vec, a pointer to another vector that will be copied
 * @return
 * Nothing
 **/
template <class T>
void MyVector<T>::copy(MyVector<T> *vec){
	for(int i = 0; i < vec->getSize(); i++){
		arr[i] = (*vec)[i];
	}
	size = vec->getSize();
	cap = vec->getCap();
}

/**
 * Assigns the template value t to the index i of the vector
 * @params
 * int i, the index the value will be assigned to
 * Template value t, the value to assign
 * @return
 * Nothing
 **/
template <class T>
void MyVector<T>::assign(int i, T t){
	arr[i] = t;	
}

/**
 * Destructor
 * Frees the allocated memory
 * Sets the size and capacity to zero
 **/
template <class T>
MyVector<T>::~MyVector(){
	delete [] arr;
	arr = NULL;
	size = 0;
	cap = 0;
}

#endif
