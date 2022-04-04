#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 1e9;
const int K = 1e6 + 7;
const int MOD = 1e9 + 7;
LL n, k;

// pre[i] = (n - 1)(n - 2)..(n - i)
// pre[i] = pre[i - 1] * (n - i)
// suf[i] = (n - i)(n - (i + 1))..(n - (k + 2))
// suf[i] = suf[i + 1] * (n - i)
LL fac[K], pre[K], suf[K];

LL qpow(LL a, LL b)
{
    if (!a) return 0;
    LL ans = 1;
    while (b) {
        if (b & 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}

LL inv(LL a)
{
    return qpow(a, MOD - 2);
}
int main()
{
    cin >> n >> k;
    LL ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += qpow(i, k), ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}