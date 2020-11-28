#include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int n, m; cin >> n >> m; ) {
        vector<pair<int, int> > arr;
        for (int i = 0, d, p; i < n; cin >> d >> p, arr.emplace_back(d, p), i++) {}
        sort(arr.begin(), arr.end());
        vector<int> ans(n);
        ans[0] = arr[0].second;
        for (int i = 1; i < (int)arr.size(); ans[i] = max(ans[i - 1], arr[i].second), ++i) {}

        for (int x; m--; ) {
            cin >> x;
            cout << ans[upper_bound(arr.begin(), arr.end(), make_pair(x, 0x3f3f3f3f)) - 1 - arr.begin()] << endl;
        }
    }
    return 0;
}
