#include <bits/stdc++.h>
#define int128 __int128
using namespace std;

string genRandString(int L)
{
    string ans = "";
    ans += '1';
    for (int i = 0; i < L - 2; ++i) ans += '0' + rand() % 2;
    ans += '1';
    return ans;
}

int128 stringToInt(string s)
{
    int128 ans = 0;
    for (int i = 0; i < s.length(); ++i) ans *= 2, ans += s[i] - '0';
    return ans;
}

string intToString(int128 n)
{
    string s1 = "", s2 = "";
    while (n) {
        s1 += n % 10 + '0';
        n /= 10;
    }
    for(int i = s1.length() - 1; i >= 0; --i) s2 += s1[i];
    return s2;
}

int128 randInt128(int128 a, int128 b)
{
    mt19937 eng(time(0));
    uniform_int_distribution<int128> dis(a, b);
    return dis(eng);
}

int128 qmul(int128 a, int128 b, int128 p)
{
    int128 ans = 0;
    while (b) {
        if (b & 1) ans += a, ans %= p;
        a += a, a %= p, b >>= 1;
    }
    return ans;
}

int128 qpow(int128 a, int128 b, int128 p)
{
    int128 ans = 1;
    while (b) {
        if (b & 1) ans = qmul(ans, a, p);
        a = qmul(a, a, p), b >>= 1;
    }
    return ans;
}

bool miller_rabin(int128 n, int k)
{
    int128 t = n - 1;
    int s = 0;
    while (t % 2 == 0) t /= 2, s++;
    for (int i = 0; i < k; ++i) {
        int128 a = randInt128(2, n - 2); // 生成 [2, n-2] 中的随机数 a
        //cout << intToString(a) << endl;
        int128 temp = qpow(a, t, n);
        if (temp % n == 1 || temp % n == n - 1) continue; // 本轮检测通过
        int flag = 0;
        for (int j = 1; j < s; ++j) {
            temp = qmul(temp, temp, n);
            if (temp % n == n - 1) {flag = 1; break;}
        }
        if (flag) continue; // 本轮检测通过
        return 0; // 检测不通过
    }
    return 1;
}

bool isPrime(int128 n)
{
    if (n == 1) return 0; // 判断 1
    if (n == 2) return 1; // 判断 2
    if (n % 2 == 0) return 0; // 判断偶数
    int k = 10;
    return miller_rabin(n, k);
}

void solve()
{
    auto s = clock();
    srand((unsigned)time(0));
    int L = 120;
    int cnt = 0;
    while (cnt <= 10) {
        string s = genRandString(L);
        int128 n = stringToInt(s);
        string N = intToString(n);
        //cout << s << endl;
        //cout << N << endl;
        int flag = isPrime(n);
        //puts(flag == 1 ? "Prime" : "Not prime");
        if (flag == 1) {
            cout << N << endl;
            cnt++;
        }
    }
    auto t = clock();
    cout << (double)(t - s) / CLOCKS_PER_SEC << endl;
}

int main()
{
    solve();
    return 0;
}
/*
20
2 3 5 7 11 13 17 19 23 29
31 33 35 37 39 41 43 45 47 49
*/
