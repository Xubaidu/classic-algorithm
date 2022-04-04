#include <bits/stdc++.h>
typedef long long LL;
const int N = 2e3 + 7;
const int MOD = 998244353;
using namespace std;

LL qpow(LL a, LL b)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}
LL inv(LL x) {return qpow(x, MOD - 2) % MOD;}
LL add(LL x, LL y) {return (x + y) % MOD;}
LL sub(LL x, LL y) {return ((x - y) % MOD + MOD) % MOD;}

LL k, n, x[N], y[N];

int main()
{
    scanf("%lld %lld", &n, &k);
    for(int i = 1; i <= n; ++i) scanf("%lld %lld", &x[i], &y[i]);
    LL res = 0;
    for(int j = 1; j <= n; ++j) {
        LL ans = y[j];
        for(int i = 1; i <= n; ++i) {
            if(i == j) continue;
            ans *= sub(k, x[i]), ans %= MOD;
            ans *= inv(sub(x[j], x[i])), ans %= MOD;
        }
        res += ans, res %= MOD;
    }
    printf("%lld\n", res);
    return 0;
}