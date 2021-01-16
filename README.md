# **Dijkstra**

## **Description** :checkered_flag:

* C Implementation of Dijkstra's shortest path algorithm.
* Programming assignment II of Bilkent University CS473/573 Course.

### **Content**

* `assignment2.pdf`: Programming assignment description for the partA and partB problems.
* `max_heap.h`: .h file for the max heap.
* `min_heap.h`: .h file for the min heap.
* `partA.c`: Dijkstra with min-priority queue for computing compute weakness values of the least weak paths from a given source vertex to all other vertices.
* `partB.c`: Dijkstra with max-priority queue for computing success probabilities of most reliable paths between a given source vertex and all other vertices.
* `Makefile`: The makefile to automate the compilation process.
* `assignment2_data`: Folder containing The Matrix Market (.mtx) files to test the Dijkstra implementations.

### **Program**

Compilation and running the program:

```
> make # Generates a binary executable files called A and B
> ./A input graph.mtx # Produces an output file called a.txt
> ./B input graph.mtx # Produces an output file called b.txt
```

The Matrix Market (.mtx) format for storing a directed, weighted graph:

```
% Comment lines
50 50 230 % #Vertices #Vertices #Edges
1 3 0.5 % Source Destination Weight
3 5 0.4
...
```

The program output:

```
0.0 % Distance from vertex 1 to vertex 1
0.8 % Distance from vertex 1 to vertex 2
0.6 % Distance from vertex 1 to vertex 3
-1 % No path from vertex 1 to vertex 4
0.7
...
```

