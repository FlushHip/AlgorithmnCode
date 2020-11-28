#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const LL mod = 1000000007;

int main()
{
    int n;
    while (cin >> n) {
        vector<int> arr(n + 1, 0);
        vector<LL> dp(n + 1, 0);
        for (int i = 1, x; i <= n; cin >> x, arr[i++] = x) {}
        if (n == 1) {
            cout << "1" << endl;
            continue;
        }
        for (int i = 1; i <= n; i++)
            // dp[i] = dp[i - 1] + 1 + 1 + dp[i - 1] - dp[arr[i] - 1] + 1 - 1;
            dp[i] = (2 * dp[i - 1] % mod - dp[arr[i] - 1] + 2) % mod;
        cout << dp[n] % mod << endl;
    }
    return 0;
}
