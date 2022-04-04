#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 3e6 + 7;
int n, p;
LL a[N];
int main()
{
    scanf("%d%d", &n, &p);
    a[1] = 1;
    for(int i = 2; i <= n; ++i) {
        LL q = p / i, j = p % i;
        a[i] = (-q % p + p) % p * a[j] % p;
    }
    for(int i = 1; i <= n; ++i)
        printf("%lld%c", a[i], " \n"[i == n]);
    return 0;
}