#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for (int n; T--; ) {
		cin >> n;
		vector<int> arr;
		for (int i = 0, x; i < n << 1; cin >> x, arr.push_back(x), ++i) {}
		sort(arr.begin(), arr.end());
		cout << (arr[n / 2 - 1] != arr[n / 2] ? "YES" : "NO") << endl;
	}
	return 0;
}
