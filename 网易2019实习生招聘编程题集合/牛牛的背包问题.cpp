#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    for (LL n, w; cin >> n >> w; ) {
        vector<LL> v;
        for (int i = 0, x; i < n; cin >> x, v.push_back(x), ++i) {}

        LL n1 = n >> 1, n2 = n - n1;

        vector<LL> arr;
        for (int i = 0; i < (1 << n1); i++) {
            LL sum = 0;
            for (int bits = 0; bits < n1; bits++)
                sum += (i & (1 << bits)) ? v[bits] : 0;
            arr.push_back(sum);
        }
        sort(arr.begin(), arr.end());

        LL ans = 0;
        for (int i = 0; i < (1 << n2); i++) {
            LL sum = 0;
            for (int bits = 0; bits < n2; bits++)
                sum += (i & (1 << bits)) ? v[n1 + bits] : 0;
            ans += lower_bound(arr.begin(), arr.end(), w - sum + 1) - arr.begin();
        }
        cout << ans << endl;
    }
    return 0;
}
