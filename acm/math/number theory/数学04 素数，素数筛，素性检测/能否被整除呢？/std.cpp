#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 1e7;
int n, prime[N];
bool vis[N];

void Euler_sieve()
{
    for (int i = 2; i < N; ++i) vis[i] = 1;
    for (int i = 2; i < N; ++i) {
        if (vis[i]) prime[++n] = i;
        for (int j = 1; j <= n && prime[j] * i < N; ++j) {
            vis[prime[j] * i] = 0;
            if (i % prime[j] == 0) break;
        }
    }
}

bool check(int L1, int R1, int L2, int R2)
{
    int p = upper_bound(prime + 1, prime + 1 + n, R1) - prime;
    for (int i = 1; i < p; ++i) {
        LL temp = prime[i];
        int x = 0, y = 0;
        while (temp <= R1) {
            x += R1 / temp - (L1 - 1) / temp;
            temp *= 1LL * prime[i];
        }
        temp = prime[i];
        while (temp <= R2) {
            y += R2 / temp - (L2 - 1) / temp;
            temp *= 1LL * prime[i];
        }
        if (y < x) return 0;
    }
    return 1;
}

void solve(int L1, int R1, int L2, int R2)
{
    int flag = check(L1, R1, L2, R2);
    puts(flag ? "Yes" : "No");
}

int main()
{
    Euler_sieve();
    int l1, r1, l2, r2;
    cin >> l1 >> r1 >> l2 >> r2;
    solve(l1, r1, l2, r2);
    return 0;
}