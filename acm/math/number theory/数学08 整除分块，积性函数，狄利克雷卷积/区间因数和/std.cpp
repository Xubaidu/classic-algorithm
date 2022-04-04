#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

LL calc(LL n)
{
    LL ans = 0;
    for (LL l = 1, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans += (r - l + 1) * (l + r) * (n / l) / 2;
    }
    return ans;
}

int main()
{
    LL L, R;
    cin >> L >> R;
    cout << calc(R) - calc(L - 1) << endl;
    return 0;
}