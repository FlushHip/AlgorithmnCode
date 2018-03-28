#include <bits/stdc++.h>

using namespace std;

int main()
{
	int T;
	for (cin >> T; T--; ) {
		int n, ans = 0;
		string str;
		cin >> n >> str;
        for (int i = 0; i < (int)str.size(); ) {
			for (; i < (int)str.size() && str[i] == 'X'; ++i) {}
			for (; i < (int)str.size() && str[i] == '.'; ans++, i += 3) {}
        }
        cout << ans << endl;
	}
	return 0;
}
