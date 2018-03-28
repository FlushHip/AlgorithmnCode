#include <bits/stdc++.h>

using namespace std;

int main()
{
	for (string str; cin >> str; ) {
		vector<int> used(10, 0);
		int digit = -1, theMin = 0x3f3f3f3f;
		for (auto it = str.begin(); it != str.end(); ++it)
			++used[*it - '0'];
		for (int i = 1; i < 10; i++)
			if (theMin > used[i])
				theMin = used[i], digit = i;
		if (used[0] + 1 <= theMin)
			cout << "1" + string(used[0] + 1, '0') << endl;
		else
			cout << string(theMin + 1, digit + '0') << endl;
	}
	return 0;
}
