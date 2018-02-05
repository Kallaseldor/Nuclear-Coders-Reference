// Z-Function
// Time Complexity: O(|S|)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123456;
int z[MAXN];

void zfunction (string s) {
	int n = s.size();

	int l = 0, r = 0;
	for (int i = 1; i < n; ++i) {
		if (i > r) {
			l = r = i;
			while (r < n && s[r - l] == s[r]) ++r;
			z[i] = r - l; --r;
		} else {
			int k = i - l;
			if (z[k] < r - l + 1) z[i] = z[k];
			else {
				l = i;
				while (r < n && s[r - l] == s[r]) ++r;
				z[i] = r - l; ++r;
			}
		}
	}


}