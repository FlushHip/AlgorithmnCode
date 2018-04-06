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
		LL ans = R;
		G -= R, B -= R;
		if (G * 2 <= B) {
			ans += G;
			ans += min(2 * R, (B - 2 * G) / 3);
		} else {
			ans += G / 3 * 2;
			B -= G / 3 * 3 * 2, G %= 3;
			if (G * 2 <= B) 
				ans += G, B -= 2 * G, G = 0;
			ans += min(3 * R, B / 3 + G / 3);
		}
		cout << ans << endl;
	}
	return 0;
}
