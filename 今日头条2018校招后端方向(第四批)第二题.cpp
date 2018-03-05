#include <bits/stdc++.h>

using namespace std;

int main()
{
    int n, m;
    string s;
    for (; cin >> n >> m >> s; ) {
        int ans = 0;
        for (char c = 'a'; c < 'c'; ++c) {
            vector<vector<int> > dp(2, vector<int>(s.size(), 0));
            int ret = 1;
            for (int i = 0; i < (int)s.size(); ++i)
                dp[1][i] = s[i] != c;
            for (int len = 2; len <= (int)s.size(); ++len) {
                for (int i = 0; i + len - 1 < (int)s.size(); i++) {
                    dp[len % 2][i] = max((dp[(len - 1) % 2][i] + (s[i + len - 1] != c)),
                                         (dp[(len - 1) % 2][i + 1] + (s[i] != c)));
                    if (dp[len % 2][i] <= m)
                        ret = len;
                }
            }
            ans = max(ans, ret);
        }
        cout << ans << endl;
    }
    return 0;
}
