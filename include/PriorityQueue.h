#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <ostream>
#include <vector>
#include <cassert>

template<class T>
class IndexedPriorityQLow {
private:
	std::vector<T>& keys;

	std::vector<int> heap;
	std::vector<int> iheap;

	int size;
	int maxSize;

public:
	IndexedPriorityQLow(std::vector<T>& keys, int maxSize) :
	  keys(keys), maxSize(maxSize), size(0) {
		heap.assign(maxSize+1, 0);
		iheap.assign(maxSize+1, 0);
	}

	bool empty() const { return (size==0); }

	void insert(const int idx) {
		assert (size+1 <= maxSize);
		++size;
		heap[size] = idx;
		iheap[idx] = size;
		reorderUpwards(size);
	}

	int pop() {
		swap(1, size);
		reorderDownwards(1, size-1);
		return heap[size--];
	}

	void changePriority(const int idx) {
		reorderUpwards(iheap[idx]);
	}

	void swap(int a, int b) {
		int temp = heap[a];
		heap[a] = heap[b];
		heap[b] = temp;

		iheap[heap[a]] = a;
		iheap[heap[b]] = b;
	}

	void reorderUpwards(int nd) {
		while ((nd>1) && (keys[heap[nd/2]] > keys[heap[nd]])) {      
			swap(nd/2, nd);
			nd /= 2;
		}
	}

	void reorderDownwards(int nd, int heapSize) {
		while (2*nd <= heapSize) {
			int child = 2 * nd;

			if((child < heapSize) && (keys[heap[child]] > keys[heap[child+1]])) {
				++child;
			}

			if(keys[heap[nd]] > keys[heap[child]]) {
				swap(child, nd);
				nd = child;
			} else {
				break;
			}
		}
	}
};

#endif