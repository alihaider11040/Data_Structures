#pragma once
#include <iostream>
using namespace std;


template <typename T>
class stack {
private:
	int top;
	int capacity;
	T* ptr;
public:
	stack() {//default constructor
	    top = -1;
		capacity = 0;
		ptr = NULL;
	}
	stack(const stack& obj){//copy constructor
		top = obj.top;
		capacity = obj.capacity;
		ptr = new T[capacity];
		for (int i = 0; i < top; i++)
{
			ptr[i] = obj.ptr[i];
		}
	}
	void push(const T& obj) {
		if (top == -1) {
			ptr = new T[1];
			capacity++;
			ptr[++top] = obj;
		}
		else if (top == capacity - 1) {
			capacity *= 2;
			T* temp = new T[capacity]; // 2 , 4 , 8 , 16
			for (int i = 0; i <= top; i++) {
				temp[i] = ptr[i];
			}
			temp[++top] = obj;
			delete[] ptr;
			ptr = temp;
		}
		else {
			ptr[++top] = obj;
		}
	}
	void pop() {
		if (top >= 0) {
			if (top == 0) {
				top = -1;
				capacity = 0;
				delete[] ptr;
				ptr = NULL;
			}
			else if (top >= (capacity / 2 - 1)) {
				top--;
			}
			else {
				capacity /= 2;
				T* temp = new T[capacity];
				for (int i = 0; i <size(); i++) {
					temp[i] = ptr[i];
				}
				delete[] ptr;
				ptr = temp;
				top--;
			}
		}
	}
	bool empty() {
		return top == -1;
	}
	inline int size() {
		return (top + 1);
	}
	T peek() {
		return ptr[top];
	}
	//operator
	stack& operator =(const stack& obj)
	{
		capacity = obj.capacity;
		top = obj.top;
		ptr = new T[capacity];
		for (int i = 0; i < top; i++)
		{
			ptr[i] = obj.ptr[i];
		}
		return *this;
	}
	//destructor
	~stack()
	{
		if (ptr != nullptr)
			delete[]ptr;
		ptr = nullptr;
	}
	//debug
	void print() {
		for (int i = 0; i < size(); i++)
		{
			cout << ptr[i] << " ";
		}
	}
};



