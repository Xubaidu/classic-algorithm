#include <vector>
#include <iostream>
using namespace std;

class Set {
    int n;
    vector<int> pre;
    vector<int> rk;
public:
    Set(int _n): n(_n), pre(vector<int>(_n + 1)), rk(vector<int>(_n + 1))
    {            
        for (int i = 0; i <= n; ++i) rk[i] = 1, pre[i] = i;
    }
    int findPre(int x)
    {
        return x == pre[x] ? x : pre[x] = findPre(pre[x]);
    }
    void uni(int x, int y)
    {
        int fx = findPre(x), fy = findPre(y);
        if (fx == fy) return;
        if (rk[fx] <= rk[fy]) pre[fx] = fy, rk[fy] += rk[fx];
        else pre[fy] = fx, rk[fx] += rk[fy];
    }
    bool isCommon(int x, int y)
    {
        return findPre(x) == findPre(y);
    }
};

int main()
{
    Set* st = new Set(10);
    st->uni(1, 2), st->uni(2, 3);
    cout << st->isCommon(3, 2) << endl;
    return 0;
}