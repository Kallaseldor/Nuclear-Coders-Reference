// Longest Increasing Subsequence (LIS)
// Time Complexity: O(n log n)
// Memo Complexity: O(n)

const int MAXN = 112345;

int v[MAXN], tail[MAXN], prev[MAXN];

int findIndex (int l, int r, int key) {
	while (r - l > 1) {
		int mid = l + (r - l) / 2;
		if (v[tail[mid]] >= key)
			r = mid;
		else
			l = mid;
	}
	return r;
}

int lis (int n) {
	if (n == 0) return 0;

	memset (tail, 0, sizeof tail);
	memset (prev, -1, sizeof prev);


	int ans = 1;
	for (int i = 1; i < n; ++i) {
		if (v[i] < v[tail[0]])
			tail[0] = i;
		else if (v[i] > v[tail[ans - 1]]) {
			prev[i] = tail[ans - 1];
			tail[ans++] = i;
		} else {
			int pos = findIndex(-1, ans - 1, v[i]);
			prev[i] = tail[pos - 1];
			tail[pos] = i;
		}
	}

	return ans;
}