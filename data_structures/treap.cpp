#include <bits/stdc++.h>
using namespace std;

// Treap / Cartesian Tree

// Insert Complexity: O (log n)
// Delete Complexity: O (log n)

struct node;
vector <node> treap;

struct node {
	int x, y, cnt;
	int l, r;

	node (int _x) {
		x = _x;
		y = abs ((rand() << 16) ^ rand());
		cnt = 1;
		l = -1;
		r = -1;
	}

	void recalc () {
		cnt = 1;
		if (l + 1) cnt += treap[l].cnt;
		if (r + 1) cnt += treap[r].cnt;
	}
};

int merge (int l, int r) {
	if (!(l + 1) || !(r + 1)) return l + 1 ? l : r;
	if (treap[l].y < treap[r].y) {
		treap[l].r = merge (treap[l].r, r);
		treap[l].recalc();
		return l;
	} else {
		treap[r].l = merge (l, treap[r].l);
		treap[r].recalc();
		return r;
	}
}

void split (int v, int x, int & l, int & r) {
	l = -1; r = -1;
	if (!(v + 1)) return;
	if (treap[v].x < x) {
		split (treap[v].r, x, treap[v].r, r);
		l = v;
	} else {
		split (treap[v].l, x, l, treap[v].l);
		r = v;
	}

	treap[v].recalc();
}

int root = -1;

void insert (int x) {
	int l, r;
	split (root, x, l, r);
	treap.push_back (node (x));
	root = merge (merge (l, treap.size() - 1), r);
}

void erase (int x) {
	int l, m, r;
	split (root, x, l, m);
	split (m, x + 1, m, r);
	root = merge (l, r);
}

int getSize() {
	return root + 1 ? treap[root].cnt : 0;
}

int main () {

	srand (time (NULL));
	return 0;
}