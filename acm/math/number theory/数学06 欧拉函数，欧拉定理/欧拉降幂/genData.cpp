#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int Na = 1e9 + 1, Nm = 1e8 + 1, Nb = 1e5 + 1;

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

void solve(int a, int m, string &s)
{
    int phim = phi(m);
    int b = 0, f = 0;
    for(auto &i: s) {
        b *= 10, b += i - '0';
        if(b >= phim) f = 1, b %= phim;
    }
    if(f) b += phim; // b < phi(m) 的时候直接快速幂
    LL ans = qpow(a, b, m);
    cout << ans << '\n' << "-----" << endl;
}

int main()
{
    freopen("data.txt", "w", stdout);
    srand((unsigned)time(nullptr));
    for (int i = 0; i < 20; ++i) {
        int a = rand() % Na + 1;
        int m = rand() % Nm + 1;
        int l = rand() % Nb + 1;
        string s(l, 0);
        for (int j = 0; j < l; ++j) s[j] = rand() % 10 + '0';
        cout << a << ' ' << m << ' ' << s << '\n' << "-----" << endl;
        solve(a, m, s);
    }
    return 0;
}