#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for (int n, x1, y1, x2, y2; T--; ) {
		cin >> n;
		int ans = 0;
		for (int i = 0; i < n; i++)	
			cin >> x1 >> y1 >> x2 >> y2,
			ans += (x2 - x1 + 1) * (y2 - y1 + 1);
		cout << ans << endl;
	}
	return 0;
}
