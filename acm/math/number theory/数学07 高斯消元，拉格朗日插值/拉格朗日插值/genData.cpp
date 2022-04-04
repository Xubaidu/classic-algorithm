#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N1 = 10;
const int N2 = 100;
const int N3 = 1000;
const int M1 = 20;
const int M2 = 100;
const int M3 = 998244353;
const int MOD = 998244353;

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

LL k, n, x[N3], y[N3];

void solve()
{
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
    printf("%lld\n-----\n", res);
}

void genData(int N, int M)
{
    map<LL, int> mp;
    n = rand() % (N - 1) + 2;
    for (int i = 1; i <= n; ++i) {
        int temp1, temp2;
        while (1) {
            temp1 = rand() % M;
            if (!mp[temp1]) {
                mp[temp1] = 1;
                x[i] = temp1, y[i] = rand() % M;
                break;
            }
        }
    }
    while (1) {
        k = rand() % M;
        if (!mp[k]) {
            mp[k] = 1;
            break;
        }
    }
    cout << n << ' ' << k << endl;
    for (int i = 1; i <= n; ++i) cout << x[i] << ' ' << y[i] << endl;
    puts("-----");
}


int main()
{
    srand((unsigned)time(nullptr));
    freopen("in.txt", "w", stdout);
    for (int i = 0; i < 10; ++i) {
        if (i < 3) genData(N1, M1);
        else if (i < 6) genData(N2, M2);
        else genData(N3, M3);
        solve();
    }
    return 0;
}