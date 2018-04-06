#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	cin >> T;
	for (int a[5]; T--; ) {
		int sum = 0;
		for (int i = 0; i < 5; cin >> a[i++]) {}
		for (int i = 0; i < 5; sum += a[i++]) {}
		cout << (sum && sum % 5 == 0 ? sum / 5 : -1) << endl;
	}
	return 0;
}
