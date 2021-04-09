#include<iostream>
using namespace std;
template<typename T>
class EnhancedQueue 
{
	T* arr;
	int front;//front of queue
	int rear;//rear of queue
	int size;//size 
	int cap;//capacity
	//utility for circular movement
    inline	int next(int i) 
	{
		return (i+1) % cap;
	}
	//expansion utility
	void expand() 
	{
		T* temp = new T[cap*2];
		for (int i = 0,k=next(front); i < size; i++)
		{
			temp[i+1] = arr[k];//coping except front i.e dead cell
			k = next(k);
		}
		front = 0;
		cap *= 2;
		rear = size;
		delete[]arr;
		arr = temp;
	}
	//contraction
	void shrink() 
	{	
		T* temp = new T[cap / 2];
		for (int i = 0, k = next(front); i < size; i++)
		{
			temp[i + 1] = arr[k];//this will skip dead cell
			k = next(k);
		}
	//updates all attributes
		cap /= 2;
		front = 0;
		rear = size;
		delete[]arr;
		arr = temp;
	}
public:
	//paramertrized
	EnhancedQueue(int n=5) //by default capacity=5
	{
		cap = n;
		size = 0;
		rear=front = 0;//front /rear are at 0
		arr = new T[cap];//capacity
	}
	// enter at first of queue
	void enqueueAtFront(T& obj) 
	{
		if ((front == 0 && rear == cap - 1) || front == rear + 1 || size==cap-1) //rear and front are adjacent in circle
		{
			expand();// if rear is next to front
		}
		//now dummy cell will move one step back and new element will be at free slot
		arr[front] = obj;
		size++;//addition in size of Queue
		if (front == 0) {
			front = cap - 1;
		}else{
			front--;
		}
	}
	//remove from front
	void dequeueAtFront() {
		if (empty())
			return;//includes the case where cap==1
		else {
			//first deque the element
			front = next(front);
			size--;
			if (empty()) {
				delete[] arr;
				arr = nullptr;
				size = 0;
				rear = front = 0;
			}
			//if the number of occupied cells has fallen below cap/2,
			  //halve the array.
			else if (size < cap / 2) {//if less than half storage is used
				shrink();
			}
		}
	}
	//enter at rear
	void enqueueAtRear(T& obj) 
	{
		//is the queue full (physically)
		if (cap == size + 1) {
			expand();
			rear = next(rear);
			arr[rear] = obj;
			size++;
		}
		else {
			//there is a slot available
			rear = next(rear);
			arr[rear] = obj;
			size++;
		}
	}
	//remove from rear
	void dequeueAtRear() 
	{
		if (size == 0)
			return;
		else
		{
			if (size == 1) //after dequeue size will be 0
			{
				delete[]arr;
				size = 0;
				arr = nullptr;
				front = rear = 0;
			}
			else
			{
				if (rear == 0) {
					rear = cap - 1;
					size--;
				}
				else
				{
					rear--;
					size--;
				}
			}
		}
		if (size < cap / 2) 
		{
			shrink();
		}
	}
	T peekFront() 
	{
		return (arr[++front]);
	}
	T peekRear() 
	{
		return (arr[rear]);
	}
	int queue_size() 
	{
		return size;
	}
	bool empty() 
	{
		return(size == 0);
	}
	//debug purpose
	void print() 
	{
		for (int i = 0, k = next(front); i < size; i++)
		{
			if (k != front) {
				cout << arr[k] << " ";
			}
			k = next(k);
		}
	}
	//destructor
	~EnhancedQueue() 
	{
		if (arr != nullptr)
			delete[]arr;
		arr = nullptr;
	}
};

