// Fuzzy Search - CF 528D
// Finding position where amount of matches is maximal
// O (N * log N * A) where A is alphabet size

#include <bits/stdc++.h>
using namespace std;

const double pi = acos (-1);

class Point {
public:
	double x, y;

	Point () {x = 0.0; y = 0.0;}
	Point (double _x, double _y) {
		x = _x; y = _y;
	}

	Point operator+ (const Point & other) const {
		return Point (x + other.x, y + other.y);
	}

	Point operator- (const Point & other) const {
		return Point (x - other.x, y - other.y);
	}

	Point operator * (const Point & other) const {
		return Point (x * other.x - y * other.y, x * other.y + y * other.x);
	}

	double operator~ () const {
		return sqrt (x * x + y * y);
	}
};

class FFT {
public:
	vector <Point> data;
	vector <Point> roots;
	vector <int> rev;
	int s, n;

	void setSize (int ns) {
		s = ns;
		n = (1 << s);

		rev = vector <int> (n);
		data = vector <Point> (n);
		roots = vector <Point> (n + 1);

		for (int i = 0; i < n; ++i)
			for (int j = 0; j < s; ++j)
				if ((i & (1 << j)) != 0)
					rev[i] += (1 << (s - j - 1));

		roots[0] = Point (1, 0);
		Point mult = Point (cos (2 * pi / n), sin (2 * pi / n));
		for (int i = 1; i <= n; ++i)
			roots[i] = roots[i - 1] * mult;
	}

	void bitReverse (vector <Point> & v) {
		vector <Point> temp (n);
		for (int i = 0; i < n; ++i)
			temp[i] = v[rev[i]];
		for (int i = 0; i < n; ++i)
			v[i] = temp[i];
	}

	void transform (bool inverse = false) {
		bitReverse (data);

		for (int i = 1; i <= s; ++i) {
			int m = (1 << i), md2 = m >> 1;
			int start = 0, increment = (1 << (s - i));
			if (inverse) {
				start = n;
				increment *= -1;
			}

			Point t;
			for (int k = 0; k < n; k += m) {
				int index = start;
				for (int j = k; j < md2 + k; ++j) {
					t = roots[index] * data[j + md2];
					index += increment;
					data[j + md2] = data[j] - t;
					data[j] = data[j] + t;
				}
			}
		}

		if (inverse)
			for (int i = 0; i < n; ++i) {
				data[i].x /= n;
				data[i].y /= n;
			}
	}

	static vector <int> convolution (const vector <int> & a, const vector <int> & b) {
		int alen = a.size(), blen = b.size();
		int resn = alen + blen - 1;

		int s = 0;
		while ((1 << s) < resn) ++s;
		int n = 1 << s;

		FFT pga, pgb;
		pga.setSize (s);
		for (int i = 0; i < alen; ++i) pga.data[i] = Point (a[i], 0);
		for (int i = alen; i < n; ++i) pga.data[i] = Point (0, 0);
		pga.transform();

		pgb.setSize (s);
		for (int i = 0; i < blen; ++i) pgb.data[i] = Point (b[i], 0);
		for (int i = blen; i < n; ++i) pgb.data[i] = Point (0, 0);
		pgb.transform();

		for (int i = 0; i < n; ++i) pga.data[i] = pga.data[i] * pgb.data[i];
		pga.transform (true);
		vector <int> result = vector <int> (resn);
		for (int i = 0; i < resn; ++i) result[i] = (int) (pga.data[i].x + 0.5);
		
		int actualSize = resn - 1;
		while (actualSize >= 0 && result[actualSize] == 0)
			actualSize--;
		if (actualSize < 0) actualSize = 0;
		result.resize (actualSize + 1);
		return result;
	}
};

int match[212345];

int main () {
	string cc = "ATCG";

	int n, m, k;
	cin >> n >> m >> k;		// For no "errors", set K = 0

	string s, t;
	
	cin >> s >> t;
	
	for (int c = 0; c < cc.size(); ++c) {
		char ch = cc[c];
		vector <int> ss = vector <int> (n + 1, 0);
		vector <int> tt = vector <int> (m + 1, 0);

		for (int i = 0; i < n; ++i) {
			if (s[i] == ch) {
				ss[max (0, i - k)]++;
				ss[min (n, i + k + 1)]--;
			}
		}

		for (int i = 1; i <= n; ++i)
			ss[i] += ss[i - 1];

		for (int i = 0; i < n; ++i)
			if (ss[i]) ss[i] = 1;

		int q = 0;
		for (int i = 0; i < m; ++i) {
			if (t[i] == ch) {
				tt[m - i - 1] = 1;
				++q;
			}
		}

		vector <int> tmp = FFT :: convolution (ss, tt);

		for (int i = 0; i < n - m + 1; ++i) {
			match[i] += tmp[i + m - 1];
		}
	}

	int ans = 0;
	for (int i = 0; i < n - m + 1; ++i) {
		if (match[i] == m) ++ans;
	}

	cout << ans << endl;


	return 0;
}