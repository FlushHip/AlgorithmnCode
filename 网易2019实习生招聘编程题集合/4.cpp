#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
    for (LL n, k; cin >> n >> k; ) {
        LL ans = 0;
        if (!k)
            ans = n * n;
        else
            for (LL y = k + 1; y <= n; y++)
                ans += n / y * (y - k) + (n % y >= k ? n % y - k + 1 : 0);
        cout << ans << endl;
    }
    return 0;
}
