#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N1 = 1e5;
const LL N2 = 1e7;
const LL N3 = 2e9;
const LL MOD = 998244353;

LL calc(LL n)
{
    LL ans = 0;
    for (LL l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (r - l + 1) * (l + r) * (n / l) / 2;
    }
    return ans;
}

void solve(LL N)
{
    LL R = rand() % N + 1;
    LL L = rand() % (R - 1) + 1;
    cout << L << ' ' << R << "\n-----" << endl;
    LL ans = calc(R) - calc(L - 1);
    cout << ans << "\n-----" << endl;
}

int main()
{
    srand((unsigned)time(nullptr));
    freopen("in.txt", "w", stdout);
    for (int i = 0; i < 50; ++i)
    {
        if (i < 15) solve(N1);
        else if (i < 30) solve(N2);
        else solve(N3);
    }
    return 0;
}