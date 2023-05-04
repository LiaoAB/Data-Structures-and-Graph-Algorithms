#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <string>
using namespace std;

// Data structure to store a graph edge
struct Edge {
	int source, dest, weight;
};

// Data structure to store a heap node
struct Node {
	int vertex, weight;
};

// A class to represent a graph object
class Graph
{
public:
	// a vector of vectors of `Edge` to represent an adjacency list
	vector<vector<Edge>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const &edges, int n)
	{
		// resize the vector to hold `n` elements of type vector<Edge>
		adjList.resize(n);

		// add edges to the directed graph
		for (Edge const &edge: edges)
		{
			// insert at the end
			adjList[edge.source].push_back(edge);
		}
	}
};

// Data structure to store a PriorityQueue
class PriorityQueue {
  public:
    vector<Node> heap;
    unordered_map<int, int> vertexToHeap;

    bool Empty();
    int LeftChild(int index);
    int RightChild(int index);
    int Parent(int index);

    void Swap(int a, int b);

    void BubbleUp(int index);
    void BubbleDown(int index);
    void DecreaseKey(int vertex, int newWeight);
    
    void Insert(Node n);
    Node Front();
    Node Pop();
};

bool PriorityQueue::Empty() {
  return heap.empty();
}

int PriorityQueue::LeftChild(int index) {
  return 2 * index + 1;
}

int PriorityQueue::RightChild(int index) {
  return 2 * index + 2;
}

int PriorityQueue::Parent(int index) {
  return (index - 1) / 2;
}

void PriorityQueue::Swap(int a, int b) {
  Node _a = heap[a];
  Node _b = heap[b];
  heap[b] = _a;
  heap[a] = _b;
  vertexToHeap[_a.vertex] = b;
  vertexToHeap[_b.vertex] = a;
}

void PriorityQueue::BubbleUp(int index) {
  if (index == 0) return; // Edge case is the root.
  int p = Parent(index);
  if (heap[p].weight > heap[index].weight) {
    Swap(p, index);
    BubbleUp(p);
  }
}

void PriorityQueue::BubbleDown(int index) {
  int n = heap.size();
  int left  = LeftChild(index);
  int right = RightChild(index);
  int min;
  if (right > n)
    if (left > n) return;
    else min = left;
  else
    min = (heap[left].weight > heap[right].weight) ? left : right;

  if (heap[index].weight > heap[min].weight) {
    Swap(index, min);
    BubbleDown(min);
  }
}

void PriorityQueue::Insert(Node n) {
  heap.push_back(n);
  vertexToHeap[n.vertex] = heap.size() - 1;
  BubbleUp(heap.size() - 1);
}

Node PriorityQueue::Front() {
  return heap[0];
}

Node PriorityQueue::Pop() {
  Node tmp = heap[0];
  heap[0] = heap[heap.size() - 1];
  heap.pop_back();
  vertexToHeap[tmp.vertex] = -1;
  vertexToHeap[heap[0].vertex] = 0;
  if (heap.size() > 0)
    BubbleDown(0);

  return tmp;
}

void printPath(vector<int> const &prev, int i, int source)
{
	if (i < 0) {
		return;
	}
	printPath(prev, prev[i], source);
	if (i != source) {
		cout << ", ";
	}
	cout << i;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(const Node &lhs, const Node &rhs) const {
		return lhs.weight > rhs.weight;
	}
};

// Run Dijkstra’s algorithm on the given graph
void findShortestPaths(Graph const &graph, int source, int n)
{
	// create a min-heap and push source node having distance 0
	PriorityQueue min_heap;
	min_heap.Insert({source, 0});

	// set initial distance from the source to `v` as infinity
	vector<int> dist(n, INT_MAX);

	// distance from the source to itself is zero
	dist[source] = 0;

	// boolean array to track vertices for which minimum
	// cost is already found
	vector<bool> done(n, false);
	done[source] = true;

	// stores predecessor of a vertex (to a print path)
	vector<int> prev(n, -1);

	// run till min-heap is empty
	while (!min_heap.Empty())
	{
		// Remove and return the best vertex
		Node node = min_heap.Front();
		min_heap.Pop();

		// get the vertex number
		int u = node.vertex;

		// do for each neighbor `v` of `u`
		for (auto i: graph.adjList[u])
		{
			int v = i.dest;
			int weight = i.weight;

			// Relaxation step
			if (!done[v] && (dist[u] + weight) < dist[v])
			{
				dist[v] = dist[u] + weight;
				prev[v] = u;
				min_heap.Insert({v, dist[v]});
			}
		}

		// mark vertex `u` as done so it will not get picked up again
		done[u] = true;
	}

	for (int i = 0; i < n; i++)
	{
		if (i != source && dist[i] != INT_MAX)
		{
			cout << "Path (" << source << " —> " << i << "): Minimum cost = "
				 << dist[i] << ", Route = [";
			printPath(prev, i, source);
			cout << "]" << endl;
		}
	}
}

int main()
{
	// initialize edges as per the above diagram
	// (u, v, w) represent edge from vertex `u` to vertex `v` having weight `w`
	vector<Edge> edges = {};
	int row, col, position, value;
	cout << "Enter weighted graph matrix: " << endl;
	cin >> row >> col;
	for(int i = 0; i < row; i++){
		while(cin >> position && position != 0 && position <= col){
			cin >> value;
			edges.push_back({i, position, value});
		}
		if(position > col){
			cout << "Invalid position" << endl;
            return 0;
		}
	}

	// total number of nodes in the graph (labelled from 0 to 4)

	// construct graph
	Graph graph(edges, row + 1 );

	// run the Dijkstra’s algorithm from every node
	for (int source = 0; source < row + 1; source++) {
		findShortestPaths(graph, source, row + 1);
	}

	return 0;
}
