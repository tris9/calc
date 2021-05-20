#ifndef MYSTACK_H
#define MYSTACK_H

#include "MyVector.h"

/**
 * MyStack.h
 * A simple stack implemented with a vector
 **/

template <class T>
class MyStack{
	private:
		MyVector<T> stack;
	public:
		MyStack();
		~MyStack();
		void push(T t);
		T pop();
		bool isEmpty();
		void print();
		int getSize();
		T peek();
};

/**
 * Default constructor
 * Creates an empty stack
 **/
template <class T>
MyStack<T>::MyStack(){
}

/**
 * Adds the template value t to the top of the stack
 * @param
 * The template value t to be added to the top of the stack
 * @return
 **/
template <class T>
void MyStack<T>::push(T t){
	stack.push(t);
}

/**
 * Removes the value t from the top of the stack
 * @param
 * @return
 * The value at the top of the stack
 **/
template <class T>
T MyStack<T>::pop(){
	if(isEmpty()){	//Make sure we dont pop off an empty stack
		return stack[0];
	}
	return stack.pop();
}

/**
 * Check if the stack is empty
 * @param
 * @return
 * True if the stack is empty and false otherwise
 **/
template <class T>
bool MyStack<T>::isEmpty(){
	return stack.getSize() == 0;
}

/**
 * Display the contents of the stack
 * @param
 * @return
 **/
template <class T>
void MyStack<T>::print(){
	stack.print();
}

/**
 * Get the size of the stack
 * @param
 * @return
 * An int representing the size of the stack
 **/
template <class T>
int MyStack<T>::getSize(){
	return stack.getSize();
}

/**
 * Look at the top of the stack without modifying it
 **/
template <class T>
T MyStack<T>::peek(){
	return stack[getSize()-1];
}

/**
 * Destructor
 * Handled by the MyVector class
 **/
template <class T>
MyStack<T>::~MyStack(){	
}

#endif
