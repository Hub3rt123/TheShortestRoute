#pragma once

template <typename T>
class Queue {
	struct Node {
		T item;
		Node* next;
	};
	Node* first;
	Node* last;
public:
	Queue() : first(nullptr), last(nullptr) {}
	~Queue();
	void push(T item);
	T front();
	void pop();
	bool empty() const;
};

template <typename T>
Queue<T>::~Queue() {
	while (first != nullptr) {
		Node* temp = first;
		first = first->next;
		delete temp;
	}
};

template <typename T>
void Queue<T>::push(T item) {
	Node* temp = new Node;
	temp->item = item;
	temp->next = nullptr;
	if (last == nullptr) {
		last = temp;
		first = temp;
	}
	else {
		last->next = temp;
		last = temp;
	}
}

template <typename T>
T Queue<T>::front() {
	return first->item;
}

template <typename T>
void Queue<T>::pop() {
	if (first != nullptr) {
		Node* temp = first;
		first = first->next;
		delete temp;
		if (first == nullptr)
			last = nullptr;
	}
}

template <typename T>
bool Queue<T>::empty() const {
	if (first == nullptr)
		return true;
	else
		return false;
}