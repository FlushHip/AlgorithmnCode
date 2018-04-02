#include <bits/stdc++.h>

using namespace std;

int main()
{
	string src, des;
	cin >> src;
	des = src;
	reverse(des.begin(), des.end());
	vector<string> arr;
	for (string str; cin >> str; arr.push_back(str)) {}
	arr.push_back(des);
	queue<pair<string, int> > que;
	que.emplace(src, 1);
	bool isOk = false;
	while (!que.empty()) {
		auto now = que.front();
		que.pop();

		if (now.first == des) {
			cout << now.second << endl;
			isOk = true;
			break;
		}

        	if (now.second > 99)
			continue;
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			int sum = 0;
			for (int i = 0; i < (int)now.first.size(); i++)
				sum += now.first[i] != (*it)[i];
			if (sum == 1)
				que.emplace(*it, now.second + 1);
		}
	}
	if (!isOk)
		puts("0");
	return 0;
}
