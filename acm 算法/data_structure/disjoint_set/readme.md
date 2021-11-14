# 并查集

## 简介

并查集用树形结构模拟集合

主要使用技术

- **路径压缩** 将树结构压扁，防止子树退化成链
- **按秩合并** 令子树大小为秩，将小子树合并到大子树下面

从而支持在常数时间内

- 判断两个元素是否在同一个集合
- 合并两个元素所在的集合

## 例题

### [处理含限制条件的好友请求](https://leetcode-cn.com/problems/process-restricted-friend-requests/)

```cpp
// cpp
const int N = 1e3 + 7;
class Set {
    int n;
    vector<int> pre;
    vector<int> rk;
public:
    Set(int _n):
        n(_n), pre(vector<int>(_n + 1)), rk(vector<int>(_n + 1)) {
            for (int i = 0; i <= n; ++i) rk[i] = 1, pre[i] = i;
        }
    int findPre(int x) {
        return x == pre[x] ? x : pre[x] = findPre(pre[x]);
    }
    void uni(int x, int y) {
        int fx = findPre(x), fy = findPre(y);
        if (fx == fy) return;
        if (rk[fx] <= rk[fy]) pre[fx] = fy, rk[fy] += rk[fx];
        else pre[fy] = fx, rk[fx] += rk[fy];
    }
    bool isCommon(int x, int y) {return findPre(x) == findPre(y);}
};
class Solution {
public:
    bool check(Set* st, int u, int v, int x, int y) {
        return (st->isCommon(u, x) && st->isCommon(v, y) || st->isCommon(u, y) && st->isCommon(v, x));
    }
    vector<bool> friendRequests(int n, vector<vector<int>>& res, vector<vector<int>>& req) {
        Set* st = new Set(n);
        vector<bool> ans;
        for (auto& i: req) {
            int u = i[0], v = i[1];
            bool flag = true;
            for (auto& j: res) {
                int x = j[0], y = j[1];
                if (check(st, u, v, x, y)) {flag = false; break;}
            }
            if (flag) st->uni(u, v);
            ans.push_back(flag);
        }
        return ans;
    }
};
```

