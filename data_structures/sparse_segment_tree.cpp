const int MAXN = 112345;

int st[60 * MAXN];
int L[60 * MAXN];
int R[60 * MAXN];

int root[MAXN];

int cnt = 0;

inline void create (int & nd) {
	if (! (nd + 1))
		nd = cnt++;
}

void update (int & nd, int l, int r, int pos, int val) {
	create (nd);
	st[nd] = max (st[nd], val);

	if (l == r) return;
	int mid = (l + r) >> 1;

	if (pos <= mid)
		update (L[nd], l, mid, pos, val);
	else
		update (R[nd], mid + 1, r, pos, val);
}

int query (int nd, int l, int r, int ll, int rr) {
	if (nd == -1) return 0;
	if (rr < l || r < ll) return 0;
	if (ll <= l && r <= rr) return st[nd];

	int mid = (l + r) >> 1;
	return max (query (L[nd], l, mid, ll, rr), query (R[nd], mid + 1, r, ll, rr));
}