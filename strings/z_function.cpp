// Z-Function
// Time Complexity: O(|str|)

// Acho que nao ta funcionando

const int MAXN = 1123456;
int z[MAXN];

void zfunction (const string & str) {
	int n = str.size();

	int L = 0, R = 0;
	for (int i = 1; i < n; ++i) {
		if (i > R)
			L = R = i;
		z[i] = min (z[i - L], R - i);
		while (i + z[i] < n && str[i + z[i]] == str[z[i]])
			++z[i], L = i, R = i + z[i];
	}
}


void zfunction (const string & str) {
	int n = str.size();

	int L = 0, R = 0;
	for (int i = 1; i < n; ++i) {
		if (i > R) {
			L = R = i;
			while (R < n && s[R - L] == R) ++R;
			z[i] = R - L; --R;
		} else {
			int k = i - L;
			if (z[k] < R - i + 1) z[i] = z[k];
			else {
				L = i;
				while (R < n && s[R - L] == s[R]) ++R;
				z[i] = R - L; --R;
			}
		}
	}
}