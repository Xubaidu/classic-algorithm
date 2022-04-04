#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N1 = 10;
const int N2 = 100;
const int N3 = 1e9;
const int K1 = 50;
const int K2 = 100;
const int K3 = 1e6;
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
    if (!a)
        return 0;
    LL ans = 1;
    while (b)
    {
        if (b & 1)
            ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}

LL inv(LL a)
{
    return qpow(a, MOD - 2);
}

void genData(int N, int K)
{
    n = rand() % N + 1;
    k = rand() % K + 1;
    cout << n << ' ' << k << "\n-----" << endl;
}

void solve()
{
    pre[0] = suf[k + 3] = fac[0] = 1;
    for (int i = 1; i <= k + 2; ++i)
        pre[i] = pre[i - 1] * (n - i) % MOD;
    for (int i = k + 2; i >= 1; --i)
    {
        suf[i] = suf[i + 1] * (n - i) % MOD;
        suf[i] = (MOD + suf[i]) % MOD;
    }
    for (int i = 1; i <= k + 2; ++i)
        fac[i] = i * fac[i - 1] % MOD;
    LL ans = 0, y = 0;
    for (int i = 1; i <= k + 2; ++i)
    {
        y += qpow(i, k), y %= MOD;
        LL fz = pre[i - 1] * suf[i + 1] % MOD;
        LL fm = fac[i - 1] * fac[k + 2 - i] % MOD;
        if ((k - i) % 2)
            fm = (MOD - fm) % MOD;
        ans += y * (fz * inv(fm) % MOD) % MOD, ans %= MOD;
    }
    cout << ans << "\n-----" << endl;
}
int main()
{
    srand((unsigned)time(nullptr));
    freopen("in.txt", "w", stdout);
    for (int i = 0; i < 20; ++i)
    {
        if (i < 6)
            genData(N1, K1);
        else if (i < 12)
            genData(N2, K2);
        else
            genData(N3, K3);
        solve();
    }
    return 0;
}