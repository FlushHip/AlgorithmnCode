#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (string S, T; cin >> S >> T; ) {
		int a = 0, b = 0;
		int lens = S.size(), lent = T.size();
		for (int i = 0; i < lens - lent + 1; i++)
			a += S[i] == 'a',
			b += S[i] == 'b';
		int ans = 0;
		for (int i = 0; i + lens - lent < lens; i++) {
			ans += T[i] == 'a' ? b : a;
			S[i] == 'a' ? --a : --b;
			S[i + lens - lent + 1] == 'a' ? ++a : ++b;
		}
		cout << ans << endl;
	}
	return 0;
}
