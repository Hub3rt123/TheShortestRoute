#pragma once
#include <list>
#include "String.h"

struct CityNeighbours;

struct Cities {
	String name;
	int x;
	int y;
	std::list<CityNeighbours> neighbours;
};

struct CityNeighbours {
	Cities* city;
	int distance;
};

class Heap {
	struct Leaf{
		Cities* city;
		int* distance;
	};
	Leaf* leaf;
	int size;
public:
	Heap(Cities* city, int* distance, int size);
	~Heap() { delete[]leaf; }
	void heapify(int index);
	void buildHeap();
	int getSize() const { return size; }
	void removeMin();
	int getMinDistance() const { return *leaf[0].distance; }
	Cities* getMinCity() const { return leaf[0].city; }
	int* getDistance(Cities* city);
	bool isCity(Cities* city) const;
};