#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N1 = 1e3;
const int N2 = 1e7;
const int N3 = 1e9;
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

void gen(int &a, int &b, int &m, int N)
{
    while (1) {
        m = rand() % N + 1;
        a = rand() % m + 1;
        b = rand() % m + 1;
        if (a != 1 && b != 1 && __gcd(a, m) == 1) break;
    }
    cout << a << ' ' << b << ' ' << m << '\n' << "-----" << endl;
    cout << solve(a, b, m) << '\n' << "-----" << endl;
}

int main()
{
    srand((unsigned)time(0));
    freopen("data.txt", "w", stdout);
    for (int i = 1; i <= 50; ++i) {
        int a, b, m;
        if (i <= 20) gen(a, b, m, N1);
        else if (i <= 30) gen(a, b, m, N2);
        else gen(a, b, m, N3);
    }

    return 0;
}
