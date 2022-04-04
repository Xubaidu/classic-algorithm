#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
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

int phi(int m)
{
    int ans = m;
    for(int i = 2; i * i <= m; ++i) {
        if(m % i == 0) {
            ans -= ans / i;
            while(m % i == 0) m /= i;
        }
    }
    if(m > 1) ans -= ans / m;
    return ans;
}
int main()
{
    int a, m;
    a = read(), m = read();
    int phim = phi(m);
    int b = 0, f = 0;
    for(char ch = getchar(); isdigit(ch); ch = getchar()) {
        b *= 10, b += ch - '0';
        if(b >= phim) f = 1, b %= phim;
    }
    if(f) b += phim; //b < phi(m) 的时候直接快速幂
    printf("%d\n", qpow(a, b, m));
    return 0;
}