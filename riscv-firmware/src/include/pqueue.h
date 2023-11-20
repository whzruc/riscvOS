#ifndef PQUEUE_H
#define PQUEUE_H


// Define the PriorityQueue structure
typedef struct {
    int *array; // Array to store elements
    int capacity; // Capacity of the array
    int size; // Current size of the queue
} PriorityQueue;


#endif