#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

void getabc(int i, LL a, LL *pb, LL *pc, LL d1, LL d2)
{
    switch (i) {
    case 0:
        *pb = a + d1;
        *pc = *pb + d2;
        break;
    case 1:
        *pb = a + d1;
        *pc = *pb - d2;
        break;
    case 2:
        *pb = a - d1;
        *pc = *pb + d2;
        break;
    case 3:
        *pb = a - d1;
        *pc = *pb - d2;
        break;
    }
}

int main()
{
    int T;
    for (cin >> T; T--; ) {
        LL n, k, d1, d2;
        scanf("%lld%lld%lld%lld", &n, &k, &d1, &d2);
        if (n % 3) {
            cout << "no" << endl;
            continue;
        }

        LL x[] = {k - 2 * d1 - d2,
                    k - 2 * d1 + d2,
                    k + 2 * d1 - d2,
                    k + 2 * d1 + d2};
        bool ans = false;
        for (int i = 0; i < 4; i++) {
            int sum = 0;
            for (LL t = x[i]; t; sum += t % 10, t /= 10) {}

            if (sum % 3 == 0 && 0 <= x[i] / 3 && x[i] / 3 <= k && x[i] <= n) {
                LL a = x[i] / 3, b, c;
                getabc(i, a, &b, &c, d1, d2);

                if (0 <= b && b <= min(k, n / 3) && 0 <= c && c <= min(k, n / 3)) {
                    ans = true;
                    break;
                }
            }
        }
        cout << (ans ? "yes" : "no") << endl;
    }
    return 0;
}
