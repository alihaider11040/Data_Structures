#pragma once
#include <iostream>
using namespace std;
template <typename T>
class queue {//class template for circular queue
private:
	T* arr;//pointer to be allocated
	int cap;//physical size
	int size;//logical size
	int front, rear;

	int next(int i) {//utility function
		return (i + 1) % cap;//cap=5
	}

public:
	//next time
	queue(int icap = 0) {
		if (icap > 0) {
			arr = new T[icap + 1];
			cap = icap;
		}
		else {//default behaviour
			arr = nullptr;
			cap = 0;
		}
		size = 0;
		front = rear = 0;//dead cell
	}
	//copy constructor
	queue(const queue& obj){
		arr = new T[obj.cap];
		size = obj.size;
		front = obj.front;
		cap = obj.cap;
		for (int i = 0, k = front; i < size + 1; i++)
		{
			arr[k] = obj.arr[k];
			k = next(k);
		}
	}
	void enqueue(const T& obj) {
		//is the queue full (physically)
		if (cap == size + 1) {
			//array is full, so grow it
			T* temp = new T[cap * 2];
			//copy data from the older array
			int k = 0, i = next(front);
			while (k < size) {
				temp[k + 1] = arr[i];
				i = next(i);
				k++;
			}
			//how to change front and rear values?
			front = 0;//dead cell
			rear = size;
			rear++;
			temp[rear] = obj;
			cap *= 2;
			size++;
			delete[] arr;
			arr = temp;
		}
		else if (cap == 0) {
			//what should we do?
			arr = new T[2];
			front = 0;
			rear = 1;
			arr[1] = obj;
			size = 1;
			cap = 2;
		}
		else {
			//there is a slot available
			rear = next(rear);
			arr[rear] = obj;
			size++;
		}
	}
	void dequeue() {
		if (empty())
			return;
		if ((size + 1) == cap / 2)
		{
			//dequeue and shrink the array
			T* temp = new T[cap / 2];
			for (int i = 0, k = next(front); i < size; i++)
			{
				temp[i + 1] = arr[k];
				k = next(k);
				rear = i + 1;//rear is at recent entry in temp;
			}
			delete[]arr;
			arr = temp;
			cap = cap / 2;
			front = 0;//at begining of queue
				//deque method
			front = next(front);
			size--;
		}
		else {
			front = next(front);
			size--;
		}
	}
	void printQueue() {
		for (int i = 0, k = next(front); i < size; i++)
		{
			cout << arr[k] << " ";
			k = next(k);
		}
	}
	const T& peek() {//read only reference
		return arr[next(front)];
	}
	bool empty() {
		return size == 0;
	}
	int getSize() {
		return size;
	}
	//destructor
	~queue(){
		if (arr != nullptr)
			delete[]arr;
		arr = nullptr;
	}
};

