#pragma once
#include <iostream>
#include <stack>
using namespace std;
template <typename T>
class LinkedList {
private:
	struct Node {
		T data;
		Node* next;//pointer to next node

		Node(const T& d, Node* nptr = nullptr) {
			data = d;//assumes operator is available
			next = nptr;
		}

		Node() {
			next = nullptr;
		}

	};

	Node* head, * tail;
	int size;
public:
	LinkedList();
	LinkedList(const LinkedList& obj);
	bool empty();
	//Use for push
	void insertAtHead(const T& obj);
	void insertAtTail(const T& obj);
	void insertInOrder(const T& obj);
	void eraseAtHead();
	void eraseAtTail();
	//
	void operator =(LinkedList& obj);
	//testing
	void print();
	void eraseAtKey(const T& key);
	~LinkedList();

};
