#include <bits/stdc++.h>

using namespace std;

#define gcd __gcd

struct Point {
	int x, y, z;
	Point() {}
	Point(int x, int y, int z) : x(x), y(y), z(z) {}
	
	bool operator<(const Point &other) const {
		if (x != other.x)
			return x < other.x;
		if (y != other.y)
			return y < other.y;
		if (z != other.z)
			return z < other.z;
	}
};

typedef pair<pair<int, int>, int> Node;

int main()
{
    for (int n; cin >> n; ) {
		vector<Point> points;
		for (int i = 0, x, y, z; i < n; i++)
			cin >> x >> y >> z, points.push_back(Point(x, y, z));
		sort(points.begin(), points.end());
		
		int ans = 0;
		for (int i = 0; i < n; i++) {
			map<Node, int> mp;
			for (int j = i + 1; j < n; j++) {
				int vx = points[j].x - points[i].x;
				int vy = points[j].y - points[i].y;
				int vz = points[j].z - points[i].z;
				int g = gcd(gcd(vx, vy), vz);
				mp[make_pair(make_pair(vx / g, vy / g), vz / g)]++;
			}
			int sum = 0;
			for (auto it = mp.begin(); it != mp.end(); ++it)
				sum = max(sum, it->second);
			ans = max(sum, ans);
		}
		cout << ans + 1 << endl;
	}
    return 0;
}
