#include <math.h>
#include "min_heap.h"


// * * * * * start of min heap * * * * //

// Create a node
struct node* createNode(int v) {
  struct node* newNode = malloc(sizeof(struct node*));
  newNode->vertex = v;
  newNode->distance = INFINITY;
	newNode->next = NULL;
  return newNode;
}

/*
* Initialises the binary min heap
*/
void init_heap(heap *heap, int numVertices){
	heap -> size = 0;
	int i;
	int len = numVertices;
	for(i = 1; i <= len; i++){
		struct node* newNode = createNode(i);
		heap -> data[i-1] = newNode;
	}
}

/*
* Creates the heap data structure
* @param heap Heap datastructure
* @param s The array  to build a heap from
* @param n the size of the s array
*/
void build_heap(heap *heap, node * s[], int n){
	int i; //counter
	//initialize the heap
	init_heap(heap, n);
	//insert the elements into the heap
	for(i = 0; i < n; i++){
		insert(heap,s[i]);
	}
}

/*
* Prints the content of the heap
*/
void print_heap(heap *heap){
	int i;
	int heapSize = heap -> size;

	for(i = 1; i <= heapSize; i++){
		printf("Item[%d]: vertex: %i , distance: %f \n", i, heap -> data[i]->vertex, heap -> data[i]->distance);
	}
}

/*
* Returns the minimum item from the heap
* @param heap Heap datastructure
* @return minItem
*/
node * peek(heap *heap){
	return heap -> data[1];
}

//returns the index of the parent (if any) of the index n
int get_parent(int n){
	return n == 1 ? -1 : (int)(n/2);

}
//returns the index of the younger child
int young_child(int n){
	return 2*n;
}

/*
* Removes and returns the minimum item from the heap
* @param heap Heap datastructure
* @return minItem
*/
node * extract_min(heap *heap){
	node * min = NULL;

	if(heap -> size <= 0)
		printf("Warning: Empty heap!");

	else{
		//the root is the minimum element
		min = heap -> data[1];
		//replace the element at the top with last element in the heap
		heap -> data[1] = heap -> data[heap -> size];
		//reduce the total elements in the heap
		heap -> size -= 1;
		bubble_down(heap,1);
	}
	return min;
}

//bubbles down an element into it's proper place in the heap
void bubble_down(heap *heap, int p){
	int c; //child index
	int i; //counter
	int min_index; //index of lightest child

	c = young_child(p);
	min_index = p;

	for(i = 0; i < 2; i++){
		if(c + i <= heap -> size){
			//check to see if the data at min_index is larger than the data at the child
			if(heap -> data[min_index]->distance > heap -> data[c+i]->distance){
				min_index = c + i;
			}
		}
	}

	if(min_index != p){
		//swap the elements
		node * temp_variable = heap -> data[p];
		heap -> data[p] = heap -> data[min_index];
		heap -> data[min_index] = temp_variable;
		//call bubble down
		bubble_down(heap, min_index);
	}
}

//bubbles up the last element of the heap to maintain heap structure
void bubble_up(heap *heap, int index){
	//if we are at the root of the heap, no parent
	if(get_parent(index) == -1)
		return;

	//if the parent node has a larger data value, we need to bubble up
	if(heap->data[get_parent(index)]->distance > heap->data[index]->distance){
		//swap the elements
		node * temp_variable = heap -> data[get_parent(index)];
		heap -> data[get_parent(index)] = heap -> data[index];
		heap -> data[index] = temp_variable;
		//call the bubble up function to the new parent
		bubble_up(heap, get_parent(index));
	}
}

void insert(heap *heap, node *x){
	//if the heap is already full
	if(heap -> size >= HEAP_CAPACITY)
		printf("Warning: Heap overflow capacity!\n");

	else{
		//increment the number of elements in the heap
		heap -> size += 1;
		//insert the data value into the left most position in the heap
		heap -> data[heap -> size] = x;
		//put in appropriate position by bubbling up
		bubble_up(heap, heap -> size);

	}
}

/*
* Decreases the distance value of the key
* @param heap Heap datastructure
* @param index key value
* @param new_val new value to replace the distance
*/
void decrease_key(heap *heap, int key, double new_val){
	int index;
	for (int i = 0; i < heap->size; i++)
	{
		if(heap->data[i]->vertex == key){
			index = i;
		}
	}
	heap->data[index]->distance = new_val;
	bubble_up(heap, index);
}


