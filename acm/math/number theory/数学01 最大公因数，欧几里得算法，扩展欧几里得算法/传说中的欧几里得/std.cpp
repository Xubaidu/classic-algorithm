#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

int qpow(int a, int b, int m)
{
    int ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}
int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}
pair<int, int> getXY(int a, int b, int r, int x, int y)
{
    int add = b / r;
    while(x < 0) x += add;
    x %= add;
    if(b) y = (1 - 1LL * a * x) / b;
    return {x, y};
}
int main()
{
    int a, b;
    while(~scanf("%d%d", &a, &b)) {
        int x, y;
        int r = exgcd(a, b, x, y);
        if(r != 1) puts("sorry");
        else {
            pair<int, int> p = getXY(a, b, r, x, y);
            printf("%d %d\n", p.first, p.second);
        }
    }
    return 0;
}
