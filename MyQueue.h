#ifndef MYQUEUE_H
#define MYQUEUE_H

#include "MyVector.h"

/**
 * MyQueue.h
 *
 * A simple FIFO queue implemented with a vector
 **/

template <class T>
class MyQueue{
	private:
		MyVector<T> queue;
		int front;
	public:
		MyQueue();
		~MyQueue();
		void push(T t);
		T pop();
		bool isEmpty();
		void print();
		int getSize();
		void resize();
		T peek();
};

/**
 * Default constructor
 * Creates an empty queue
 **/
template <class T>
MyQueue<T>::MyQueue(){
	front = 0;
}

/**
 * Adds value t to the back of the queue
 * @param
 * template value t, the value added
 * @return
 * Nothing 
 **/
template <class T>
void MyQueue<T>::push(T t){
	queue.push(t);
}

/**
 * Removes the value at the front of the queue
 * @param
 * @return
 * The removed value
 **/
template <class T>
T MyQueue<T>::pop(){
	if(isEmpty()){	//if the queue is empty return a garbage value
		return queue[front];
	}else{
		T temp = queue[front++];
		if(getSize() <= front){	//if our queue gets small enough, resize down to save space
			resize();
		}
		return temp;
	}
}

/**
 * Checks if the queue is empty
 * @param
 * @return
 * true if the queue is empty and false otherwise
 **/
template <class T> 
bool MyQueue<T>::isEmpty(){
	return front == queue.getSize();
}

/**
 * Display the contents of the queue
 * @param
 * @return
 **/
template <class T>
void MyQueue<T>::print(){
	cout << "[";
	for(int i = front; i < queue.getSize(); i++){
		cout << queue[i] << ",";
	}
	cout << "]" << endl;
}

/**
 * Gets the size of the queue
 * @param
 * @return
 * An int representing the queue size
 **/
template <class T>
int MyQueue<T>::getSize(){
	return queue.getSize() - front;
}

/**
 * Modifies the current queue to start from the beginning
 * @param
 * @return
 **/
template <class T>
void MyQueue<T>::resize(){
	MyVector<T> *new_vec = new MyVector<T>();
	for(int i = front; i < queue.getSize(); i++){	//copy values to new queue
		new_vec->push(queue[i]);
	}

	queue.copy(new_vec);	//assign old queue to the new queue
	front = 0;

	//free the memory
	delete new_vec;
	new_vec = NULL;
}

/**
 * Shows the value at the front of the queue without modifying it
 * @param
 * @return
 * The value at the front of the queue
 **/
template <class T>
T MyQueue<T>::peek(){
	return queue[front];
}

/**
 * Destructor
 * Handled completely by the MyVector class
 **/
template <class T>
MyQueue<T>::~MyQueue(){
}

#endif
