#include <bits/stdc++.h>
#include <random>
using namespace std;

typedef long long LL;
const LL N1 = 1e3;
const LL N2 = 1e5;
const LL N3 = 1e7;

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<unsigned long long> dis;

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

LL get(LL n, LL m)
{
    LL ans = 0;
    if (n < m) swap(n, m);
    for (LL l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}
void solve(LL N)
{
    LL a = dis(gen) % N + 1;
    LL b = dis(gen) % N + 1;
    cout << a << ' ' << b <<  "\n-----" << endl;
    LL ans = get(a, b);
    cout << ans << "\n-----" << endl;
}

int main()
{
    sieve();
    for (int i = 1; i < N; ++i) mu[i] += mu[i - 1];
    freopen("in.txt", "w", stdout);
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 50; ++i)
    {
        if (i < 15) solve(N1);
        else if (i < 30) solve(N2);
        else solve(N3);
    }
    return 0;
}