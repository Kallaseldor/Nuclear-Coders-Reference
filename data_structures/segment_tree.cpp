
// Segment Tree
// Build:	O(n)
// Query:	O(log n)
// Update:	O(log n)

// Memo Complexity: O(n)

const int MAXN = 112345

int st[4 * MAXN];
int v[MAXN];

void build (int nd, int l, int r) {
	if (l == r) {
		st[nd] = v[l];
		return;
	}

	int mid = (l + r) >> 1;
	int nxt = nd << 1;

	build (nxt, l, mid);
	build (nxt + 1, mid + 1, r);

	st[nd] = st[nxt] + st[nxt + 1];
	return;
}

void update (int nd, int l, int r, int pos, int val) {
	if (pos < l || pos > r) return;
	if (l == r) {
		st[nd] = val;
		return;
	}

	int mid = (l + r) >> 1;
	int nxt = nd << 1;

	update (nxt, l, mid, pos, val);
	update (nxt + 1, mid + 1, r, pos, val);

	st[nd] = st[nxt] + st[nxt + 1];
	return;
}

int query (int nd, int l, int r, int ll, int rr) {
	if (rr < l || r < ll) return 0;
	if (ll <= l && r <= rr) return st[nd];

	int mid = (l + r) >> 1;
	int nxt = nd << 1;

	return query (nxt, l, mid, ll, rr) + query (nxt + 1, mid + 1, r, ll, rr);
}