/*
* Check the heap contains a key
* @param heap Heap datastructure
* @param index key value
*/
int contains(heap *heap, int key){
	for (int i = 0; i < heap->size; i++)
	{
		if(heap->data[i]->vertex == key){
			return 1;
		}
	}
	return 0;
}

// * * * * * * Graph  * * * * * * //
// A structure to represent an adjacency list node


// A structure to represent an adjacency list
struct AdjList
{
    struct node *head;
};

// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices
// in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

// A utility function to create a new adjacency list node
struct node* newAdjListNode(int vertex)
{
    struct node* newNode =
     (struct node*) malloc(sizeof(struct node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph =
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V+1;

    // Create an array of adjacency lists.  Size of
    // array will be V
    graph->array =
      (struct AdjList*) malloc((V+1) * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by
    // making head as NULL
    int i;
    for (i = 0; i <= V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest, double dist)
{
    // Add an edge from src to dest.  A new node is
    // added to the adjacency list of src.  The node
    // is added at the beginning
    struct node* newNode = newAdjListNode(dest);
    newNode->distance = dist;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
}

// A utility function to print the adjacency list
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct node* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->vertex);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

// * * * * *  read the graph * * * *//
/*
* Load the graph from market matrix file
*/
void loadGraph(struct Graph** graph, int *nofVerticies, char ** argv){
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_n = 0;
  FILE *input;
  input = fopen(argv[1], "r");
  if (input == NULL) exit(EXIT_FAILURE);
  while ((read = getline(&line, &len, input)) != -1) {
    if (*line == '%'){
      continue;
    }
    int num1, num3;
		double num2;
		char *str1 = strtok(line, " \t\v\f\r"), *str3 = strtok(NULL, " \t\v\f\r") , *str2 = strtok(NULL, " \t\v\f\r")  ;
		if(str1 != NULL && str2 != NULL && str3 != NULL ){
				num1 = atoi( str1 );
				num2 = atof(str2);
				num3 = atoi( str3 );
			} else{
        continue;
      }
    if(line_n == 0){
      *nofVerticies = num1 ;
      //*nofEdges = num2 ;
      *graph = createGraph(*nofVerticies);
		}else{
      addEdge(*graph, num1, num3, num2);
		}
		line_n += 1 ;
  }
}

// * * * * dijkstra * * * * //
double * dijkstra(struct Graph* graph, int s) {
  int nofVertices = graph->V;
	// distance array to keep track of distance from s to d
	double *distance = malloc(sizeof(double) * nofVertices);
	int visited[nofVertices];
	for (int i = 0; i < nofVertices; i++)
	{
		distance[i] = INFINITY;
		visited[i] = 0;
	}
	distance[s-1] = 0;
	// priority queue
	heap *min_heap = malloc(sizeof(heap));
	init_heap(min_heap, nofVertices);
	struct node * newNode = createNode(s);
	newNode->distance = 0.0;
	insert(min_heap, newNode);
	while (min_heap->size > 0)
	{
		struct node * current = extract_min(min_heap);
		int index = current->vertex;
		visited[index-1] = 1;
		double newDist;
		//if(distance[index] < current->distance) continue;
		struct node * temp = graph->array[index].head;;
    while (temp) {
			if (visited[temp->vertex-1] == 0)
			{
				newDist = distance[index-1] + temp->distance;
				if (newDist < distance[temp->vertex-1])
				{
					distance[temp->vertex-1] = newDist;
					if(contains(min_heap, temp->vertex)){
						decrease_key(min_heap, temp->vertex, newDist);
					} else {
						struct node * newNode = createNode(temp->vertex);
						newNode->distance = newDist;
						insert(min_heap, newNode);
					}
				}
			}
      temp = temp->next;
    }
	}
	return distance;
}

// * * * * program * * * *//


int main(int argc, char ** argv){
	// read the .mtx file
  if(argc != 2) return 0;
  struct Graph* graph;
  int nofVertices;
	// prepare the adjacency matrix
  loadGraph(&graph, &nofVertices, argv);
  //printGraph(graph);

	double *distance = dijkstra(graph, 1);
	// write result to the file
	FILE * fp;
	fp = fopen("a.txt", "w+");
	double dist;
	for (int i = 1; i <= nofVertices; i++)
	{
		dist = distance[i-1];
		if(dist == INFINITY){
			fprintf(fp,"%i\n", -1);
		}else {
			fprintf(fp,"%0.8lf\n", dist);
		}
	}
	fclose(fp);

	return 0;
}
