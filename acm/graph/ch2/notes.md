## 877. 解锁关卡

有 $n$ 个关卡需要通关，但是有 $m$ 条依赖关系，第 $i$ 条为：解锁关卡 $a_i$ 前必须先解锁关卡 $b_i$。

请你为 $n$ 个关卡设置一个合理的通关顺序。若有多解，请输出字典序最小的解。

数据规定 $n\leq 1000,\ m\leq 10000,\ 1\leq a_i,\ b_i\leq n$

---

## 题解

输出字典序最小的拓扑序。建图后用 Kahn 算法，并用优先队列维护入度为 $0$ 的点集。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 7;
int n, m, cnt, ind[N], ans[N];
vector<int> g[N];

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        g[b].push_back(a);
        ind[a]++;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 1; i <= n; ++i) if (!ind[i]) q.push(i);
    while (!q.empty()) {
        int temp = q.top(); q.pop();
        ans[++cnt] = temp;
        for (int i = 0; i < g[temp].size(); ++i) {
            int v = g[temp][i];
            ind[v]--;
            if (!ind[v]) q.push(v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i] << " \n"[i == n];
    }
    return 0;
}
```