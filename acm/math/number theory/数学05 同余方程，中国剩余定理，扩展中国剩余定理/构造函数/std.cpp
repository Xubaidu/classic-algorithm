#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
typedef long long LL;
using namespace std;

const int N = 3e5 + 7;
int n, p, k, a[N];
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

int main()
{
    scanf("%d%d%d", &n, &p, &k);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    map<LL, LL> mp;
    for(int i = 1; i <= n; ++i) {
        LL temp = (qpow(a[i], 4, p) - 1LL * k * a[i] % p + p) % p;
        mp[temp]++;
    }
    LL ans = 0;
    for(map<LL, LL>::iterator it = mp.begin(); it != mp.end(); ++it)
        ans += (*it).se * ((*it).se - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}
