#include <bits/stdc++.h>
 
using namespace std;
 
int main()
{
    string s;
    int m;
    while (cin >> s >> m) {
        int ans = 1;
        for (char c = 'a'; c <= 'z'; c++) {
            vector<int> pos;
            for (int i = 0; i < (int)s.size(); i++)
                if (c == s[i])
                    pos.push_back(i);
 
            if (pos.size() < 2)
                continue;
 
            int ret = 1;
            vector<vector<int> > dp(pos.size(), vector<int>(pos.size(), 0));
 
            for (int len = 2; len <= (int)pos.size(); ++len) {
                for (int i = 0; i + len - 1 < (int)pos.size(); i++) {
                    dp[i][i + len - 1] = dp[i + 1][i + len - 2] + pos[i + len - 1] - pos[i] - len + 1;
                    if (dp[i][i + len - 1] <= m)
                        ret = len;
                }
            }
            ans = max(ans, ret);
        }
        cout << ans << endl;
    }
    return 0;
}
