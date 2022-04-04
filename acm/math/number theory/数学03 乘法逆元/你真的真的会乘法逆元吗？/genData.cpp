#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 1e5;
const int P = 1e9;
const int K = 1e9;

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

int n, p, k, a[N];
LL b[N], m[N];
void solve(int n, int p, int k, int *a)
{
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
    cout << "-----" << endl;
}

void example(int n, int p, int k, int *a)
{
    cout << n << ' ' << p << ' ' << k << endl;
    for(int i = 1; i <= n; ++i)
        printf("%d%c", a[i], " \n"[i == n]);
    cout << "-----" << endl;
    solve(n, p, k, a);
}

bool check(int n)
{
    if(n == 1) return 0; 
    for(int i = 2; i * i <= n; ++i)
        if(n % i == 0) return 0;
    return 1;
}
int main()
{
    srand((unsigned)time(NULL));
    freopen("data.txt", "w", stdout);
    n = 10, p = 5, k = 7;
    for(int i = 1; i <= n; ++i) {
        while(1) {
            a[i] = rand() % p;
            if(a[i] >= 1) break;
        }
    }
    example(n, p, k, a);
    n = 6, p = 233, k = 42;
    a[1] = 1, a[2] = 4, a[3] = 2, a[4] = 8, a[5] = 5, a[6] = 7;
    example(n, p, k, a);
    for(int i = 1; i <= 5; ++i) {
        LL n = rand() % N + 1;
        LL p, k;
        while(1) {
            p = rand() % P;
            if(check(p) && p >= 2) break;
        }
        while(1) {
            k = rand() % K;
            if(k >= 2) break;
        }
        cout << n << ' ' << p << ' ' << k << endl;
        for(int i = 1; i <= n; ++i) {
            while(1) {
                a[i] = rand() % p;
                if(a[i] >= 1) break;
            }
            printf("%d%c", a[i], " \n"[i == n]);
        }
        cout << "-----" << endl;
        solve(n, p, k, a);
    }
    return 0;
}
