#include "Heap.h"

Heap::Heap(City** city, int* distance, int size, int WIDTH) : WIDTH(WIDTH) {
	leaf = new Leaf[size];
	indexes = new int[size];
	for (int i = 0; i < size; i++) {
		leaf[i].city = city[i];
		leaf[i].distance = &distance[i];
		indexes[i] = i;
	}
	this->size = size;
	buildHeap();
}

Heap::~Heap() {
	delete[]leaf;
	delete[]indexes;
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
		if (leaf[index - 1].city != nullptr)
			indexes[leaf[index - 1].city->y * WIDTH + leaf[index - 1].city->x] = index - 1;
		if (leaf[min - 1].city != nullptr)
			indexes[leaf[min - 1].city->y * WIDTH + leaf[min - 1].city->x] = min - 1;
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
	if (leaf[0].city != nullptr)
		indexes[leaf[0].city->y * WIDTH + leaf[0].city->x] = 0;
	if (leaf[size - 1].city != nullptr)
		indexes[leaf[size - 1].city->y * WIDTH + leaf[size - 1].city->x] = size - 1;
	size--;
}

void Heap::replace(int i) {
	int index = i + 1;
	if (index - 1 > 0 && *leaf[index - 1].distance >= *leaf[index / 2 - 1].distance)
		heapify(index);
	else {
		while (index != 0) {
			heapify(index);
			index = index / 2;
		}
	}
}

bool Heap::changeDistance(City* city, int temp_distance, int distance_2) {
	if (indexes[city->y * WIDTH + city->x] < size) {
		if (*leaf[indexes[city->y * WIDTH + city->x]].distance > temp_distance + distance_2) {
			*leaf[indexes[city->y * WIDTH + city->x]].distance = temp_distance + distance_2;
			replace(indexes[city->y * WIDTH + city->x]);
			return true;
		}
		else
			return false;
	}
	return false;
}