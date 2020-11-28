#include <bits/stdc++.h>

using namespace std;

int fun(int x)
{
    return x / 3 * 2 + (x % 3 == 0 ? 0 : x % 3 == 1 ? 0 : 1);
}

int main()
{
    for (int l, r; cin >> l >> r; cout << fun(r) - fun(l - 1) << endl) {}
    return 0;
}
