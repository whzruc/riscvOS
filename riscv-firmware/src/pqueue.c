#include "include/pqueue.h"
#include <stdlib.h>



void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(PriorityQueue *pq, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && pq->array[index] < pq->array[parent]) {
        swap(&pq->array[index], &pq->array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

void heapifyDown(PriorityQueue *pq, int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int smallest = index;

    if (leftChild < pq->size && pq->array[leftChild] < pq->array[smallest])
        smallest = leftChild;

    if (rightChild < pq->size && pq->array[rightChild] < pq->array[smallest])
        smallest = rightChild;

    if (smallest != index) {
        swap(&pq->array[index], &pq->array[smallest]);
        heapifyDown(pq, smallest);
    }
}

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (int*)malloc(sizeof(int) * capacity);
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

void insert(PriorityQueue *pq, int value) {
    if (pq->size == pq->capacity) {
        // printf("PriorityQueue is full. Cannot insert.\n");
        return;
    }

    pq->array[pq->size] = value;
    pq->size++;
    heapifyUp(pq, pq->size - 1);
}

int extractMin(PriorityQueue *pq)
{
    if (pq->size <= 0) {
        // printf("PriorityQueue is empty. Cannot extract minimum.\n");
        return -1;
    }

    int minValue = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);

    return minValue;
}

// void printPriorityQueue(PriorityQueue *pq) {
//     printf("PriorityQueue: ");
//     for (int i = 0; i < pq->size; ++i) {
//         printf("%d ", pq->array[i]);
//     }
//     printf("\n");
// }

void destroyPriorityQueue(PriorityQueue *pq) {
    free(pq->array);
    free(pq);
}