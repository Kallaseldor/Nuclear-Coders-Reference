// Z-Function
// Time Complexity: O(|S|)

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1123456;
int z[MAXN];

void zfunction (string s) {
	int n = s.size();

	int L = 0, R = 0;
	for (int i = 1; i < n; ++i) {
		if (i > R)
			L = R = i;
		z[i] = min (z[i - L], R - i);
		while (i + z[i] < n && s[i + z[i]] == s[z[i]])
			++z[i], L = i, R = i + z[i];
	}
}