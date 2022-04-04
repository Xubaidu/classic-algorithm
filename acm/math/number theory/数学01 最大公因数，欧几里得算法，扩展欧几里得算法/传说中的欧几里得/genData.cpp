#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int M = 1 << 31;
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
    if(b) y = (1 - a * x) / b;
    return {x, y};
}
void solve(LL a, LL b)
{
    int x, y;
    int r = exgcd(a, b, x, y);
    if(r != 1) puts("sorry");
    else {
        pair<int, int> p = getXY(a, b, r, x, y);
        printf("%d %d\n", p.first, p.second);
    }
    cout << "-----" << endl;
}

int main()
{
    srand((unsigned)time(NULL));
    freopen("data.txt", "w", stdout);
    cout << 1 << ' ' << 2 << endl;
    cout << "-----" << endl;
    solve(1, 2);
    cout << 2 << ' ' << 5 << endl;
    cout << "-----" << endl;
    solve(2, 5);
    for(int i = 1; i <= 100; ++i) {
        LL a = rand() % M, b = rand() % M;
        cout << a << ' ' << b << endl;
        cout << "-----" << endl;
        solve(a, b);
    }
    return 0;
}
