#include <bits/stdc++.h>

using namespace std;

struct Rect {
    int x[4];
    Rect() {}
};

bool judge(const vector<Rect>::iterator &it, int x, int y)
{
    return it->x[0] < x && x < it->x[2] && it->x[1] < y && y < it->x[3];
}

int main()
{
    for (int n; cin >> n; ) {
        vector<Rect> rects(n);
        vector<int> approch_x, approch_y;
        for (int i = 0, x; i < n; cin >> x, approch_x.push_back(rects[i++].x[0] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_y.push_back(rects[i++].x[1] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_x.push_back(rects[i++].x[2] = x)) {}
        for (int i = 0, x; i < n; cin >> x, approch_y.push_back(rects[i++].x[3] = x)) {}
        sort(approch_x.begin(), approch_x.end());
        sort(approch_y.begin(), approch_y.end());
        for (auto it = rects.begin(); it != rects.end(); ++it) {
            for (int i = 0; i < 4; i++) {
                if (i % 2 == 0)
                    it->x[i] = (lower_bound(approch_x.begin(), approch_x.end(), it->x[i]) - approch_x.begin()) * 2;
                else
                    it->x[i] = (lower_bound(approch_y.begin(), approch_y.end(), it->x[i]) - approch_y.begin()) * 2;
            }
        }

        int col = (lower_bound(approch_x.begin(), approch_x.end(), approch_x.back()) - approch_x.begin()) * 2;
        int row = (lower_bound(approch_y.begin(), approch_y.end(), approch_y.back()) - approch_y.begin()) * 2;

        int ans = 1;
        for (int i = 0; i + 2 < row; i += 2) {
            for (int j = 0; j + 2 < col; j += 2) {
                int sum = 0;
                for (auto it = rects.begin(); it != rects.end(); ++it)
                    sum += judge(it, i + 1, j + 1);
                ans = max(ans, sum);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
