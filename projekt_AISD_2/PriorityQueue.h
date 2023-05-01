#pragma once
#include "Heap.h"

class PriorityQueue {
	Heap heap;
public:
	PriorityQueue(City** city, int* distance, int size, int WIDTH) : heap(city, distance, size, WIDTH) {}
	bool isEmpty() const { return !(bool(heap.getSize())); }
	void removeMin();
	int getMinDistance() const { return heap.getMinDistance(); }
	City* getMinCity() const { return heap.getMinCity(); }
	void replace(int i) { heap.replace(i); }
	bool changeDistance(City* city, int temp_distance, int distance_2) { return heap.changeDistance(city, temp_distance, distance_2); }
};