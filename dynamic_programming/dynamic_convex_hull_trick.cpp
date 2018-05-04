// === UNTESTED ===

// Dynamic Convex Hull Trick (DP optimization)
// Insert:	O (log N)
// Query:	O (log N)
// Memo Complexity: O (N)

const long long is_query = -0x3F3F3F3F3F3F3F3FLL;	// if double, -HUGE_VAL

struct Line {
	long long m, b;
	mutable function <const Line * ()> succ;
	bool operator< (const Line & rhs) const {
		if (rhs.b != is_query) return m < rhs.m; // > for min
		const Line * s = succ();
		if (!s) return 0;
		return b - s -> b < (s -> m - m) * rhs.m; // > for min
	}
};

struct DynamicHull : public multiset <Line> {
	bool bad (iterator y) {
		auto z = next (y);
		if (y == begin ()) {
			if (y == end ()) return 0;	// talvez seja z == end() aqui. n sei. acho que nao faz diferenca
			return y -> m == z -> m && y -> b <= z -> b; // >= for min
		}

		auto x = prev (y);

		if (z == end () ) return y -> m == x -> m && y -> b <= x -> b; // >= for min
		return 1.0L * (x -> b - y -> b) * (z -> m - y -> m) >= 1.0L * (y -> b - z -> b) * (y -> m - x -> m);
	}

	void insert_line (long long m, long long b) {
		auto y = insert ({ m, b });
		y -> succ = [=] { return next (y) == end () ? 0 : & * next (y); };
		if (bad (y) ) { erase (y); return; }
		while (next (y) != end() && bad (next (y))) erase (next (y));
		while (y != begin () && bad (prev (y))) erase (prev (y)); 
	}

	long long eval (long long x) {
		auto l = *lower_bound ((Line) { x, is_query });
		return l.m * x + l.b;
	}
};