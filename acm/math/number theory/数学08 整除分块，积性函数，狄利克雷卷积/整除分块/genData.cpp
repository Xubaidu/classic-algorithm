#include <bits/stdc++.h>
#include <random>
using namespace std;

typedef long long LL;
const LL N1 = 1e5;
const LL N2 = 1e8;
const LL N3 = 1e12;
const LL MOD = 998244353;

random_device rd;
mt19937_64 gen(rd());
uniform_int_distribution<unsigned long long> dis;

void solve(LL N)
{
    LL n = dis(gen) % N + 1;
    cout << n << "\n-----" << endl;
    LL ans = 0;
    for (LL l = 1, r; l <= n; l = r + 1)
    {
        r = n / (n / l);
        ans += (r - l + 1) * (n / l);
        ans %= MOD;
    }
    cout << ans << "\n-----" << endl;
}

int main()
{
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