const int MAXN = 500;
const int MAXC = 26;    // Alphabet size

int term[MAXN];
int len[MAXN];
int to[MAXN][MAXC];
int link[MAXN];

int sz = 1;

void add_str (string s) {
	int cur = 0;
	for (int i = 0; i < s.size(); ++i) {
		char c = s[i] - 'a';
		if (!to[cur][c]) {
			to[cur][c] = sz++;
			len[to[cur][c]] = len[cur] + 1;
		}

		cur = to[cur][c];
	}
	term[cur] = cur;
}

void push_links () {
	int que[sz];
	int st = 0, fi = 1;   // Start, Target
	que[0] = 0;

	while (st < fi) {
		int v = que[st++];
		int u = link[v];
		if (!term[v]) term[v] = term[u];
		for (int c = 0; c < MAXC; ++c)
			if (to[v][c]) {
				link[to[v][c]] = v ? to[u][c] : 0;
				que[fi++] = to[v][c];
			} else
				to[v][c] = to[u][c];
	}
}