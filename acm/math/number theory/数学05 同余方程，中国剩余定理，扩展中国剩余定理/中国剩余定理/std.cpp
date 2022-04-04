#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;


int n;
LL m[12], a[12];

LL qpow(LL a, LL b, LL m)
{
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

LL getInv(LL a, LL MOD)
{
    LL x, y;
    LL r = exgcd(a, MOD, x, y);
    while(x < 0) x += MOD;
    y = (1 - a * x) / b;
    return x;
}

int main()
{
    scanf("%d", &n);
    LL M = 1;
    for(int i = 1; i <= n; ++i)
        scanf("%lld %lld", &m[i], &a[i]), M *= m[i];
    LL x = 0;
    for(int i = 1; i <= n; ++i) {
        LL Mi = M / m[i];
        LL Xi = 1LL * a[i] * getInv(Mi, m[i]) % m[i] * Mi % M;
        x += Xi, x %= M;
    }
    cout << x << endl;
    return 0;
}
