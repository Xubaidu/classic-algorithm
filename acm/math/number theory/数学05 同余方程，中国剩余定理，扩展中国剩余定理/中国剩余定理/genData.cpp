#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
typedef long long LL;
using namespace std;

const LL N1 = 10, N2 = 20;
const LL MAXN = 10000000000000000;

LL qpow(LL a, LL b, LL p)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= p;
        a *= a, a %= p, b >>= 1;
    }
    return ans;
}

bool isPrime(LL x)
{
    if(x == 1) return 0;
    for(LL i = 2; i * i <= x; ++i)
        if(x % i == 0) return 0;
    return 1;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

void getXY(LL a, LL b, LL r, LL &x, LL &y)
{
    LL add = b / r;
    while(x < 0) x += add;
    if(b) y = (1 - 1LL * a * x) / b;
}

LL getInv(LL a, LL MOD)
{
    LL x, y;
    LL r = exgcd(a, MOD, x, y);
    getXY(a, MOD, r, x, y);
    return x;
}

void genParameter(int &n, vector<LL>& a, vector<LL>& m)
{
    while(1) {
        n = rand() % 15 + 1;
        if(n < 2) continue;
        else break;
    }
    for(int i = 1; i <= n; ++i) {
        LL x, y;
        unordered_map<int, int> mp1;
        unordered_map<int, int> mp2;
        while(1) {
            x = rand() % N2;
            if(!mp1[x]) {mp1[x] = 1; break;}
            else continue;
        }
        m.pb(x);
        while(1) {
            y = rand() % x;
            if(!mp2[y]) {mp2[y] = 1; break;}
            else continue;
        }
        a.pb(y);
    }
}

void input(int &n, vector<LL>& a, vector<LL>& m)
{
    cout << n << endl;
    for(int i = 0; i < n; ++i) cout << a[i] << ' ' << m[i] << endl;
    cout << "-----" << endl;
}

void output(int &n, vector<LL>& a, vector<LL>& m)
{
    LL M = 1;
    for(int i = 0; i < n; ++i)
        M *= m[i];
    LL x = 0;
    for(LL i = 0; i < n; ++i) {
        LL Mi = M / m[i];
        LL Xi = 1LL * a[i] * getInv(Mi, m[i]) % m[i] * Mi % M;
        //cout << Mi << ' ' << m[i] << ' ' << getInv(Mi, m[i]) << ' ' << Xi << endl;
        x += Xi, x %= M;
    }
    cout << x << endl;
    cout << "-----" << endl;
}

void example()
{
    int n;
    vector<LL> a;
    vector<LL> m;
    n = 3, a = {1, 1, 2}, m = {3, 5, 7};
    input(n, a, m);
    output(n, a, m);
    n = 10;
    a = {1, 2, 4, 6, 10, 12, 16, 18, 22, 28};
    m = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    input(n, a, m);
    output(n, a, m);
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("data.txt", "w", stdout);
    example();
    for(int i = 1; i <= 10; ++i) {
        int n;
        vector<LL> a;
        vector<LL> m;
        genParameter(n, a, m);
        input(n, a, m);
        output(n, a, m);
    }
    return 0;
}
