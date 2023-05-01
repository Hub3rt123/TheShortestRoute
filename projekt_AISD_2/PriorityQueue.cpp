#include "PriorityQueue.h"

void PriorityQueue::removeMin() {
	heap.removeMin();
	heap.heapify(1);
}