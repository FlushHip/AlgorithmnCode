#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m, c;
	while (EOF != scanf("%d%d%d", &n, &m, &c)) {
		vector<vector<int> > arr(n + m);
		for (int i = 0, num, x; i < n; i++)
			for (scanf("%d", &num); num--;
				arr[i].push_back((scanf("%d", &x), x))) {}
		for (int i = 0; i < m; i++)
			arr[n + i] = arr[i];
		vector<bool> used(c, false);
		map<int, int> color;
		for (int i = 0; i < c; color[i++] = 0) {}

		for (int i = 0; i < n + m; i++) {
			for (int j = 0; !(i < m) && j < (int)arr[i - m].size(); j++)
				color[arr[i - m][j] - 1]--;
			for (int j = 0; j < (int)arr[i].size(); j++)
				color[arr[i][j] - 1]++;
			for (map<int, int>::iterator it = color.begin(); it != color.end(); ++it)
				used[it->first] = it->second > 1 ? true : used[it->first];
		}
		int ans = 0;
		for (int i = 0; i < c; ans += used[i++]) {}
		printf("%d\n", ans);
	}
	return 0;
}
