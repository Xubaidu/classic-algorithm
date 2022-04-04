#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 1e4;
const int P = 20007;

LL a[N];
void solve(int n, int p)
{
    a[1] = 1;
    for(int i = 2; i <= n; ++i) {
        LL q = p / i, j = p % i;
        a[i] = (-q % p + p) % p * a[j] % p;
    }
    for(int i = 1; i <= n; ++i)
        printf("%lld%c", a[i], " \n"[i == n]);
    cout << "-----" << endl;
}

void example(int n, int p)
{
    cout << n << ' ' << p << endl;
    cout << "-----" << endl;
    solve(n, p);
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
    example(7, 11);
    example(10, 13);
    for(int i = 1; i <= 5; ++i) {
        LL n = rand() % N + 1;
        LL p;
        while(1) {
            p = rand() % P;
            if(check(p)) break;
        }
        cout << n << ' ' << p << endl;
        cout << "-----" << endl;
        solve(n, p);
    }
    return 0;
}
