#include <bits/stdc++.h>
#define inf 2147483647
#define fi first
#define se second
#define pii pair<int, int>
typedef long long LL;
using namespace std;


const int N = 100 + 7;
const int MOD = 1e9 + 7;
struct Matrix
{
    int n, m;
    LL mat[N][N];

    Matrix() {}
    Matrix(int _n, int _m): n(_n), m(_m)
    {
        memset(mat, 0, sizeof(mat));
    }
    Matrix operator + (const Matrix& y) const
    {
        Matrix ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.mat[i][j] = mat[i][j] + y.mat[i][j];
        return ans;
    }
    Matrix operator - (const Matrix& y) const
    {
        Matrix ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                ans.mat[i][j] = mat[i][j] - y.mat[i][j];
        return ans;
    }
    Matrix operator * (const Matrix& y) const
    {
        Matrix ans(n, m);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < y.m; ++j)
                for (int k = 0; k < m; ++k)
                    ans.mat[i][j] = (ans.mat[i][j] + mat[i][k] * y.mat[k][j]) % MOD;
        return ans;
    }
    Matrix operator ^ (int y) const
    {
        Matrix ans(n, m);
        Matrix x = *this;
        for (int i = 0; i < n; ++i) ans.mat[i][i] = 1;
        while (y) {
            if (y & 1) ans = ans * x;
            x = x * x, y >>= 1;
        }
        return ans;
    }
    void outp()
    {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                printf("%lld%c", mat[i][j], " \n"[j == m - 1]);
    }
};

int main() {
    Matrix a = Matrix(3, 3);
    a.mat[0][0] = 1, a.mat[0][1] = 0, a.mat[0][2] = 1;
    a.mat[1][0] = 1, a.mat[1][1] = 0, a.mat[1][2] = 0;
    a.mat[2][0] = 0, a.mat[2][1] = 1, a.mat[2][2] = 0;
    const int n = 3;
    int x;
    scanf("%d", &x);
    if (x == 1 || x == 2 || x == 3) cout << 1 << endl;
    else {
        Matrix temp = Matrix(3, 1);
        temp.mat[0][0] = 1, temp.mat[1][0] = 1, temp.mat[2][0] = 1;
        Matrix ans = (a ^ (x - n)) * temp;
        cout << ans.mat[0][0] << endl;
    }
    return 0;
}