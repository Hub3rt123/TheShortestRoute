#pragma once
#include "List.h"

class Heap {
	struct Leaf{
		City* city;
		int* distance;
	};
	Leaf* leaf;
	int* indexes;
	int size;
	int WIDTH;
public:
	Heap(City** city, int* distance, int size, int WIDTH);
	~Heap();
	void heapify(int index);
	void buildHeap();
	int getSize() const { return size; }
	void removeMin();
	int getMinDistance() const { return *leaf[0].distance; }
	City* getMinCity() const { return leaf[0].city; }
	void replace(int i);
	bool changeDistance(City* city, int temp_distance, int distance_2);
};