#ifndef MAX_HEAP_H
#define MAX_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// initial heap capacity
#define HEAP_CAPACITY 1000000

//node item stored in the heap
typedef struct node{
	int vertex; // node index
	double distance; //distance to the node from source
  struct node* next; // to used by adj graph
}node;

//building a min-heap
typedef struct heap{
	struct node* data[HEAP_CAPACITY + 1]; //the body of the heap
	int size; //the size of the heap
}heap;

struct node* createNode(int v);
void insert(heap *heap, node *x);
void init_heap(heap *heap, int numVertices);
void build_heap(heap *heap, node *s[], int n);
void print_heap(heap *heap);
node * peek(heap *heap);
int get_parent(int n);
int young_child(int n);
node * extract_max(heap *heap);
void bubble_up(heap *heap, int total_elements);
void bubble_down(heap *heap, int index);
void increase_key(heap *heap, int key, double new_val);
int contains(heap *heap, int key);

#endif /* MAX_HEAP_H */