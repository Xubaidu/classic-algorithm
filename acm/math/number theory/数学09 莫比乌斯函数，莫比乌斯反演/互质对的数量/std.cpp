#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 5e4 + 7;
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

LL solve(LL n, LL m)
{
    LL ans = 0;
    if (n < m) swap(n, m);
    for (LL l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}
int main()
{
    sieve();
    for (int i = 1; i < N; ++i) mu[i] += mu[i - 1];
    LL a, b;
    scanf("%lld %lld", &a, &b);
    LL ans = solve(a, b); 
    cout << ans << endl;
    return 0;
}