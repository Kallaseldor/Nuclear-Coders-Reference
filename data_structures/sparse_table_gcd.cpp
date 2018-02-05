// Sparse Table (GCD)
// Build Time Complexity: O(n log n)
// Query Time Complexity: O(1)

// 0 - indexed queries

const int MAXN = 1123;
const int LOGN = 30;

int memo[MAXN][LOGN];	// memo[i][j] = gcd v[i  ..  i + (1 << j) - 1]
int v[MAXN];			// Original array

void build (int n) {
	for (int i = 0; i < n; ++i) {
		memo[i][0] = v[i];
	}

	for (int j = 1; (1 << j) <= n; ++j)
		for (int i = 0; (1 << j) + i - 1 < n; ++i)
			memo[i][j] = __gcd(memo[i][j - 1], memo[i + (1 << (j - 1))][j - 1]);
}

int query (int l, int r) {
	int j = (int) log2(r - l + 1);
	return __gcd(memo[l][j], memo[r - (1 << j) + 1][j]);
}