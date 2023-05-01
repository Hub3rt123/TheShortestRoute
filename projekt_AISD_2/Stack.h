#pragma once

template <typename T>
class Stack {
	struct Node {
		T item;
		Node* next;
		Node* previous;
	};
	Node* first;
	Node* last;
public:
	Stack() : first(nullptr), last(nullptr) {}
	~Stack();
	T top();
	void pop();
	void push(T item);
	bool empty() const;
};

template <typename T>
Stack<T>::~Stack() {
	while (first != nullptr) {
		Node* temp = first;
		first = first->next;
		delete temp;
	}
};

template <typename T>
T Stack<T>::top() {
	return last->item;
}

template <typename T>
void Stack<T>::pop() {
	if (first != nullptr) {
		if (first == last) {
			delete first;
			first = nullptr;
			last == nullptr;
		}
		else {
			Node* temp = last;
			last = last->previous;
			last->next = nullptr;
		}
	}
}

template <typename T>
void Stack<T>::push(T item) {
	Node* temp = new Node;
	temp->item = item;
	temp->next = nullptr;
	if (first == nullptr) first = temp;
	else last->next = temp;
	temp->previous = last;
	last = temp;

}

template <typename T>
bool Stack<T>::empty() const {
	if (first == nullptr)
		return true;
	else
		return false;
}