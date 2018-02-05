#include <bits/stdc++.h>
using namespace std;

struct TVector {
	long long x, y;

	TVector () {}
	TVector (long long _x, long long _y) {
		x = _x; y = _y;
	}

	TVector operator+ (const TVector p) const {
		return TVector (x + p.x, y + p.y);
	}

	TVector operator- (const TVector p) const {
		return TVector (x - p.x, y - p.y);
	}

	long long operator^ (const TVector p) const {
		return x * p.y - y * p.x;
	}

	long long operator* (const TVector p) const {
		return x * p.x + y * p.y;
	}

	long long operator~ () const {
		return x * x + y * y;
	}

	long long distanceToSegment2 (const TVector s1, const TVector s2) const {
		TVector c = *this;
		if ( 	((s2 - s1) * (c - s1)) <= 0 ||
				((s1 - s2) * (c - s2)) <= 0) {
			return min(~(s1 - c), ~(s2 - c));
		} else {
			long long area = (s2 - s1) ^ (c - s1);
			return (area * area) / (~(s2 - s1));
		}
	}
};

struct TCircle {
	TVector p;
	long long r;

	TCircle () {}
	TCircle (TVector _o, long long _r) {
		o = _o; r = _r;
	}

};

struct TLine {
	long long a, b, c;

	TLine () {}
	TLine (long long _a, long long _b, long long _c) {
		a = _a; b = _b; c = _c;
	}
}


int main() {

	return 0;
}