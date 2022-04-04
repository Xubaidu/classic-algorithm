#include <bits/stdc++.h>
#define EPS 1e-6
using namespace std;

const int N1 = 10;
const int N2 = 20;
const int N3 = 107;
const int M1 = 50;
const int M2 = 100;
const int M3 = 10000;
int n;
int Mat[N3][N3];
double x[N3];

void solve()
{
    double mat[N3][N3];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            mat[i][j] = 1.0 * Mat[i][j];
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
    /*
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            printf("%f%c", mat[i][j], " \n"[j == n + 1]);
    */
    for (int i = 1; i <= n; ++i) x[i] = mat[i][n + 1] / mat[i][i];
    for (int i = 1; i <= n; ++i) printf("%.2f%c", x[i], " \n"[i == n]);
    puts("-----");
}

void genData(int N, int M)
{
    n = rand() % N + 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            Mat[i][j] = rand() % M;
    cout << n << endl;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n + 1; ++j)
            printf("%d%c", Mat[i][j], " \n"[j == n + 1]);
    puts("-----");
}

int main()
{
    srand((unsigned)time(nullptr));
    freopen("in.txt", "w", stdout);
    for (int i = 0; i < 10; ++i) {
        if (i < 3) {
            genData(N1, M1);
            solve();
        }
        else if (i < 6) {
            genData(N2, M2);
            solve();
        }
        else {
            genData(N3, M3);
            solve();
        }
    }
    return 0;
}