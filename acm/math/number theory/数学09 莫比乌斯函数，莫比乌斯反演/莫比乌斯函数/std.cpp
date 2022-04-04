#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 1e7 + 7;
int cnt, mu[N], vis[N], prime[N];
void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < N; ++i)
    {
        if (!vis[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i < N; ++j) {
            vis[i * prime[j]] = 1;
            mu[i * prime[j]] = mu[i] * mu[prime[j]];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
int main()
{
    sieve();
    LL ans = 0;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ans += 1LL * i * mu[i];
    }
    cout << ans << endl;
    return 0;
}