#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N1 = 1e2, N2 = 1e3, N3 = 1e4, N4 = 3e5 + 7;
const int P = 1e9 + 1;
int n, p, k, a[N4];

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

bool isPrime(int x)
{
    if(x == 1) return 0;
    for(int i = 2; i * i <= x; ++i)
        if(x % i == 0) return 0;
    return 1;
}

void genParameter(int &n, int &p, int &k, int *a, int N)
{
    while(1) {
        n = rand() % N + 1;
        if(n >= 2) break;
    }
    while(1) {
        p = rand() % P;
        if(p >= 2 && isPrime(p)) break;
    }
    k = rand() % p;
    for(int i = 1; i <= n; ++i) a[i] = rand() % p;
}

void input(int &n, int &p, int &k, int *a)
{
    printf("%d %d %d\n", n, p, k);
    for(int i = 1; i <= n; ++i) printf("%d%c", a[i], " \n"[i == n]);
    cout << "-----" << endl;
}

void solve(int n, int p, int k, int *a)
{
    unordered_map<LL, LL> mp;
    for(int i = 1; i <= n; ++i) {
        LL temp = (qpow(a[i], 4, p) - 1LL * k * a[i] % p + p) % p;
        mp[temp]++;
    }
    LL ans = 0;
    for(auto &i: mp) ans += i.se * (i.se - 1) / 2;
    printf("%lld\n", ans);
    cout << "-----" << endl;
}

void example()
{
    n = 3, p = 3, k = 0, a[1] = 0, a[2] = 1, a[3] = 2;
    input(n, p, k, a);
    solve(n, p, k, a);
    n = 6, p = 7, k = 2, a[1] = 1, a[2] = 2, a[3] = 3, a[4] = 4, a[5] = 5, a[6] = 6;
    input(n, p, k, a);
    solve(n, p, k, a);
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("data.txt", "w", stdout);
    example();
    for(int i = 1; i <= 5; ++i) {
        if(i == 1) genParameter(n, p, k, a, N1);
        else if(i <= 3) genParameter(n, p, k, a, N2);
        else if(i <= 4) genParameter(n, p, k, a, N3);
        else genParameter(n, p, k, a, N4);
        input(n, p, k, a);
        solve(n, p, k, a);
    }
    return 0;
}
