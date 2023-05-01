#include "List.h"

List<City*>::~List() {
	while (first != nullptr) {
		Node* temp = first;
		first = first->next;
		delete temp;
	}
};

void List<City*>::push_back(City* item) {
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

City* List<City*>::find(String& str) {
	Node* temp = first;
	while (temp != nullptr) {
		if (temp->item->name == str)
			return temp->item;
		else
			temp = temp->next;
	}
	return nullptr;
}

bool List<City*>::empty() const {
	if (first == nullptr)
		return true;
	else
		return false;
}
