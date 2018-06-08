#include <bits/stdc++.h>
using namespace std;

// Checks for Q queries if the removal of K edges
// disconnects the graph in time O(N + M + Q * 2^K)

// OBS: There is a trick to change the 2^K to
// polynomial time but I don't know it (unfortunately)

// Edges are 0-indexed
// Vertices are 0-indexed

const int MAXN = 11234;

int n, m;
vector <int> g[MAXN];
vector <int> tr[MAXN];
int pai[MAXN];			// Edge ID with respect to the tree, not the graph
int dist[MAXN];			// Distance to root on the tree

struct Edge {
	int x, y, id;
	bool inTree;
	Edge () { inTree = false; }
	Edge (int _x, int _y, int _id) {
		x = _x; y = _y; id = _id;
		inTree = false;
	}

	int other (int u) const {
		return (x == u) ? y : x;
	}
};

vector <Edge> edges;
vector <long long> eulerianPaths;	// 64 eulerian paths, each in a bit position

void addEdge (int x, int y) {
	g[x].push_back (edges.size());
	g[y].push_back (edges.size());

	edges.push_back (Edge (x, y, edges.size()));
}

bool vis[MAXN];
vector <int> path;

void dfs (int x, int h) {
	vis[x] = true;
	dist[x] = h;

	for (int i = 0; i < g[x].size(); ++i) {
		Edge & e = edges[g[x][i]];
		int y = e.other (x);
		if (vis[y]) continue;

		e.inTree = true;
		tr[x].push_back (e.id);

		pai[y] = e.id;
		dfs (y, h + 1);
	}

	path.push_back (x);

}

long long genRand() {
	long long r1 = rand() << 15;
	r1 ^= rand();

	long long r2 = rand() << 15;
	r2 ^= rand();

	return (r1 << 32LL) ^ r2;
}

long long currVal[MAXN];
bool alwaysYes;
void createTree () {
	dfs (0, 0);

	// Checking if answer is always yes
	alwaysYes = false;
	for (int i = 0; i < n; ++i)
		if (!vis[i]) alwaysYes = true; 

	eulerianPaths.resize (edges.size());

	// Generating random values for edges not on trees
	for (int i = 0; i < m; ++i) {
		const Edge & e = edges[i];
		if (e.inTree) continue;
		
		long long val = genRand();
		eulerianPaths[e.id] ^= val;
		currVal[e.x] ^= val;
		currVal[e.y] ^= val;
	}

	// Propagate random values upwards
	path.pop_back();
	for (int i = 0; i < path.size(); ++i) {
		const int & x = path[i];
		const Edge & e = edges[pai[x]];
		long long val = currVal[x];
		eulerianPaths[e.id] ^= val;
		currVal[e.other (x)] ^= val;
	}

}

vector <int> queryEdges;
int main () {

	srand (time (NULL));

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int a, b;
		scanf ("%d %d", &a, &b);
		addEdge (a - 1, b - 1);
	}

	createTree ();
	
	int q;
	cin >> q; 

	while (q--) {
		int k;
		scanf ("%d", &k);

		queryEdges.clear();
		for (int i = 0; i < k; ++i) {
			int a;
			scanf ("%d", &a);
			queryEdges.push_back (a - 1);
		}

		// Test all subsets of edges in the query
		bool flag = alwaysYes;
		for (int msk = 1; msk < (1 << k); ++msk) {
			if (flag) break;
			long long curr = 0;
			for (int i = 0; i < k; ++i) {
				if (!((1 << i) & msk)) continue;
				curr ^= eulerianPaths[queryEdges[i]];
			}

			if (curr == 0) flag = true;
		}

		if (flag)
			printf ("Disconnected\n");
		else
			printf ("Connected\n");
	}

	return 0;
}
