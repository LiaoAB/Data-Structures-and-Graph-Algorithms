// C++ program for Kruskal's algorithm to find Minimum
// Spanning Tree of a given connected, undirected and
// weighted graph
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Structure to represent a graph
struct Graph
{
	int V, E;
	vector<pair<int, pair<int, int> > > edges;

	// Constructor
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}

	// Utility function to add an edge
	void addEdge(int u, int v, int w)
	{
		edges.push_back(std::make_pair(w, std::make_pair(u, v)));
	}

	// Function to find MST using Kruskal's algorithm
	int kruskalMST();
};

// To represent Disjoint Sets
struct DisjointSets
{
	int *parent, *rank;
	int n;

	// Constructor.
	DisjointSets(int n)
	{
		// Allocate memory
		this->n = n;
		parent = new int[n + 1];
		rank = new int[n + 1];

		// Initially, all vertices are in
		// different sets and have rank 0.
		for (int i = 0; i <= n; i++)
		{
			rank[i] = 0;

			// every element is parent of itself
			parent[i] = i;
		}
	}

	// Find the parent of a node 'j'
	// Path Compression
	int find(int j)
	{
		/* Make the parent of the nodes in the path
		from u--> parent[u] point to parent[u] */
		if (j != parent[j])
			parent[j] = find(parent[j]);
		return parent[j];
	}

	// Union by rank
	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		/* Make tree with smaller height
		a subtree of the other tree */
		if (rank[x] > rank[y])
			parent[y] = x;
		else // If rank[x] <= rank[y]
			parent[x] = y;

		if (rank[x] == rank[y])
			rank[y]++;
	}
};

/* Functions returns weight of the MST*/

int Graph::kruskalMST()
{
	int mst_wt = 0; // Initialize result

	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());

	// Create disjoint sets
	DisjointSets ds(V);

	// Iterate through all sorted edges
	vector<pair<int, pair<int, int> > >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;

		int set_u = ds.find(u);
		int set_v = ds.find(v);

		// Check if the selected edge is creating
		// a cycle or not (Cycle is created if u
		// and v belong to same set)
		if (set_u != set_v)
		{
			// Current edge will be in the MST
			// so print it
			cout << u << " - " << v << endl;

			// Update MST weight
			mst_wt += it->first;

			// Merge two sets
			ds.merge(set_u, set_v);
		}
	}

	return mst_wt;
}

int main()
{	
	int row, col, position, value;
	cout << "Enter weighted graph matrix: " << endl;
	cin >> row >> col;
	Graph g(row, col*col);
	for(int i = 0; i < row; i++){
		while(cin >> position && position != 0 && position <= col){
			cin >> value;
			g.addEdge(i, position, value);
		}
		if(position > col){
			cout << "Invalid position" << endl;
            return 0;
		}
	}

	cout << "Edges of MST are \n";
	int mst_wt = g.kruskalMST();

	cout << "\nWeight of MST is " << mst_wt << endl;

	return 0;
}