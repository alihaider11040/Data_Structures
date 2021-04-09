class Invertible_stack {
	int top;//top of stack
	int cap;//capacity
	T* arr;
	bool inverted;//decides FIFO/LIFO behavior
	int front;//start of stack
	int size;
	///////////////////////////utilities/////////////////////////
	inline int next(int i) {
		return (i + 1) % cap;
	}
	void expand() {
		T* temp = new T[cap * 2];
		for (int i = 0, k = front; i < size; i++)
		{
			temp[i] = arr[k];
			k = next(k);
		}
		front = 0;
		cap *= 2;
		top = size;
		delete[]arr;
		arr = temp;
	}
	void shrink() {
		T* temp = new T[cap / 2];
		for (int i = 0, k = front; i < size; i++)
		{
			temp[i] = arr[k];
			k = next(k);
		}
		front = 0;
		cap /= 2;
		top = size;
		delete[]arr;
		arr = temp;
	}
private:
	//additional utilities for invertible stack
	//push/pop survices only to be used by member functions
	void push_At_Top(const T& obj)
	{
		//is the queue full (physically)
		if (cap == size + 1) {
			expand();
			
			arr[top] = obj;
			top = next(top);
			size++;
		}
		else {
			//there is a slot available
			
			arr[top] = obj;
			top = next(top);
			size++;
		}
	}
	void push_At_Start(const T& obj)
	{
		if ((front == 0 && top == cap - 1) || front == top + 1 || size == cap - 1) //rear and front are adjacent in circle
		{
			expand();// if rear is next to front
		}
		if (top == front) {
			arr[front] = obj;
		}
		else
		{
			if (front == 0) {
				front = cap - 1;
				arr[front] = obj;
			}
			else
			{
				front--;
				arr[front] = obj;
			}
		}
		size++;
	}
	void pop_Top()
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
				front = 0;
			}
			else
			{
				if (top == 0) {
					top = cap - 1;
					size--;
				}
				else
				{
					top--;
					size--;
				}
			}
		}
		if (size < cap / 2)
		{
			shrink();
		}
	}
	void pop_Start() {
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
				front = 0;
			}
			//if the number of occupied cells has fallen below cap/2,
			  //halve the array.
			else if (size < cap / 2) {//if less than half storage is used
				shrink();
			}
		}
	}
public:
	stack(int i=2) {
		arr = new T[i];
		size = 0;
		cap = i;
		front = 0;
		top = 0;
		inverted = false;
	}
	stack(const stack& obj)
	{
		top = obj.top;
		cap = obj.cap;
		size = obj.size;
		inverted = obj.inverted;
		front = 0;
		obj.stack_ptr = new T[cap];
		for (int i = obj.front,k=0; k < size;k++)
		{
			arr[k] = obj.arr[i];
			i = next(i);
		}
	}
	//flip_stack method 
	void flip_Stack() 
	{
		if (inverted == false) {
			inverted = true;
		}
		else
		{
			inverted = false;
		}
		
	}
	void push(const T& obj) {
		if (inverted == false) 
		{
			push_At_Top(obj);
		}
		else
		{
			push_At_Start(obj);
		}
	}
	void pop() {
		if (inverted == false) {
			pop_Top();
		}
		else
		{
			pop_Start();
		}
	}
	bool empty() {
		return size ==0;
	}
	T peek() {
		if (inverted == true) {
			return arr[front];
		}
		return  arr[top];
	}
	//destructor
	~stack()
	{
		if (arr != nullptr)
			delete[]arr;
		arr = nullptr;
	}
	//Debug & checking pruposes
	void print() {
		for (int i = 0,k=front; i < size; i++)
		{
			cout << arr[k] << " ";
			k = next(k);
		}
	}
};
