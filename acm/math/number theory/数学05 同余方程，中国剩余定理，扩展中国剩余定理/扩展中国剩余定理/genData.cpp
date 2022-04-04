#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
typedef long long LL;
using namespace std;

const LL N1 = 10, N2 = 100;

LL qpow(LL a, LL b, LL p)
{
    LL ans = 1;
    while (b) {
        if (b & 1) ans *= a, ans %= p;
        a *= a, a %= p, b >>= 1;
    }
    return ans;
}

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

bool isPrime(LL x)
{
    if (x == 1) return 0;
    for (LL i = 2; i * i <= x; ++i)
        if (x % i == 0) return 0;
    return 1;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if (!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

LL getInv(LL a, LL MOD)
{
    LL x, y;
    LL r = exgcd(a, MOD, x, y);
    while (x < 0) x += MOD;
    y = (1 - a * x) / MOD;
    return x;
}

LL excrt(LL n, vector<LL>& a, vector<LL>& m)
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

void genParameter(LL& n, vector<LL>& a, vector<LL>& m)
{
    map<LL, LL> mp;
    while (1) {
        n = rand() % N1;
        if (n < 2) continue;
        else break;
    }
    for (int i = 0; i < n; ++i) {
        LL x = 0, y = 0;
        while (1) {
            x = rand() % N2;
            if (x >= 2 && !mp[x]) {mp[x] = 1; break;}
        }
        m.pb(x);
        mp.clear();
        while (1) {
            y = rand() % x;
            if (y >= 2 && !mp[y]) {mp[y] = 1; break;}
        }
        a.pb(y);
    }
}

void input(LL& n, vector<LL>& a, vector<LL>& m)
{
    cout << n << endl;
    for (LL i = 0; i < n; ++i)
        cout << a[i] << ' ' << m[i] << endl;
    cout << "-----" << endl;
}

void output(LL& n, vector<LL>& a, vector<LL>& m)
{
    LL ans = excrt(n, a, m);
    if (ans == -1) puts("-1");
    else printf("%d\n", ans);
    cout << "-----" << endl;
}

void example()
{
    LL n = 3;
    vector<LL> a = {6, 9, 17};
    vector<LL> m = {11, 25, 33};
    input(n, a, m);
    output(n, a, m);
}

int main()
{
    srand((unsigned)time(NULL));
    //freopen("data.txt", "w", stdout);
    example();
    for(int i = 1; i <= 100; ++i) {
        LL n = 0;
        vector<LL> a; a.clear();
        vector<LL> m; m.clear();
        genParameter(n, a, m);
        input(n, a, m);
        output(n, a, m);
    }
    return 0;
}
