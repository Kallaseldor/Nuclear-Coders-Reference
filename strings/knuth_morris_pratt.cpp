
const int MAXN = 112345;

int b[MAXN];

void kmpBuild (const string & p) {
	int i = 0, j = -1;
	b[0] = -1;

	while (i < p.size()) {
		while (j >= 0 && p[i] != p[j]) j = b[j];
		++i; ++j;
		v[i] = j;
	}
}

int kmpSearch (const string & p, const string & t) {
	int i = 0, j = 0;

	int ans = 0;
	while (i < t.size()) {
		while (j >= 0 && t[i] != p[j]) j = b[j];
		++i; ++j;
		if (j == p.size()) {
			++ans;
			j = b[j];
		}
	}

	return ans;
}