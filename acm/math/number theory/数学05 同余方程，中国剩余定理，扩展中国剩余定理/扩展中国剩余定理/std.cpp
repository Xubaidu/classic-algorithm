#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 1e5 + 7;
int n;
LL a[N], p[N];

LL qmul(LL a, LL b, LL mod)
{
    LL res = 0;
    while(b > 0) {
        if(b & 1) res += a, res %= mod;
        a += a, a %= mod;
        b >>= 1;
    }
    return res;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}

LL excrt(LL n, LL *a, LL *p)
{
    LL M = p[1]; // 维护LCM
    LL x = a[1]; // 维护解
    for(int i = 2; i <= n; ++i){
        LL xx = 0, yy = 0;
        LL gcd = exgcd(M, p[i], xx, yy);
        LL c = (a[i] - x % p[i] + p[i]) % p[i];
        LL ag = p[i] / gcd;
        if(c % gcd) return -1;
        c /= gcd;
        LL t = qmul(xx, c, ag); // 若数据较大，使用快速乘防止溢出
        //LL t = (xx * c) % ag;
        x += t * M; // 得到新的特解
        M *= ag; // 更新LCM
        x = (x % M + M) % M; // 将x更新到最小
    }
    return x;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld %lld", &a[i], &p[i]);
    LL ans = excrt(n, a, p);
    if(ans == -1) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
