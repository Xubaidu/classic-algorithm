#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 1e7 + 7;
const int MOD = 998244353;
int vis[N], prime[N], num[N], d[N];
LL ans[N];
int sieve(int n)
{
    int cnt = 0;
    d[1] = 1;
    for (int i = 2; i <= n; ++i) {
        if (!vis[i]) prime[++cnt] = i, num[i] = 1, d[i] = 2;
        for (int j = 1; j <= cnt && i * prime[j] <= n; ++j) {
            vis[i * prime[j]] = 1;
            d[i * prime[j]] = d[i] * d[prime[j]];
            num[i * prime[j]] = 1; // i * prime[j] 中第一次出现最小质因子 prime[j]
            if (i % prime[j] == 0) {
                d[i * prime[j]] = d[i] / (num[i] + 1) * (num[i] + 2);
                num[i * prime[j]] = num[i] + 1; // i * prime[j] 中再一次出现最小质因子 prime[j]
                break;
            }
        }
    }
    return cnt;
}

int main()
{
    LL n;
    cin >> n;
    int cnt = sieve(n);
    LL res1 = 0, res2 = 0;
    for (int i = 1; i <= n; ++i) {
        res1 += d[i], res1 %= MOD;
        res2 += 1LL * i * d[i], res2 %= MOD;
    }
    cout << res1 << endl;
    cout << res2 << endl;
    return 0;
}