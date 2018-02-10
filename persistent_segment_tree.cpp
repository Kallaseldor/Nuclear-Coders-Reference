const int MAXN = 112345;

int root[MAXN];
int tr[50 * MAXN], L[50 * MAXN], R[50 * MAXN];
int cnt = 1;

void build(int no, int l, int r) {
	tr[no] = 0;
	L[no] = cnt++;
	R[no] = cnt++;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(L[no], l, mid);
	build(R[no], mid + 1, r);
}

int update(int no, int l, int r, int pos, int val) {
	int clone = cnt++;
	int mid = (l + r) >> 1;
	tr[clone] = tr[no] + val;
	L[clone] = L[no];
	R[clone] = R[no];

	if (l == r) return clone;

	if (pos <= mid) {
		L[clone] = update(L[clone], l, mid, pos, val);
	} else {
		R[clone] = update(R[clone], mid + 1, r, pos, val);
	}

	return clone;
}

int query(int no, int l, int r, int i, int j) {
	if (r < i || j < l) return 0;
	if (i <= l && r <= j) return tr[no];
	int mid = (l + r) >> 1;
	return query(L[no], l, mid, i, j) + query(R[no], mid + 1, r, i, j);
}
