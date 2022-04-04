#include <bits/stdc++.h>
#define EPS 1e-7
using namespace std;

const int N = 1e2 + 7;
int n;
double mat[N][N], x[N];

void Gauss_jordan()
{
    for (int i = 1; i <= n; ++i) {
        // 在第 i 列寻找最大的数值作为主元
        int m = i;
        for (int j = i + 1; j <= n; ++j)
            if (fabs(mat[j][i]) > fabs(mat[m][i])) m = j;

        // 第 i 列全为 0，xi 无解
        if (fabs(mat[m][i]) < EPS) {
            printf("No Solution\n");
            return;
        }
        
        // 交换行
        if (m != i) swap(mat[i], mat[m]);

        //对每行进行消元，首项不一定为1
        for (int j = 1; j <= n; ++j)
            if (j != i) {
                double temp = mat[j][i] / mat[i][i];
                for (int k = i; k <= n + 1; ++k)
                    mat[j][k] -= temp * mat[i][k];
            }

    }
    for (int i = 1; i <= n; ++i) x[i] = mat[i][n + 1] / mat[i][i];
    for (int i = 1; i <= n; ++i) printf("%.2f%c", x[i], " \n"[i == n]);
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            scanf("%lf", &mat[i][j]);
    Gauss_jordan();
    return 0;
}
/*
3
1 3 4 26
1 4 7 41
9 3 2 26

1 3 4
*/
