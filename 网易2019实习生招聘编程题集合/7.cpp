#include <bits/stdc++.h>

using namespace std;

int main()
{
    for (int n; cin >> n; ) {
        vector<int> arr;
        for (int i = 0, x, y; i < n; cin >> x >> y, arr.push_back(x * 60 + y), ++i) {}
        sort(arr.begin(), arr.end());
        int x, A, B;
        cin >> x >> A >> B;
        int ans = *(lower_bound(arr.begin(), arr.end(), A * 60 + B - x + 1) - 1);
        cout << ans / 60 << " " << ans % 60 << endl;
    }
    return 0;
}
