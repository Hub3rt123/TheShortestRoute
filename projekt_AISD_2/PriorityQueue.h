#pragma once
#include "Heap.h"

class PriorityQueue {
	Heap heap;
public:
	PriorityQueue(Cities* city, int* distance, int size) : heap(city, distance, size) {}
	bool isEmpty() const { return !(bool(heap.getSize())); }
	void removeMin();
	bool isCity(Cities* city) const { return heap.isCity(city); }
	int getMinDistance() const { return heap.getMinDistance(); }
	Cities* getMinCity() const { return heap.getMinCity(); }
	int* getDistance(Cities* city) { return heap.getDistance(city); }
};