#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 4e4 + 1;
int n, prime[N], phi[N], vis[N], dp[N];
int Euler_sieve()
{
    int cnt = 0;
    for(int i = 2; i < N; ++i) vis[i] = 1;
    for(int i = 2; i < N; ++i){
        if(vis[i]) prime[++cnt] = i, phi[i] = i - 1; //素数的欧拉函数值为 i - 1
        for(int j = 1; j <= cnt && prime[j] * i < N; ++j){
            vis[prime[j] * i] = 0;
            phi[prime[j] * i] = (prime[j] - 1) * phi[i];
            if(i % prime[j] == 0) {
                phi[prime[j] * i] = prime[j] * phi[i];
                break;
            }
        }
    }
    return cnt;
}

void solve(int n)
{
    dp[1] = 0;
    dp[2] = 3;
    for (int i = 3; i < N; ++i)
        dp[i] = dp[i - 1] + 2 * phi[i - 1];
    cout << dp[n] << '\n' << "-----" << endl;
}

int main()
{
    int cnt = Euler_sieve();
    freopen("data.txt", "w", stdout);
    srand((unsigned)time(nullptr));
    map<int, int> mp;
    for (int i = 0; i < 30; ++i) {
        int n;
        while (1) {
            if (i < 5) n = rand() % 20 + 1;
            else if (i < 15) n = rand() % 100 + 1;
            else n = rand() % N + 1;
            if (!mp[n]) {mp[n] = 1; break;}
        }
        cout << n << '\n' << "-----" << endl;
        solve(n);
    }
    return 0;
}