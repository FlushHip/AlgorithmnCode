#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int find(vector<int> &p, int x)
{
	return p[x] == -1 ? x : (p[x] = find(p, p[x]));
}

int main()
{
	for (LL n, m, k; cin >> n >> m >> k; ) {
		vector<int> mp[n];
		vector<int> p(n, -1);
		for (int i = 0, x, y; i < m; i++) {
			cin >> x >> y;
			if (x + y == 1)
				continue;
			mp[x].push_back(y), mp[y].push_back(x);
			int fx = find(p, x), fy = find(p, y);
			if (fx == fy)
				continue;
			if (fx == 0 || fx == 1)
				p[fy] = fx;
			else
				p[fx] = fy;
		}
		vector<vector<LL> > dp0(1, vector<LL>(n, 0)), dp1(dp0);
		dp0[0][0] = dp1[0][1] = 1;
		LL pos = 1, d = 1;
		for (; pos < k; ++d) {
			dp0.push_back(vector<LL>(n, 0));	
			dp1.push_back(vector<LL>(n, 0));	
			for (int i = 2; i < n; i++) {
				if (find(p, i) == 0) {
					for (auto it = mp[i].begin(); it != mp[i].end(); ++it)
						dp0[d][i] += dp0[d - 1][*it];
				} else {
					for (auto it = mp[i].begin(); it != mp[i].end(); ++it)
						dp1[d][i] += dp1[d - 1][*it];
				}
			}
			for (int dd = 0; dd <= d; dd++) {
				for (int i = 0; i < n; i++) {
					if (find(p, i) == 1)
						continue;
					for (int j = 0; j < n; j++) {
						if (find(p, j) == 0)
							continue;
						pos += dp0[dd][i] * dp1[d - dd][j] * 2;
					}
				}
			}
		}
		cout << d << endl;
	}
	return 0;
}
