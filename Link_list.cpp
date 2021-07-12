#include"Link_list.h"
template<typename T>
LinkedList<T>::LinkedList() {//create an empty list
	head = tail = nullptr;
	size = 0;
}
template<typename T>
bool LinkedList<T>::empty()
{
	return size == 0;
}
//Use for push
template<typename T>
void LinkedList<T>::insertAtHead(const T& obj) {
	if (size == 0) {
		head = new Node(obj);
		tail = head;
	}
	else {

		head = new Node(obj, head);//next points to???
	}
	size++;

}
template<typename T>
void LinkedList<T>::insertAtTail(const T& obj) {

	if (size == 0) {
		tail = new Node(obj);
		head = tail;
	}
	else {
		tail->next = new Node(obj);
		tail = tail->next;
	}
	size++;
}
template<typename T>
void LinkedList<T>::insertInOrder(const T& obj) {

	if (size == 0)
		insertAtHead(obj);
	else if (size == 1) {
		Node* prev = head, * current = head->next;
		if (obj <= prev->data) {
			insertAtHead(obj);
		}
		else
		{
			insertAtTail(obj);
		}
	}
	else {
		Node* curr = head->next, * prev = head;
		if (obj <= curr->data) {
			insertAtHead(obj);//smallest key at the start
		}
		else if (tail->data <= obj) {
			insertAtTail(obj);//largest key at the end
		}
		else {
			//insert somewhere inside the the list
			Node* temp = new Node(obj);
			while (curr != nullptr && curr->data <= obj) {
				prev = curr;//prev is one step behind curr
				curr = curr->next;
			}
			//connect temp
			prev->next = temp;
			temp->next = curr;
			size++;
			// temp-->curr
		}

	}
}
template<typename T>
void LinkedList<T>::eraseAtHead() {
	if (size > 0) {//O(1)
		Node* temp = head->next;
		if (size == 1)
			head = tail;
		delete head;
		head = temp;
		size--;
	}
}
template<typename T>
void LinkedList<T>::eraseAtTail() {
	if (size > 0) {

		Node* ptail = head;//pointing to first node

		while (ptail->next != tail)//O(n)
			ptail = ptail->next;


		delete tail;
		ptail->next = nullptr;
		tail = ptail;

		size--;
	}
}
//testing
template<typename T>
void LinkedList<T>:: print() {
	Node* curr = head;
	while (curr != nullptr) {
		cout << (curr->data) << " ";
		//curr is a 4-byte address of a node
		curr = curr->next; //(*curr).next
	}
}
template<typename T>
void LinkedList<T>:: eraseAtKey(const T& key) {
	if (size > 0) {

		if (size != 1) {
			Node* prev = head, curr = head->next;//curr cannot be null
			while (curr != nullptr && curr->data != key) {
				prev = curr;
				curr = curr->next;
			}

			if (curr != nullptr) {
				//curr is not nullptr, also, prev is not null

				if (curr == tail)
					tail = prev;
				prev->next = curr->next;
				delete curr;
				size--;
			}
		}
		else
		{
			if (key == head->data) {
				delete head;
				size--;
				head = tail = nullptr;
			}
		}
	}
}
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& obj) {

	this->~LinkedList();
	Node* ptr = obj.head;
	for (int i = 0; i < obj.size; i++)
	{
		this->insertAtTail(ptr->data);
		ptr = ptr->next;
	}
	head = obj.head;
	tail = obj.tail;
}

template<typename T>
void LinkedList<T>:: operator =(LinkedList<T>& obj) {
	this->~LinkedList();
	Node* ptr = obj.head;
	for (int i = 0; i < obj.size; i++)
	{
		this->insertAtTail(ptr->data);
		ptr = ptr->next;
	}
	head = obj.head;
	tail = obj.tail;
}
template<typename T>
LinkedList<T>:: ~LinkedList() {
	stack<Node*> lnodes;

	Node* curr = head;

	while (curr != nullptr) {
		lnodes.push(curr);
	}

	while (!lnodes.empty()) {
		delete lnodes.top();
		lnodes.pop();
	}
}
