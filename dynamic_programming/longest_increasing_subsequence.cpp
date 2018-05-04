// Longest Increasing Subsequence (LIS)
// Time Complexity: O(n log n)
// Memo Complexity: O(n)

// If you dont need to reconstruct the sequence
int lis (const vector<int> & v) {
	
	multiset<int> s;
	multiset<int> :: iterator it;

	for (int i = 0; i < v.size(); ++i) {
		s.insert (v[i]);
		it = s.upper_bound (v[i]);	// for strictly increasing subsequence:
									// it = s.lower_bound (v[i]); ++it;

		if (it != s.end())
			s.erase (it);
	}

	return s.size();
}

// If you need to reconstruct the sequence
vector<int> lis_reconstruction(const vector<int> &elements) {
    // declare the set with a custom comparison function
    // that compares values instead of indices
    auto compare = [&](int x, int y) {
        return elements[x] < elements[y];
    };
    set< int, decltype(compare) > S(compare);

    // process the elements; for each length
    // maintain the index of the best end so far
    vector<int> previous( elements.size(), -1 );
    for (int i=0; i<int( elements.size() ); ++i) {
        auto it = S.insert(i).first;
        if (it != S.begin())
            previous[i] = *prev(it);
        if (*it == i && next(it) != S.end()) 
            S.erase(next(it));
    }

    // reconstruct the indices that form 
    // one possible optimal answer
    vector<int> answer;
    answer.push_back( *S.rbegin() );
    while ( previous[answer.back()] != -1 )
        answer.push_back( previous[answer.back()] );
    reverse( answer.begin(), answer.end() );
    return answer;
}


// gfg method with reconstruction
const int MAXN = 112345;

int v[MAXN], tail[MAXN], prev[MAXN];

int findIndex (int l, int r, int key) {
	while (r - l > 1) {
		int mid = l + (r - l) / 2;
		if (v[tail[mid]] >= key)
			r = mid;
		else
			l = mid;
	}
	return r;
}

int lis (int n) {
	if (n == 0) return 0;

	memset (tail, 0, sizeof tail);
	memset (prev, -1, sizeof prev);


	int ans = 1;
	for (int i = 1; i < n; ++i) {
		if (v[i] < v[tail[0]])
			tail[0] = i;
		else if (v[i] > v[tail[ans - 1]]) {
			prev[i] = tail[ans - 1];
			tail[ans++] = i;
		} else {
			int pos = findIndex(-1, ans - 1, v[i]);
			prev[i] = tail[pos - 1];
			tail[pos] = i;
		}
	}

	return ans;
}