#pragma once
#include "String.h"

struct CityNeighbours;

template <typename T>
class List {
	struct Node {
		T item;
		Node* next;
	};
	Node* first;
	Node* last;
	Node* current_node;
public:
	List() : first(nullptr), last(nullptr), current_node(nullptr) {}
	~List();
	void push_back(T item);
	bool empty() const;
	T* getItem();
};

template <typename T>
List<T>::~List() {
	while (first != nullptr) {
		Node* temp = first;
		first = first->next;
		delete temp;
	}
};

template <typename T>
void List<T>::push_back(T item) {
	Node* temp = new Node;
	temp->item = item;
	temp->next = nullptr;
	if (last == nullptr) {
		last = temp;
		first = temp;
		current_node = temp;
	}
	else {
		last->next = temp;
		last = temp;
	}
}

template <typename T>
bool List<T>::empty() const {
	if (first == nullptr)
		return true;
	else
		return false;
}

template <typename T>
T* List<T>::getItem() {
	if (current_node == nullptr) {
		current_node = first;
		return nullptr;
	}
	else {
		Node* temp = current_node;
		current_node = current_node->next;
		return &(temp->item);
	} 
}

struct City {
	String name;
	int x;
	int y;
	List<CityNeighbours> neighbours;
};

struct CityNeighbours {
	City* city;
	int distance;
};


//specjalizacja dla T = City*
template <>
class List<City*> {
	struct Node {
		City* item;
		Node* next;
	};
	Node* first;
	Node* last;
public:
	List() : first(nullptr), last(nullptr) {}
	~List();
	void push_back(City* item);
	City* find(String& str);
	bool empty() const;
};

