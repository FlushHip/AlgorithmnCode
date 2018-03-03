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

		LL x[] = {k - 2 * d1 - d2,
					k - 2 * d1 + d2,
					k + 2 * d1 - d2,
					k + 2 * d1 + d2};
        bool ans = false;
        for (int i = 0; i < 4; i++) {
			int sum = 0;
			for (LL t = x[i]; t; sum += t % 10, t /= 10) {}

			if (sum % 3 == 0 && 0 <= x[i] / 3 && x[i] / 3 <= k) {
				LL a = x[i] / 3, b, c;
				getabc(i, a, &b, &c, d1, d2);

				if (0 <= b && b <= k && 0 <= c && b <= k) {
					LL max_ele = max(a, max(b, c));
					LL diff = 3 * max_ele - a - b - c;
					if (n - k - diff >= 0 && (n - k - diff) % 3 == 0) {
						ans = true;
						break;
					}
				}
			}
        }
        cout << (ans ? "yes" : "no") << endl;
    }
	return 0;
}
