#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x); // y 的值被修改为 x', x 的值被修改为 y'
    y -= 1LL * (a / b) * x;
    return r;
}

int getInv(int a, int m)
{
    int x, y;
    int r = exgcd(a, m, x, y);
    if(r != 1) return -1; // 不存在逆元
    while(x < 0) x += m;
    return x % m;
}

int solve(int a, int b, int m)
{
    return 1LL * b * getInv(a, m) % m;
}

int main()
{
    int a, b, m; cin >> a >> b >> m;
    cout << solve(a, b, m) << endl;

    return 0;
}
