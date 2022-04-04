#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL MOD = 998244353;

LL solve(LL n)
{
    LL ans = 0;
    for (LL l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (r - l + 1) * (n / l);
        ans %= MOD;
    }
    return ans;
}

int main()
{
    LL n;
    cin >> n;
    cout << solve(n) << endl;
    return 0;
}