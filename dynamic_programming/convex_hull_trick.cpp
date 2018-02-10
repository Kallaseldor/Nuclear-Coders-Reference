// Convex Hull Trick (DP optimization)
// Time Complexity: O((N + Q log N)
// Memo Complexity: O(N)

// OBS: Lines have to be inserted in order

const int MAXN = 112345;
const long long LINF = 0x3F3F3F3F3F3F3F3FLL;

struct Line {
	long long m, b;
	Line () {}
	Line (long long _m, long long _b) {
		m = _m; b = _b;
	}

	bool operator< (const Line other) const {
		if (m != other.m) return m > other.m;
		return b > other.b;
	}

	long long getVal (const int x) {
		return m * x + b;
	}
};

struct ConvexHullTrick {
	vector< Line > st;
	bool badLine (Line s, Line t, Line u) {
		if (t.m == u.m) return true;
		return 1.0 * (t.b - s.b) * (s.m - u.m) >= 1.0 * (u.b - s.b) * (s.m - t.m);
	}

	void addLine (Line l) {
		while (st.size() >= 2 && badLine(st[st.size() - 2], st[st.size() - 1], l)) st.pop_back();
		st.push_back(l);
	}

	long long query (long long x) {
		if (st.size() == 0) return LINF;
		int lo = 0, hi = st.size() - 1;
		
		while (lo < hi) {
			int mid = (lo + hi) >> 1;
			if (st[mid].getVal(x) <= st[mid + 1].getVal(x)) hi = mid;
			else lo = mid + 1;
		}

		return st[lo].getVal(x);
	}
} s;

long long a[MAXN], b[MAXN], dp[MAXN];

int main() {

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) scanf("%lld", a + i);
	for (int i = 0; i < n; ++i) scanf("%lld", b + i);

	dp[0] = 0;
	s.addLine(Line(b[0], dp[0]));
	for (int i = 1; i < n; ++i) {
		dp[i] = s.query(a[i]);
		s.addLine(Line(b[i], dp[i]));
	}

	cout << dp[n - 1] << endl;

	return 0;
}