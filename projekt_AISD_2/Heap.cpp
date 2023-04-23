#include "Heap.h"

Heap::Heap(Cities* city, int* distance, int size) {
	leaf = new Leaf[size];
	for (int i = 0; i < size; i++) {
		leaf[i].city = &city[i];
		leaf[i].distance = &distance[i];
	}
	this->size = size;
	buildHeap();
}

void Heap::heapify(int index) {
	int L = index * 2;
	int R = index * 2 + 1;
	int min;
	if (L <= size && *leaf[L - 1].distance < *leaf[index - 1].distance)
		min = L;
	else
		min = index;
	if (R <= size && *leaf[R - 1].distance < *leaf[min - 1].distance)
		min = R;
	if (min != index) {
		Leaf temp = leaf[index - 1];
		leaf[index - 1] = leaf[min - 1];
		leaf[min - 1] = temp;
		heapify(min);
	}
}

void Heap::buildHeap() {
	for (int i = size; i > 0; i--) {
		heapify(i);
	}
}

void Heap::removeMin() {
	Leaf temp = leaf[0];
	leaf[0] = leaf[size - 1];
	leaf[size - 1] = temp;
	size--;
}

int* Heap::getDistance(Cities* city) {
	for (int i = 0; i < size; i++) {
		if (leaf[i].city->name == city->name)
			return leaf[i].distance;
	}
	
}

bool Heap::isCity(Cities* city) const {
	for (int i = 0; i < size; i++) {
		if (leaf[i].city->name == city->name)
			return true;
	}
	return false;
}