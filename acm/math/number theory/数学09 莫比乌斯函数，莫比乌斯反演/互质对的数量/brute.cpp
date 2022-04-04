#include <bits/stdc++.h>
#include <algorithm>
typedef long long LL;
using namespace std;

LL gcd(LL a, LL b) {
    return b ? gcd(b, a % b) : a;
}

int main()
{
    freopen("in.txt", "r", stdin);
    LL a, b;
    while (cin >> a >> b) {
        string s;
        cin >> s;
        LL ans = 0;
        cin >> ans >> s;
        int cnt = 0;
        for (int i = 1; i <= a; ++i) {
            for (int j = 1; j <= b; ++j)
                if (gcd(i, j) == 1) cnt++;
        }
        cout << ((cnt == ans) ? "Yes" : "No") << endl;
    }
    return 0;
}