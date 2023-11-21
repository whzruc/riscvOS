#ifndef PQUEUE_H
#define PQUEUE_H


// Define the PriorityQueue structure
typedef struct {
    int *array; // Array to store elements
    int capacity; // Capacity of the array
    int size; // Current size of the queue
} PriorityQueue;


void swap(int *a, int *b);

void heapifyUp(PriorityQueue *pq, int index);
void heapifyDown(PriorityQueue *pq, int index);

PriorityQueue* createPriorityQueue(int capacity);

void insert(PriorityQueue *pq, int value);
int extractMin(PriorityQueue *pq);

void destroyPriorityQueue(PriorityQueue *pq);

#endif