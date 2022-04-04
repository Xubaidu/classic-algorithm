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
    freopen("data.txt", "w", stdout);
    srand((unsigned)time(0));
    Euler_sieve();
    int l1, r1, l2, r2;
    for (int i = 1; i <= 30; ++i) {
        while (1) {
            r1 = rand() % N + 1;
            l1 = rand() % (r1 - 2) + 1;
            if (r1 > l1) break;
        }
        while (1) {
            r2 = rand() % N + 1;
            l2 = rand() % (r1 - 2) + 1;
            if (r1 > l1) break;
        }
        cout << l1 << ' ' << r1 << ' ' << l2 << ' ' << r2 << endl;
        cout << "-----" << endl;
        solve(l1, r1, l2, r2);
        cout << "-----" << endl;

    }
    return 0;
}