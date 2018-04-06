#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int main()
{
	int T;
	cin >> T;
	for (LL r, g, b; T--; ) {
		cin >> r >> g >> b;
		LL R = min(min(r, g), b), B = max(max(r, g), b), G = r + g + b - R - B;
		LL ans = (R + G) * 2 <= B ? R + G : (R + G + B) / 3;
		cout << ans << endl;
	}
	return 0;
}
