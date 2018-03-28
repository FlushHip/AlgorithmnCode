#include <bits/stdc++.h>

using namespace std;

int main()
{
	const char DIR[] = "NESW";
	for (int n; cin >> n; ) {
		string str;
		cin >> str;
		int ans = 0;
		for (int i = 0; i < n; i++)
			ans = (ans + (str[i] == 'L' ? -1 : 1) + 4) % 4;
		cout << DIR[ans % 4] << endl;
	}
	return 0;
}
