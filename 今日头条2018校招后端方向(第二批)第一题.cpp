#include <bits/stdc++.h>

using namespace std;

bool sort_cmp(const pair<int, int> &A, const pair<int, int> &B)
{
	return A.first == B.first ? A.second < B.second :
		A.first < B.first;
}

struct find_first_cmp {
	bool operator()(const pair<int, int> &P, int k) const
	{
		return P.first < k;
	}

	bool operator()(int k, const pair<int, int> &P) const
	{
		return k < P.first;
	}
};

struct find_second_cmp {
	bool operator()(const pair<int, int> &P, int k) const
	{
		return P.second < k;
	}

	bool operator()(int k, const pair<int, int> &P) const
	{
		return k < P.second;
	}
};

int main()
{
	int n, q;
	while (EOF != scanf("%d", &n)) {
		vector<pair<int, int> > arr;
		for (int i = 0, x; i < n; cin >> x, arr.emplace_back(x, ++i)) {}
		sort(arr.begin(), arr.end(), sort_cmp);

		for (scanf("%d", &q); q--;) {
			int L, R, k;
			scanf("%d%d%d", &L, &R, &k);
			pair<vector<pair<int, int> >::iterator, vector<pair<int, int> >::iterator> sd =
				equal_range(arr.begin(), arr.end(), k, find_first_cmp{});
			printf("%d\n", upper_bound(sd.first, sd.second, R, find_second_cmp{}) -
				lower_bound(sd.first, sd.second, L, find_second_cmp{}));
		}
	}
	return 0;
}
