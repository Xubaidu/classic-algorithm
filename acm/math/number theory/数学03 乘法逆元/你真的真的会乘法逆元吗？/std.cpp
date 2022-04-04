#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 5e6 + 7;
LL n, p, k, a[N], b[N], m[N];

LL read()
{
    char c = getchar();
    LL ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}
LL qpow(LL a, LL b, LL m)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}
LL getInv(LL a, LL m) {return qpow(a, m - 2, m);}
int main()
{
    n = read(), p = read(), k = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    m[0] = 1;
    for(int i = 1; i <= n; ++i)
        m[i] = a[i] * m[i - 1], m[i] %= p;
    LL M = getInv(m[n], p);
    for(int i = n; i >= 1; --i) {
        b[i] = M * m[i - 1] % p;
        M *= a[i], M %= p;
    }
    LL ans = 0, temp = 1;
    for(int i = 1; i <= n; ++i) {
        temp *= k, temp %= p;
        ans += temp * b[i], ans %= p;
    }
    printf("%lld\n", ans);
    return 0;
}