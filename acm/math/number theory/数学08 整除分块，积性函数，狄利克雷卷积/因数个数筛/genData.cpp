#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL N1 = 1e3;
const LL N2 = 1e5;
const LL N3 = 1e7;
const LL MOD = 998244353;

const int N = 1e7 + 7;
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
void solve(LL N)
{
    int n = rand() % N + 1;
    cout << n << "\n-----" << endl;
    LL res1 = ans[n], res2 = 0;
    for (int i = 1; i <= n; ++i)
        res2 += 1LL * i * d[i], res2 %= MOD;
    cout << res1 << "\n" << res2 << "\n-----" << endl;
}

int main()
{
    srand((unsigned)time(nullptr));
    freopen("in.txt", "w", stdout);
    sieve(N - 1);
    for (int i = 1; i <= N - 1; ++i) ans[i] = (ans[i - 1] + d[i]) % MOD;
    for (int i = 0; i < 50; ++i)
    {
        if (i < 15) solve(N1);
        else if (i < 30) solve(N2);
        else solve(N3);
    }
    return 0;
}