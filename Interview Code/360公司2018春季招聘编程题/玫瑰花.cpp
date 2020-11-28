#include <bits/stdc++.h>

using namespace std;

const int mod = 772235;

int main()
{
	for (int n, k; cin >> n >> k; ) {
		vector<vector<int> > dp(n + 1, vector<int>(k + 1, 0));
		dp[0][0] = 1;
		for (int i = 1; i < n + 1; i++)
			for (int j = 1; j < k + 1; j++)
				dp[i][j] = (j * dp[i - 1][j] % mod + (k - j + 1) * dp[i - 1][j - 1] % mod) % mod;
		cout << dp[n][k] << endl;
	}
	return 0;
}
