## Algorithm Template

## Chenyang\ Xu

---

## 预处理

- 头文件与宏定义

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define fi first
#define se second
#define pii pair<int, int>
typedef long long LL;
const int dx[]={0, -1, 0, 1, 0, -1, -1, 1, 1};
const int dy[]={0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N=1e3+7;
const int mod=998244353;
const int base=131;
using namespace std;
```

- 快读快写

```cpp
inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}
inline void write(int x)
{
    if(x < 0) {putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
```

- 离散化

如果一个序列，我们不关心各个元素具体值，只关心其大小关系，那么可以采用离散化策略，将原序列离散化为一个紧凑的新序列。
构造辅助数组 $b[N]$，这样一来，$a[i]$ 中所有的元素都被一一对应地映射到 $1\sim n$

```cpp
for(int i = 1; i <= n; ++i) a[i] = read(), b[i] = a[i];
sort(b + 1, b + 1 + n);
int L = unique(b + 1, b + 1 + n) - (b + 1);
for(int i = 1; i <= L; ++i)
    a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
```

## 数学

### 组合数取模

- 基于动态规划递推 $C_{n}^{k}=C_{n-1}^{k-1}+C_{n-1}^{k}$

适用于 $n$ 较小的时候，$p$ 随意。
  
```cpp
//初始化组合数并取模
void C_ini(int n, int p)
{
    for(int i = 0; i <= n; ++i){
        C[i][0] = C[i][i] = 1;
            for(int j = 1; j < i; ++j)
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % p;
    }
}
```

- 基于组合数公式 $C_{n}^{m}=\frac{n!}{m!(n-m)!}$

用费马小定理求逆元即可

适用于 $n$ 相对小（可以打阶乘表），$p$ 为素数的时候。

```cpp
LL fac[MAXN], inv_fac[MAXN];
LL qpow(LL a, LL b)
{
    b %= MOD - 1;
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}
LL getInv(LL x) {return qpow(x, MOD - 2);}
LL Add(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return (a + b) % MOD;}
LL Sub(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return (a - b + MOD) % MOD;}
LL Mul(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return a * b % MOD;}
LL Div(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return b * getInv(a) % MOD;}
void ini()
{
    fac[0] = 1;
    for(int i = 1; i < MAXN; ++i) fac[i] = Mul(fac[i - 1], i);
    inv_fac[MAXN - 1] = getInv(fac[MAXN - 1]);
    for(int i = MAXN - 2; i >= 0; --i) inv_fac[i] = Mul(inv_fac[i + 1], i + 1);
}
LL getC(int k, int i)
{
    return Mul(fac[k], Mul(inv_fac[i], inv_fac[k - i]));
}
```

- 基于卢卡斯定理

$$
\binom{n}{m}\mod\ p=\binom{\left \lfloor \frac{n}{p}\right \rfloor}{\left \lfloor \frac{m}{p}\right \rfloor}\cdot \binom{n\ mod\ p}{m\ mod\ p}\ mod\ p
$$

适用于 $n$ 很大，$p$ 为素数的时候。

```cpp
LL Lucas(LL n, LL m, LL p)
{
    return m ? Lucas(n / p, m / p, p) * (C[n % p][m % p] % p) % p : 1;
}
```

### 扩展欧几里得

求 $ax+by=c$ 的整数解。其中，若 $c|gcd(a,\ b)$，方程有解，否则无解。

```cpp
int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x);//y的值被修改为x'，x的值被修改为y'
    y -= (a / b) * x;
    return r;
}
```

### 中国剩余定理

给定线性同余方程组
$$
\left\{\begin{matrix}
x_{1}\equiv a_{1}\ (mod\ m_{1})
\\x_{2}\equiv a_{2}\ (mod\ m_{2})
\\...
\\x_{n}\equiv a_{n}\ (mod\ m_{n})
\end{matrix}\right.
$$

保证 $m_{1},\ m_{2},\ ...\ m_{n}$ 两两互质

#### $CRT\ code$

```cpp
int n, a[N], p[N];
LL M = 1;

int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x);//y的值被修改为x'，x的值被修改为y'
    y -= (a / b) * x;
    return r;
}

int inv(int a, int p)
{
    int x = 0, y = 0;
    int gcd = exgcd(a, p, x, y);
    while(x < 0) x += p;
    return x;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &p[i]);
    for(int i = 1; i <= n; ++i)
        M *= p[i];
    int x = 0;
    for(int i = 1; i <= n; ++i){
        x += a[i] * inv(M / p[i], p[i]) * M / p[i], x %= M;
    }
    printf("%d\n", x);
    return 0;
}
```

### 扩展中国剩余定理

给定线性同余方程组
$$
\left\{\begin{matrix}
x_{1}\equiv a_{1}\ (mod\ m_{1})
\\x_{2}\equiv a_{2}\ (mod\ m_{2})
\\...
\\x_{n}\equiv a_{n}\ (mod\ m_{n})
\end{matrix}\right.
$$

$m_{1},\ m_{2},\ ...\ m_{n}$ 不一定两两互质

#### $EXCRT\ code$

处理到第 $k$ 个方程时，具体求 $x_{2}$ 的过程如下

因为

$$
x_{2} = x_{1} + t\cdot m
$$

其中

$$
m = [m_{1}m_{2}...m_{k - 1}]
$$

所以即在方程中求 $t$

$$
t\cdot m\equiv a_{k} - x_{1}\ (mod\ m_{k})
$$

先用扩欧求方程

$$
t\cdot m + q\cdot m_{k} = (m,\ m_{k})
$$

的特解 $t_{0}$，然后自乘系数

$$
\frac{a_{k} - x_{1}}{(m,\ m_{k})}
$$

进而得到通解

$$
t = t_{0}\cdot \frac{a_{k} - x_{1}}{(m,\ m_{k})} + q\cdot \frac{m_{k}}{(m,\ m_{k})},\ q\in \mathbb{Z}
$$

为了防止溢出，将 $t$ 取模数 $\frac{m_{k}}{(m,\ m_{k})}$ 至最小非负数

于是得到

$$
x_{2} = x_{1} + t\cdot m
$$

```cpp
int n;
LL a[N], p[N];

LL qmul(LL a, LL b, LL mod)
{
    LL res = 0;
    while(b > 0) {
        if(b & 1) res += a, res %= mod;
        a += a, a %= mod;
        b >>= 1;
    }
    return res;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return r;
}

LL excrt(LL n, LL *a, LL *p)
{
    LL M = p[1];//维护LCM
    LL x = a[1];//维护解
    for(int i = 2; i <= n; ++i){
        LL xx = 0, yy = 0;
        LL gcd = exgcd(M, p[i], xx, yy);
        LL c = (a[i] - x % p[i] + p[i]) % p[i];
        LL ag = p[i] / gcd;
        if(c % gcd) return -1;
        c /= gcd;
        //若数据较大，使用快速乘防止溢出
        //LL t = qmul(xx, c, ag);
        LL t = (xx * c) % ag;
        x += t * M;//得到新的特解
        M *= ag;//更新LCM
        x = (x % M + M) % M;//将x更新到最小
    }
    return x;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld %lld", &p[i], &a[i]);
    LL ans = excrt(n, a, p);
    if(ans == -1) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}
```

### 矩阵

- 矩阵类

```cpp
const int N = 100 + 7;
const int mod = 998244353;
struct Matrix
{
    int n, m;
    LL a[N][N];
    Matrix() {}
    Matrix(int nn, int mm) {n = nn, m = mm; memset(a, 0, sizeof(a));}//不memset，则ans对象传递
    Matrix operator + (const Matrix& y) const
    {
        Matrix ans(n, m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                ans.a[i][j] = a[i][j] + y.a[i][j];
        return ans;
    }
    Matrix operator - (const Matrix& y) const
    {
        Matrix ans(n, m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                ans.a[i][j] = a[i][j] - y.a[i][j];
        return ans;
    }
    Matrix operator * (const Matrix& y) const
    {
        Matrix ans(n, y.m);
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= y.m; ++j)
                for(int k = 1; k <= m; ++k)
                    ans.a[i][j] += a[i][k] * y.a[k][j], ans.a[i][j] %= mod;
        return ans;
    }
    Matrix operator ^ (int y) const
    {
        Matrix ans(n, m);
        Matrix x = *this;//this是指针，指向此对象
        for(int i = 1; i <= n; ++i)
            ans.a[i][i] = 1;
        while(y) {
            if(y & 1) ans = x * ans;
            x = x * x, y >>= 1;
        }
        return ans;
    }
    void outp()
    {
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= m; ++j)
                printf("%lld%c", a[i][j], " \n"[j == m]);
        puts("");
    }
};
```

- 矩阵快速幂

```cpp
Matrix operator ^ (int y) const
{
    Matrix ans(n, m);
    Matrix x = *this;//this是指针，指向此对象
    for(int i = 1; i <= n; ++i)
        ans.a[i][i] = 1;
    while(y) {
        if(y & 1) ans = x * ans;
        x = x * x, y >>= 1;
    }
    return ans;
}
```

- 矩阵加速

```cpp
LL matrix_speedup(Matrix A, Matrix F, int t, int n)
{
    Matrix ans = A ^ (t - n);
    ans = ans * F;
    return ans.a[1][1];
}

LL x[N], y[N];
int main()
{
    int n, t; cin >> n >> t;
    for(int i = 1; i <= n; ++i) cin >> x[i];//读入系数
    for(int i = 1; i <= n; ++i) cin >> y[i];//读入初始值
    puts("");
    Matrix A(n, n), F(n, 1);
    for(int i = n; i >= 1; --i) F.a[i][1] = y[n - i + 1];//构造F(1)
    for(int i = 1; i <= n; ++i) A.a[1][i] = x[i];
    for(int i = 2; i <= n; ++i) A.a[i][i - 1] = 1;
    if(t > n) cout << matrix_speedup(A, F, t, n) << endl;
    else cout << F.a[t][1] << endl;
    return 0;
}
/*
2 4
1 1
1 1
*/
/*
样例为斐波那契第四项，输出3
*/
```

### 高斯消元

```cpp
void Gauss_jordan()
{
    for(int i = 1; i <= n; ++i){
        //在第i列寻找最大的数值作为主元
        int m = i;
        for(int j = i + 1; j <= n; ++j)
            if(fabs(mat[j][i]) > fabs(mat[m][i])) m = j;
        if(fabs(mat[m][i]) < eps) {printf("No Solution\n"); return;}//第i列全为0，xi无解
        if(m != i) swap(mat[i], mat[m]);

        //对每行进行消元，首项不一定为1
        for(int j = 1; j <= n; ++j)
            if(j != i){
                double temp = mat[j][i] / mat[i][i];
                for(int k = i; k <= n + 1; ++k)
                    mat[j][k] -= temp * mat[i][k];
            }
    }
    for(int i = 1; i <= n; ++i) x[i] = mat[i][n + 1] / mat[i][i];
    for(int i = 1; i <= n; ++i) printf("%.2f\n", x[i]);
}
int main()
{
    n = read();
    for(int i = 1; i <= n; ++i)
        for(int j = 1; j <= n + 1; ++j)
            scanf("%lf", &mat[i][j]);
    Gauss_jordan();
    return 0;
}
/*
3
1 3 4 5
1 4 7 3
9 3 2 2
*/
```

### 快速幂与逆元

- 快速幂 $+$ 费马小定理求逆元

```cpp
inline LL qpow(LL a, LL b)//快速幂取模
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= MOD;
        b >>= 1;
        a *= a, a %= MOD;
    }
    return ans;
}
LL Inv(LL x) {return qpow(x, MOD - 2);}
```

- 扩欧求逆元

```cpp
//扩欧求逆元
int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x);//y的值被修改为x'，x的值被修改为y'
    y -= (a / b) * x;
    return r;
}

int Inv(int a, int p)
{
    int x = 0, y = 0;
    int gcd = exgcd(a, p, x, y);
    while(x < 0) x += p;
    return x;
}
int main()
{
    a = read(), p = read();
    printf("%d\n", inv(a, p));
    return 0;
}
```

- 线性递推逆元

```cpp
//线性递推逆元，求1到n内所有值在模p意义下的逆元
int n, p;
LL inv[N];

int main()
{
    n = read(), p = read();
    inv[1] = 1;
    printf("%d\n", inv[1]);
    for(int i = 2;i <= n; ++i){
        inv[i] = (LL)p - (p / i) * inv[p % i] % p;
        write(inv[i]), puts("");
    }
    return 0;
}
```

- 阶乘递推，阶乘逆元递推，组合数逆元
  
```cpp
LL fac[MAXN], inv_fac[MAXN];
LL qpow(LL a, LL b)
{
    b %= MOD - 1;
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}
LL getInv(LL x) {return qpow(x, MOD - 2);}
LL Add(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return (a + b) % MOD;}
LL Sub(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return (a - b + MOD) % MOD;}
LL Mul(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return a * b % MOD;}
LL Div(LL a, LL b) {a = (a % MOD + MOD) % MOD; b = (b % MOD + MOD) % MOD; return b * getInv(a) % MOD;}
void ini()
{
    fac[0] = 1;
    for(int i = 1; i < MAXN; ++i) fac[i] = Mul(fac[i - 1], i);
    inv_fac[MAXN - 1] = getInv(fac[MAXN - 1]);
    for(int i = MAXN - 2; i >= 0; --i) inv_fac[i] = Mul(inv_fac[i + 1], i + 1);
}
LL getC(int k, int i)
{
    return Mul(fac[k], Mul(inv_fac[i], inv_fac[k - i]));
}
```

### 筛法

- 埃氏筛

$code$

```cpp
int n;
bool vis[N];
void getPrime()
{
    for(int i = 2; i <= n; ++i) vis[i] = 1;
    for(int i = 2; i * i <= n; ++i){
        if(vis[i]){
            for(int j = i * i; j <= n; j += i)
                vis[j] = 0;
        }
    }
}
```

复杂度 $O(nlglgn)$

- 欧拉筛
  
```cpp
int n, prime[N];
bool vis[N];
int Euler_sieve()
{
    int cnt = 0;//length of prime table
    for(int i = 2; i <= n; ++i)
        vis[i] = 1;
    for(int i = 2; i <= n; ++i){
        if(vis[i]) prime[++cnt] = i;
        for(int j = 1; j <= cnt && prime[j] * i <= n; ++j){
            vis[prime[j] * i] = 0;
            if(i % prime[j] == 0) break;
        }
    }
    return cnt;
}
```

复杂度 $O(n)$

### 拉格朗日插值

给定 $n+1$ 个点，对于每一个点都可以得出一个 $n$ 次多项式函数，将 $n+1$ 个 $n$ 次多项式函数求和

由 $k$ 点在该函数 $x_{k}$ 处的值便可以近似目标函数值$y_{k}$

复杂度 $O(n^2)$

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define eps 1e-9
#define fi first
#define se second
#define LL long long
#define pii pair<int, int>
using namespace std;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N = 2e3 + 10;
const LL MOD = 998244353;
LL n, k, x[N], y[N];

//快读快写
inline LL read()
{
    char c = getchar();
    LL ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c=getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}
inline void write(LL x)
{
    if(x < 0) {putchar('-'); x = -x;}
    if(x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

//Lagrange interpolation polynomial
LL qpow(LL a, LL b)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}
LL Inv(LL x) {return qpow(x, MOD - 2);}
LL add(LL x, LL y) {return ((x + y) % MOD + MOD) % MOD;}
LL mul(LL x, LL y) {return x * y % MOD;}
LL lagrange(LL k)
{
    LL ans = 0;
    for(int i = 1; i <= n; ++i){
        LL s1 = 1, s2 = 1;
        for(int j = 1; j <= n; ++j)
            if(j != i) {
                s1 = mul(s1, add(k, -x[j]));
                s2 = mul(s2, add(x[i], -x[j]));
            }
        ans = add(ans, mul(y[i], mul(s1, Inv(s2))));
    }
    return ans;
}
int main()
{
    n = read(), k = read();
    for(int i = 1; i <= n; ++i) x[i] =read(), y[i] = read();
    write(lagrange(k));
}

```

### $FFT$

```cpp
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
const double PI = acos(-1);
const int N = 3e6 + 7;
using namespace std;
int n, m, r[N];

struct CP
{
    double x, y;
    CP() {}
    CP(double _x, double _y) {x = _x, y = _y;}
    CP operator + (const CP &A) const {return CP(x + A.x, y + A.y); }
    CP operator - (const CP &A) const {return CP(x - A.x, y - A.y); }
    CP operator * (const CP &A) const {return CP(x * A.x - y * A.y, x * A.y + y * A.x); }
}f[N], g[N], temp[N];

int read()
{
    int flag = 1, ans = 0;
    char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') flag = -1; ch = getchar(); }
    while(isdigit(ch)) {ans = ans * 10 + ch - '0'; ch = getchar(); }
    return ans * flag; 
}

void FFT(CP *f, int n, bool flag)
{
    for(int i = 0; i < n; ++i)
        if(i < r[i]) swap(f[i], f[r[i]]);
    for(int i = 2; i <= n; i <<= 1){//枚举区间长度
        int len = i >> 1;//待合并的区间长度
        CP tg(cos(2 * PI / i), sin(2 * PI / i));
        if(!flag) tg.y *= -1;
        for(int j = 0; j < n; j += i){//枚举起始点
            CP buf(1, 0);
            for(int k = j; k < j + len; ++k){
                CP mid = buf * f[k + len];
                f[k + len] = f[k] - mid;
                f[k] = f[k] + mid;
                buf = buf * tg;
            }
        }
    } 
}

int main()
{
    n = read(), m = read();
    for(int i = 0; i <= n; ++i) scanf("%lf", &f[i].x);
    for(int i = 0; i <= m; ++i) scanf("%lf", &g[i].x);
    for(m += n, n=1; n <= m; n <<= 1);
    for (int i = 0; i < n; ++i)
        r[i] = (r[i >> 1] >> 1 | ((i & 1) ? n >> 1 : 0));
    FFT(f, n, 1), FFT(g, n, 1);//DFT
    for(int i = 0; i < n; ++i) f[i] = f[i] * g[i];
    FFT(f, n, 0);//IDFT
    for(int i = 0; i <= m; ++i) printf("%d%c", (int)(f[i].x / n + 0.5), " \n"[i == m]);//四舍五入
    return 0;
}
```

## 数据结构

### 并查集

```cpp
//并查集
int pre[N], rk[N];
void init(int n) {for(int i = 0; i <= n; ++i) pre[i] = i, rk[i] = 1;}
int findPre(int x) {return x == pre[x] ? x : (pre[x] = findPre(pre[x]));} // path compression
void uni(int x, int y)
{
    int fx = findPre(x), fy = findPre(y);
    if(fx == fy) return;
    if(rk[fx] <= rk[fy]) pre[fx] = fy;
    else pre[fy] = fx;
    if(rk[fx] == rk[fy]) rk[fy]++; // merge by rank
}
bool isCommon(int x, int y) {return findPre(x) == findPre(y);}
```

### $Trie$

>$Trie$是一棵字典树，可以去重地维护多个字符串及其前缀。插入效率和查找效率均为$O_{L}$，$L$为插入字符串的长度。每个节点下设多个节点（一般为$26$个节点）存储字符，根节点不存储字符。

$code:$

```cpp
const int N = 5e3 + 7;
struct trie
{
    int node[N][27], num = 0;
    bool ed[N];
    void strInsert(char *str)
    {
        int p = 0;
        for(int i = 1; str[i]; ++i){
            int idx = str[i] - 'a' + 1;
            if(!node[p][idx]) node[p][idx] = ++num;
            p = node[p][idx];
        }
        ed[p] = 1;
    }
    bool strFind(char *str)
    {
        int p = 0;
        for(int i = 1; str[i]; ++i){
            int idx = str[i] - 'a' + 1;
            if(!node[p][idx]) return 0;
            p = node[p][idx];
        }
        return ed[p];
    }
    bool prefixFind(char *str)
    {
        int p = 0;
        for(int i = 1; str[i]; ++i){
            int idx = str[i] - 'a' + 1;
            if(!node[p][idx]) return 0;
            p = node[p][idx];
        }
        return 1;
    }
}t[1010];
```

### 树状数组

#### 单点修改 $+$ 区间查询

模板题：洛谷 $3374$

本例中，树状数组 $c$ 维护 $a_{i}$ 的前缀和。直接进行单点修改和区间查询操作，求和时差分即可

$code$ 如下

```cpp
int n, m, a[N], c[N];

//BIT
int lowbit(int x) {return x & (-x);}
void upd(int *c, int i, int val)
{
    while(i <= n){
        c[i] += val;
        i += lowbit(i);
    }
}
int query(int *c, int i)
{
    int ans = 0;
    while(i > 0) {
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), upd(c, i, a[i]);
    for(int i = 1; i <= m; ++i){
        int op = read(), x = read(), y = read();
        if(op == 1) upd(c, x, y);
        else write(query(c, y) - query(c, x-1)), puts("");
    }
    return 0;
}
```

#### 区间修改 $+$ 单点查询

模板题：洛谷 $3368$

引入 $delt_{i}$ 作为 $a_{i}$ 的差分数组，通过 $delt_{i}$ 来进行区间修改

则有

$delt_{i}=a_{i}-a_{i-1}$

$delt_{1}=a_{1}-a_{0}$

$delt_{2}=a_{2}-a_{1}$

$a_{i}=delt_{1}+delt_{2}+..+delt_{i}$

用树状数组 $c$ 维护 $delt_{i}$ 的前缀和

于是区间修改变成==在 $delt_{i}$ 的两端打上标记==

单点查询变成对 $delt_{i}$ 求前缀和

例如，对 $[l,\ r]$ 中的 $a_{i}$ 区间加 $k$，查询 $a_{r}$ 的值

```cpp
//不改变差分数组做前缀和
int s[N];
delt[l] += k, delt[r+1] -= k
for(int i = l; i <= r; ++i)
    s[i] = s[i-1] + delt[i];
cout<<s[r]<<endl;
```

```cpp
//改变差分数组做前缀和
delt[l] += k, delt[r+1] -= k
for(int i = l; i <= r; ++i)
    delt[i] += delt[i - 1];
cout<<delt[r]<<endl;
```

$code$ 如下

```cpp
int n, m, a[N], c[N];

//树状数组
int lowbit(int x) {return x & (-x);}
void upd(int *c, int i, int val)
{
    while(i <= n){
        c[i] += val;
        i += lowbit(i);
    }
}
int query(int *c, int i)
{
    int ans = 0;
    while(i) {
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), upd(c, i, a[i] - a[i-1]);
    for(int i = 1; i <= m; ++i){
        int op = read();
        if(op == 1){
            int x = read(), y = read(), k = read();
            upd(c, x, k), upd(c, y + 1, -k);
        }
        else {
            int x = read();
            write(query(c, x)), puts("");
        }
    }
    return 0;
}
```

#### 区间修改 $+$ 区间查询

模板题：洛谷 $3372$

仍然设 $delt_{i}$ 是 $a_{i}$ 的差分数组，再设 $sum_{i}$ 是 $a_{i}$ 的前缀和数组，下面用 $delt_{i}$ 推导 $sum_{i}$

$$
sum_{x}=\sum_{i=1}^{x}a_{i}=\sum_{i=1}^{x}\sum_{j=1}^{i}delt_{j}
$$

考虑贡献，$delt_{1}$ 出现了 $x$ 次，$delt_{2}$ 出现了 $x-1$ 次...

所以式子改写为

$$
sum_{x}=\sum_{i=1}^{x}(x-i+1)delt_{i}
$$

即

$$
sum_{x}=(x+1)\sum_{i=1}^{x}delt_{i}-\sum_{i=1}^{x}i\cdot delt_{i}
$$

考虑用树状数组 $c_{1}$ 维护 $delt_{i}$ 前缀和，用树状数组 $c_{2}$ 维护 $i\cdot delt_{i}$ 前缀和，然后做区间修改与区间查询

$code$ 如下

```cpp
int n, m, a[N], c1[N], c2[N];

//树状数组
int lowbit(int x) {return x & (-x);}
void upd(int *c, int i, int val)
{
    while(i <= n){
        c[i] += val;
        i += lowbit(i);
    }
}
int query(int *c, int i)
{
    int ans = 0;
    while(i) {
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n = read(), m = read();
    for(int i = 1; i <= n; ++i) {
        a[i] = read();
        upd(c1, i, a[i] - a[i - 1]);
        upd(c2, i, i * (a[i]- a[i - 1]));
    }
    for(int i = 1; i <= m; ++i){
        int op = read();
        if(op == 1){
            int x = read(), y = read(), k = read();
            upd(c1, x, k), upd(c1, y + 1, -k);
            upd(c2, x, k * x), upd(c2, y + 1, -k * (y + 1));//delt数组两端加k，i*delt数组两端就要加i*k
        }
        else {
            int x = read(), y = read();
            int ans = ((y + 1) * query(c1, y) - query(c2, y)) - (x * query(c1, x - 1) - query(c2, x - 1));
            write(ans), puts("");
        }
    }
    return 0;
}
```

#### 树状数组求逆序对

模板题：洛谷 $1908$

考虑用树状数组 $c$ 维护==区间内数字出现的次数==

考虑区间 $[1,\ r]$，那么 $query(c,\ r)$ 表示满足 $1\leq a_{i}\leq r$ 的 $a_{i}$ 的总个数

再考虑区间 $[l,\ r]$，那么 $query(c,\ r)-query(c,\ l-1)$ 表示满足 $l\leq a_{i}\leq r$ 的 $a_{i}$的总个数

具体算法步骤如下

将所给数组 $a_{n}$ 离散化，那么新的 $a_{i}$ 表征旧的 $a_{i}$ 在数组中的==相对大小==

遍历数组，将 $a_{i}$ 插入树状数组 $c$，$upd(c,\ a[i],\ 1)$ 表示 $a_{i}$ 出现次数==增一==，也即 $c$ 所维护的区间 $[1,\ a_{i}]$ 的和==增一==

$query(c,\ a[i])$ 表示 ==$\leq a_{i}$ 的值出现的次数==，那么 $i - query(c,\ a[i])$表示与 $a_{i}$ 构成逆序对的 $a_{j}$ 的数量

样例解释：

>离散化后的$a:\ 5,\ 3,\ 2,\ 4,\ 1$
$a_{1}=5,\ c_{a_{1}}=c_{5}$ 自增，$i-query(c,\ a_{1})=i-query(c,\ 5)=1-1=0$
$a_{2}=3,\ c_{a_{2}}=c_{3}$ 自增，$i-query(c,\ a_{2})=i-query(c,\ 3)=2-1=1$
$a_{3}=2,\ c_{a_{3}}=c_{2}$ 自增，$i-query(c,\ a_{3})=i-query(c,\ 2)=3-1=2$
$a_{4}=4,\ c_{a_{4}}=c_{4}$ 自增，$i-query(c,\ a_{4})=i-query(c,\ 4)=4-3=1$
$a_{5}=1,\ c_{a_{5}}=c_{1}$ 自增，$i-query(c,\ a_{5})=i-query(c,\ 1)=5-1=4$
所以共有 $8$ 对逆序对

$code$ 如下

```cpp
//BIT
int n, a[N], b[N], c[N];

inline int lowbit(int x) {return x & -x;}
void upd(int *c, int i, int x)
{
    while(i <= n){
        c[i] += x;
        i += lowbit(i);
    }
}
int query(int *c, int i)
{
    int ans = 0;
    while(i){
        ans += c[i];
        i -= lowbit(i);
    }
    return ans;
}

int main()
{
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), b[i] = a[i];
    sort(b + 1, b + 1 + n);
    for(int i = 1; i <= n; ++i) a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
    LL ans = 0;
    for(int i = 1; i <= n; ++i) add(c, a[i], 1), ans += i - query(c, a[i]);
    write(ans);
    return 0;
}
```

#### 树状数组封装

```cpp
int n;
struct BIT
{
    LL c1[N], c2[N], c3[N], c4[N];
    LL lowbit(LL x) {return x & -x;}
    void index_upd(LL *c, int i, int val)
    {

        while(i <= n){
            c[i] += val, c[i] %= MOD;
            i += lowbit(i);
        }
    }
    LL index_query(LL *c, int i)
    {

        LL ans = 0;
        while(i){
            ans += c[i], ans %= MOD;
            i -= lowbit(i);
        }
        return ans;
    }
    void interval_upd(LL *c, int L, int R, LL val)//差分数组打标记
    {
        index_upd(c, L, val), index_upd(c, R + 1, -val);
    }
    LL interval_query(LL *c1, LL *c2, int L, int R)
    {
        LL sum1 = ((R + 1) % MOD) * (index_query(c1, R) % MOD) % MOD;
        LL sum2 = (L % MOD) * (index_query(c1, L - 1) % MOD) % MOD;
        LL sum3 = ((sum1 - sum2) % MOD + MOD) % MOD;
        LL sum4 = ((index_query(c2, R) - index_query(c2, L - 1)) % MOD + MOD) % MOD;
        return ((sum3 - sum4) % MOD + MOD) % MOD;
    }
}BT;
```

### 线段树

线段树节点：

```cpp
struct segmentTree
{
    int l, r;//p节点维护的[l, r]区间
    ll sum, tag;
    segmentTree() {sum=0, tag=0;}
}t[N<<2];
```

由于线段树是完美二叉树，有$n$个叶子节点的完美二叉树总节点数为$2*n-1$。但大多数情况下，为了预防最后一层的溢出，即叶子节点不都在最后一层的情况，所以数组空间开$4*n$大小

建树：

```cpp
void build(int l, int r, int p)
{
    t[p].l=l, t[p].r=r;
    if(l==r) {t[p].sum=a[l];return;}
    int mid=(l+r)>>1;
    build(l, mid, 2*p);
    build(mid+1, r, 2*p+1);
    t[p].sum+=t[2*p].sum+t[2*p+1].sum;
}
```

向左右区间递归建树，回溯时合并区间值（和，$min$，$max$..）

传递懒标记：

```cpp
void pushdown(int p)
{
    if(t[p].tag){
        t[2*p].sum+=t[p].tag*(t[2*p].r-t[2*p].l+1), t[2*p].tag+=t[p].tag;
        t[2*p+1].sum+=t[p].tag*(t[2*p+1].r-t[2*p+1].l+1), t[2*p+1].tag+=t[p].tag;
        t[p].tag=0;
    }
}
```

懒标记的作用：
未引进$lazytag$时，我们是通过递归到深处修改叶子节点的值，然后回溯修改父亲区间的值来实现的。例如修改$[1, n]$区间，递归到深处修改叶子节点，复杂度$nlog{n}$，这并不可观。
如果引入$lazytag$， 对于一个被修改的区间$[l, r]$而言，回溯时他的所有父亲区间都进行了相应的变化，但是他的子区间却并没有发生改变

修改操作：

```cpp
void upd(int ql, int qr, int p, ll k)
{
    if(ql<=t[p].l&&qr>=t[p].r) {//更新区间完美覆盖p所在区间
        t[p].sum+=k*(t[p].r-t[p].l+1);
        t[p].tag+=k;
        return;
    }
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) upd(ql, qr, 2*p, k);//更新区间覆盖p左孩子区间
    if(qr>mid) upd(ql, qr, 2*p+1, k);//更新区间覆盖p右孩子区间
    t[p].sum=t[2*p].sum+t[2*p+1].sum;
}
```

查询操作:

```cpp
ll query(int ql, int qr, int p)
{
    ll ans=0;
    if(ql<=t[p].l&&qr>=t[p].r) return t[p].sum;
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) ans+=query(ql, qr, 2*p);
    if(qr>mid) ans+=query(ql, qr, 2*p+1);
    return ans;
}
```

线段树例题：

```cpp
#include <bits/stdc++.h>
using namespace std;
//裸线段树

typedef long long ll;
const int N=1e5+5;
int n, m;
ll a[N];
struct segmentTree
{
    int l, r;//p节点维护的区间
    ll sum, tag;
    segmentTree() {sum=0, tag=0;}
}t[N<<2];

void build(int l, int r, int p)
{
    t[p].l=l, t[p].r=r;
    if(l==r) {t[p].sum=a[l];return;}
    int mid=(l+r)>>1;
    build(l, mid, 2*p);
    build(mid+1, r, 2*p+1);
    t[p].sum+=t[2*p].sum+t[2*p+1].sum;
}

void pushdown(int p)
{
    if(t[p].tag){
        t[2*p].sum+=t[p].tag*(t[2*p].r-t[2*p].l+1), t[2*p].tag+=t[p].tag;
        t[2*p+1].sum+=t[p].tag*(t[2*p+1].r-t[2*p+1].l+1), t[2*p+1].tag+=t[p].tag;
        t[p].tag=0;
    }
}

void upd(int ql, int qr, int p, ll k)
{
    if(ql<=t[p].l&&qr>=t[p].r) {
        t[p].sum+=k*(t[p].r-t[p].l+1);
        t[p].tag+=k;
        return;
    }
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) upd(ql, qr, 2*p, k);//更新区间覆盖p左孩子区间
    if(qr>mid) upd(ql, qr, 2*p+1, k);//更新区间覆盖p右孩子区间
    t[p].sum=t[2*p].sum+t[2*p+1].sum;
}

ll query(int ql, int qr, int p)
{
    ll ans=0;
    if(ql<=t[p].l&&qr>=t[p].r) return t[p].sum;
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) ans+=query(ql, qr, 2*p);
    if(qr>mid) ans+=query(ql, qr, 2*p+1);
    return ans;
}
int main()
{
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;++i) scanf("%lld", &a[i]);
    build(1, n, 1);
    for(int i=1;i<=m;++i){
        int o;scanf("%d", &o);
        if(o==1){
            int x, y;ll k;
            scanf("%d%d%lld", &x, &y, &k);
            upd(x, y, 1, k);
        }
        else {
            int x, y;scanf("%d%d", &x, &y);;
            printf("%lld\n", query(x, y, 1));
        }
    }
    return 0;
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
//带优先级线段树

typedef long long ll;
const int N=1e5+5;
int n, m, mod;
ll a[N];
struct segmentTree
{
    int l, r;//p节点维护的区间
    ll sum, add, mul;
    segmentTree() {sum=0, add=0, mul=1;}
}t[N<<2];

void build(int l, int r, int p)
{
    t[p].l=l, t[p].r=r;
    if(l==r) {t[p].sum=a[l]%mod;return;}
    int mid=(l+r)>>1;
    build(l, mid, 2*p);
    build(mid+1, r, 2*p+1);
    t[p].sum=t[2*p].sum%mod+t[2*p+1].sum%mod;
}

void pushdown(int p)
{
    t[2*p].sum=t[2*p].sum*t[p].mul%mod+t[p].add*(t[2*p].r-t[2*p].l+1)%mod;
    t[2*p+1].sum=t[2*p+1].sum*t[p].mul%mod+t[p].add*(t[2*p+1].r-t[2*p+1].l+1)%mod;
    t[2*p].add=t[2*p].add*t[p].mul%mod+t[p].add%mod;
    t[2*p].mul=t[2*p].mul*t[p].mul%mod;
    t[2*p+1].add=t[2*p+1].add*t[p].mul%mod+t[p].add%mod;
    t[2*p+1].mul=t[2*p+1].mul*t[p].mul%mod;
    t[p].add=0, t[p].mul=1;
}

void upd1(int ql, int qr, int p, ll k)//区间乘
{
    if(ql<=t[p].l&&qr>=t[p].r) {//更新区间完美覆盖p所在区间
        t[p].sum=t[p].sum*k%mod;
        t[p].mul*=k%mod;
        t[p].add*=k%mod;
        return;
    }
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) upd1(ql, qr, 2*p, k);//更新区间覆盖p左孩子区间
    if(qr>mid) upd1(ql, qr, 2*p+1, k);//更新区间覆盖p右孩子区间
    t[p].sum=t[2*p].sum%mod+t[2*p+1].sum%mod;
}

void upd2(int ql, int qr, int p, ll k)//区间加
{
    if(ql<=t[p].l&&qr>=t[p].r) {
        t[p].sum=t[p].sum%mod+k*(t[p].r-t[p].l+1)%mod;
        t[p].add=t[p].add%mod+k%mod;
        return;
    }
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) upd2(ql, qr, 2*p, k);
    if(qr>mid) upd2(ql, qr, 2*p+1, k);
    t[p].sum=t[2*p].sum%mod+t[2*p+1].sum%mod;
}

ll query(int ql, int qr, int p)
{
    ll ans=0;
    if(ql<=t[p].l&&qr>=t[p].r) return t[p].sum%mod;
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(ql<=mid) ans=ans%mod+query(ql, qr, 2*p)%mod;
    if(qr>mid) ans=ans%mod+query(ql, qr, 2*p+1)%mod;
    return ans%mod;
}
int main()
{
    scanf("%d%d%d", &n, &m, &mod);
    for(int i=1;i<=n;++i) scanf("%lld", &a[i]);
    build(1, n, 1);
    for(int i=1;i<=m;++i){
        int o;scanf("%d", &o);
        if(o==1){
            int x, y;ll k;
            scanf("%d%d%lld", &x, &y, &k);
            upd1(x, y, 1, k);
        }
        else if(o==2){
            int x, y;ll k;
            scanf("%d%d%lld", &x, &y, &k);
            upd2(x, y, 1, k);
        }
        else {
            int x, y;scanf("%d%d", &x, &y);;
            printf("%lld\n", query(x, y, 1));
        }
    }
    return 0;
}
```

```cpp
#include <bits/stdc++.h>
using namespace std;
//线段树：区间max区间和

typedef long long ll;
const int N=6e4+5;
int c, s, r;
struct segmentTree
{
    int l, r;
    ll sum, tag;
    segmentTree() {sum=0, tag=0;}
}t[N<<2];

void build(int l, int r, int p)
{
    t[p].l=l, t[p].r=r;
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l, mid, 2*p);
    build(mid+1, r, 2*p+1);
}

void pushdown(int p)
{
    t[2*p].sum+=t[p].tag, t[2*p+1].sum+=t[p].tag;
    t[2*p].tag+=t[p].tag, t[2*p+1].tag+=t[p].tag;
    t[p].tag=0;
}

void upd(int l, int r, int p, int v)
{
    if(l<=t[p].l&&r>=t[p].r) {
        t[p].sum+=v;
        t[p].tag+=v;
        return;
    }
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) upd(l, r, 2*p, v);
    if(r>mid) upd(l, r, 2*p+1, v);
    t[p].sum=max(t[2*p].sum, t[2*p+1].sum);
}

int query(int l, int r, int p)
{
    int ans=0;
    if(l<=t[p].l&&r>=t[p].r)
        return t[p].sum;
    if(t[p].tag) pushdown(p);
    int mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) ans=max(ans, query(l, r, 2*p));
    if(r>mid) ans=max(ans, query(l, r, 2*p+1));
    return ans;
}
int main()
{
    scanf("%d%d%d", &c, &s, &r);
    build(1, c, 1);
    for(int i=1;i<=r;++i){
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        int temp=query(x, y-1, 1);//y个站有y-1个区间
        if(temp+z<=s) {upd(x, y-1, 1, z);cout<<"YES"<<endl;}
        else cout<<"NO"<<endl;
    }
    return 0;
}
/*
4 6 3
1 3 2
4 6 4
1 6 1
*/
```

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
//权值线段树：逆序对

typedef long long ll;
const int N=5e5+5;
int n, a[N], b[N];
struct segmenTree
{
    int l, r;
    ll v;
}t[N<<2];

void build(int l, int r, int p)
{
    t[p].l=l, t[p].r=r, t[p].v=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    if(l<=mid) build(l, mid, 2*p);
    if(r>mid) build(mid+1, r, 2*p+1);
}

void upd(int x, int p)
{
    if(t[p].l==t[p].r) {t[p].v++;return;}//x出现次数++
    int mid=(t[p].l+t[p].r)>>1;
    if(x<=mid) upd(x, 2*p);
    if(x>mid) upd(x, 2*p+1);
    t[p].v=t[2*p].v+t[2*p+1].v;
}

ll query(int l, int r, int p)
{
    //cout<<l<<' '<<r<<' '<<p<<endl;
    ll ans=0;
    if(l<=t[p].l&&r>=t[p].r) return t[p].v;
    int mid=(t[p].l+t[p].r)>>1;
    if(l<=mid) ans+=query(l, r, 2*p);
    if(r>mid) ans+=query(l, r, 2*p+1);
    return ans;
}
int main()
{
    while(cin>>n&&n){
        for(int i=1;i<=n;++i) cin>>a[i], b[i]=a[i];
        sort(b+1, b+1+n);
        int l=unique(b+1, b+1+n)-(b+1);
        for(int i=1;i<=n;++i)
            a[i]=lower_bound(b+1, b+1+l, a[i])-b;
        ll ans=0;
        build(1, l, 1);
        for(int i=1;i<=n;++i){
            ans+=query(a[i]+1, l, 1);
            upd(a[i], 1);

        }
        cout<<ans<<endl;
    }
    return 0;
}
/*
7
100 2 8 9 1 1000 100
*/
```

### $ST$ 表

分析：
倍增思想$+DP$思想。$Onlgn$建表，$O1$查询。适用于静态$rmq$问题。
建表：
$ST[i][j]$表示从$i$开始长度为$(1<<j)$的区间最值，即$[i, i+(1<<j)-1]$。
特别的，$ST[i][0]=a[i],\ ST[i][1]=max(a[i], a[i+1])$。
查询最值：
查询$[l, r]$的最值，求出区间长度$len$后取$log2$，即$len=(int)log2(r-l+1)$。
由数学知识可知: $(1<<len)<=(r-l+1)$，当且仅当$(r-l+1)$是$2$的倍数时取等号。
也就是说，$(1<<len)$不一定能完全覆盖区间（但一定覆盖半区间），所以考虑从左顶点$l$和右顶点$r$分别做一次查询，最后返回二者较大值即可。

```cpp
//ST表
int ST[N][(int)log2(N)+1];
void ini(int n)
{
    int len=(int)log2(n)+1;
    for(int i=1;i<=n;++i) ST[i][0]=a[i];
    for(int j=1;j<=len;++j)
        for(int i=1;i+(1<<j)-1<=n;++i)
            ST[i][j]=max(ST[i][j-1], ST[i+(1<<j-1)][j-1]);
}
int query(int l, int r)
{
    int k=(int)log2(r-l+1);
    return max(ST[l][k], ST[r-(1<<k)+1][k]);
}
```

$code:$

```cpp
int n, m, a[N];
set<int> st;

//ST表
int ST[N][(int)log2(N)+1];
void ini(int n)
{
    int len=(int)log2(n)+1;
    for(int i=1;i<=n;++i) ST[i][0]=a[i];
    for(int j=1;j<=len;++j)
        for(int i=1;i+(1<<j)-1<=n;++i)
            ST[i][j]=max(ST[i][j-1], ST[i+(1<<j-1)][j-1]);
}
int query(int l, int r)
{
    int k=(int)log2(r-l+1);
    return max(ST[l][k], ST[r-(1<<k)+1][k]);
}

int main()
{
    n=read(), m=read();
    for(int i=1;i<=n;++i) a[i]=read();
    ini(n);
    for(int i=1;i<=m;++i){
        int l=read(), r=read();
        write(query(l, r)), puts("");
    }
    return 0;
}
/*
8 1
9 3 1 7 5 6 0 8
4 8
*/
```

## 图论

### 最短路

#### $Dijkstra$

朴素 $Dijkstra$

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
#define LL long long
#define inf 0x3f3f3f3f
using namespace std;
const int N = 5e5 + 7;
int n, m, s;
int dis[N];
bool vis[N];
vector<pii> g[N];

void dijkstra(int n, int m, int s)
{
    fill(dis + 1, dis + 1 + n, inf);
    for(auto& i: g[s])
        dis[i.fi] = min(dis[i.fi], i.se); // handle multiple edges
    dis[s] = 0; vis[s] = 1;
    for(int i = 1; i <= n; ++i){
        int mini = inf, u = 0;
        for(int j = 1; j <= n; ++j)
            if(!vis[j] && dis[j] < mini) mini = dis[j], u = j;
        vis[u] = 1;
        for(auto i: g[u]){
            if(!vis[i.fi] && dis[u] + i.se < dis[i.fi])
                dis[i.fi] = min(dis[i.fi], dis[u] + i.se); // handle multiple edges
        }
    }
}
int main()
{
    cin >> n >> m >> s;
    for(int i = 1; i <= m; ++i){
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    dijkstra(n, m, s);
    for(int i = 1; i <= n; ++i){
        if(dis[i] == inf) printf("%d%c", 2147483647, " \n"[i == n]);
        else printf("%d%c", dis[i], " \n"[i == n]);
    }
    return 0;
}

```

堆优化

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
#define dbg(a, l, r) for(int i = l; i <= r; ++i) printf("%d%c", a[i], " \n"[i == r])
typedef long long LL;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const LL MOD = 11092019;
const int inf = 0x3f3f3f3f;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N = 1e5 + 7;
const double PI = acos(-1);
const double EPS = 1e-6;
using namespace std;

inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}

int n, m, s, dis[N], vis[N];
vector<pii> g[N];
struct node
{
    int to, time;
    node() {}
    node(int _to, int _time) {to = _to, time = _time;}
    const bool operator < (const node b) const {return time > b.time;}
};
void dij(int x)
{
    memset(dis, inf, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    priority_queue<node> pq;
    pq.push(node(x, 0));
    while(!pq.empty()) {
        node temp = pq.top(); pq.pop();
        if(!vis[temp.to]) {
            vis[temp.to] = 1;
            for(auto i: g[temp.to])
                if(!vis[i.fi] && dis[i.fi] > dis[temp.to] + i.se) {
                    dis[i.fi] = dis[temp.to] + i.se;
                    pq.push(node(i.fi, dis[i.fi]);
                }
        }
    }
}
int main()
{
    n = read(), m = read(), s = read();
    for(int i = 1; i <= m; ++i) {
        int a = read(), b = read(), c = read();
        g[a].pb(pii(b, c));
    }
    dij(s);
    for(int i = 1; i <= n; ++i){
        if(dis[i] == inf) printf("%d%c", 2147483647, " \n"[i == n]);
        else printf("%d%c", dis[i], " \n"[i == n]);
    }
    return 0;
}
```

#### $spfa$

可以用于判断负环

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pb push_back
#define pii pair<int, int>
#define fi first
#define se second
#define inf 0x3f3f3f3f
using namespace std;
const int N = 1e5 + 7;
int n, m;
int num[N], dis[N], vis[N], cnt[N];
vector<pii> g[N];

bool spfa()
{
    fill(dis + 1, dis + 1 + n, inf);
    queue<pii> q;
    q.push(make_pair(1, 0)), dis[1] = 0, vis[1] = 1;
    while(!q.empty()) {
        pii temp = q.front(); q.pop();
        vis[temp.fi] = 0;
        for(auto& i: g[temp.fi]) {
            if(dis[i.fi] > dis[temp.fi] + i.se) {
                dis[i.fi] = dis[temp.fi] + i.se;
                cnt[i.fi]++;
                if(cnt[i.fi] >= n) return 0;
                if(!vis[i.fi]) {
                    q.push(make_pair(i.fi, dis[i.fi]));
                    vis[i.fi] = 1;
                }
            }
        }
    }
    return 1;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", &num[i]);
    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        //g[a].pb({b, c});
        g[b].pb(make_pair(a, c));
    }
    int flag = spfa();
    //cout << flag << endl;
    //for(int i = 1; i <= n; ++i) cout << i << ' ' << dis[i] << endl;
    if(!flag) {cout << "-1" << endl; return 0;}
    int ans = 0;
    for(int i = 1; i <= n; ++i)
        if(dis[i] != inf) ans += num[i] * dis[i];
    printf("%d\n", ans);
    return 0;
}
```

### 最小生成树

#### $prim$

维护两个点集合：$U$ 和 $V$。$U$ 记录最小生成树的顶点，$V$ 记录图 $G$ 剩下的顶点

从点 $s$ 开始，把 $s$ 放入 $U$，标记 $s$ 为“已访问”

遍历所有节点，查找距离集合 $U$ 最近的点 $x$，将 $x$ 放入 $U$，标记 $x$ 为“已访问”

对于每一个“未访问”的节点，更新其到集合 $U$ 的距离

存图时，注意判断重边

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
//最小生成树——prim算法

int n, m, g[5005][5005], dis[5005], vis[5005];

int prim(int s)
{
    int ans = 0;
    for(int i = 1; i <= n; ++i) dis[i] = g[s][i];
    vis[s] = 1;//mincost[i]为0，则代表它到集合距离为0，即在集合内
    for(int i = 1; i < n; ++i){
        int mini = inf, x = 0;
        for(int j = 1; j <= n; ++j){
            if(!vis[j] && dis[j] < mini){
                mini = dis[j];
                x = j;
            }
        }
        ans += dis[x]; vis[x] = 1;
        for(int j = 1; j <= n; ++j)
            if(!vis[j] && g[x][j] < dis[j])
                dis[j] = g[x][j];
    }
    return ans;
}
int main()
{
    cin >> n >> m;
    memset(g, inf, sizeof(g));
    for(int i = 1; i <= m; ++i){
        int x, y, w; cin >> x >> y >> w;
        if(g[x][y] > w) {//考虑重边
            g[x][y] = w;
            g[y][x] = w;
        }
    }
    cout << prim(1) << endl;
    return 0;
}
```

#### $Kruskal$

对所有边进行升序排序，每次选取权值最小的边，判断其顶点是否在同一集合：

如果是，则加上权值，并把两顶点 $union$；如果不是，则继续循环；当边数达到 $n-1$ 时停止循环

重边没有影响：对于顶点 $a$ 与 $b$，每次选取的必定是 $a$ 和 $b$ 间权值最小的边，一旦选取完毕，$a$ 和 $b$ 合并，其他重边不再判断！

对于排序操作，可以根据题目特性进行变化，例如使用基数排序降低时间复杂度；或者一些题目给定了边的大小关系，可以直接进行搭建 $MST$

```cpp
#include <bits/stdc++.h>
using namespace std;
//最小生成树——kruskal算法

const int N = 5005, M = 2e5 + 5;
int n, m, pre[N], rk[N];//pre维护顶点信息
struct data//data维护边信息
{
    int x, y, w;
}d[E];

void ini(int n) {for(int i = 1; i <= n; ++i) pre[i] = i, rk[i] = 1;}
int findPre(int x) {return pre[x] == x ? x : pre[x] = findPre(pre[x]);}
void uni(int x, int y)
{
    int fx = findPre(x), fy = findPre(y);
    if(fx == fy) return;
    if(rk[fx] < rk[fy]) pre[fx] = fy, rk[fy] += rk[fx];
    else pre[fy] = fx, rk[fx] += rk[fy];
}
bool commonpre(int x, int y) {int fx = findPre(x), fy = findPre(y); return fx == fy;}
bool cmp(data x, data y) {return x.w < y.w;}

int kruskal()
{
    int ans = 0, cnt = 0;
    for(int i = 1; i <= m; ++i){
        if(!commonPre(d[i].x, d[i].y)) {
            ans += d[i].w;
            cnt++;
            uni(d[i].x, d[i].y);
            if(cnt == n - 1) break;//MST有n-1条边
        }
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    ini();
    for(int i = 1; i <= m; ++i)
        cin >> d[i].x >> d[i].y >> d[i].w;
    sort(d + 1, d + 1 + m, cmp);
    cout << kruskal() << endl;
    return 0;
}
```

### 网络流

#### 链式前向星
  
```cpp
const int N=1e5+5;
int head[N], cnt=1, n, m;//head[i]存储出点为i的最后一条边
struct edge {
    int to, next, w;//to存储此边终点，next指向下一条边“位置”，w为此边权重
}e[N];

void lenAdd(int u, int v, int w)
{
    e[cnt].to=v;//边终点为v
    e[cnt].next=head[u];//下一条边位置为head[u]
    e[cnt].w=w;//权重
    head[u]=cnt++;//头插此边“位置”
}
int main()
{
    memset(head, -1, sizeof(head));
    cin>>n>>m;
    for(int i=1;i<=m;++i){
        int x, y, w;cin>>x>>y>>w;
        lenAdd(x, y, w);
        //lenAdd(y, x, w);无向图存两遍
    }
    for(int i=1;i<=n;++i){
        cout<<i<<": ";
        for(int j=head[i];~j;j=e[j].next){
            cout<<"{"<<i<<", "<<e[j].to<<"}";
            if(e[j].next!=-1) cout<<"->";
            else cout<<"->-1";
        }
        cout<<endl;
    }
    return 0;
}
```

#### $Dicnic$

```cpp
/*Dinic Algorithm*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define arrayDebug(a, l, r) for(int i = l; i <= r; ++i) printf("%d%c", a[i], " \n"[i == r])
typedef long long LL;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const int inf = 0x3f3f3f3f;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int MOD = 1e9 + 7;
const int N = 2e5 + 7;
const double PI = acos(-1);
const double EPS = 1e-6;
using namespace std;
inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}

int n, m, s, t, cnt, head[N], dep[N], cur[N];
struct edge
{
    int fr, to, next, w;
}e[N];

void addedge(int a, int b, int c)
{
    e[cnt].fr = a;//第一条边标为 0，对应反边为 1
    e[cnt].to = b;
    e[cnt].w = c;
    e[cnt].next = head[a];
    head[a] = cnt++;
}

void debug()
{
    for(int i = 1; i <= n; ++i){
        cout<<i<<": ";
        for(int j = head[i]; ~j; j = e[j].next)
            printf("(%d, %d, %d)", e[j].fr, e[j].to, e[j].w);
        puts("");
        cout<<dep[i]<<endl;
    }
    puts("");
}

bool bfs()
{
    memset(dep, 0, sizeof(dep)); //dep 有标记，则可以访问到该点
    queue<int> q; q.push(s);
    dep[s] = 1;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; ~i; i = e[i].next) {
            int v = e[i].to, cost = e[i].w;
            if(cost && !dep[v]) dep[v] = dep[u] + 1, q.push(v);
        }
    }
    return dep[t];
}

int dfs(int u = s, int flow = inf)
{
    if(u == t) return flow;
    int ans = 0;
    for(int &i = cur[u]; ~i; i = e[i].next) {
        int v = e[i].to, cost = e[i].w;
        if(dep[v] == dep[u] + 1 && cost) {
            int res = dfs(v, min(flow, cost));
            if(res > 0) {
                e[i].w -= res, e[i ^ 1].w += res; //建立反边
                flow -= res; //可以流通的流量减少
                ans += res; //答案的贡献增加
                if(!flow) break; //没有可以流通的流量，直接退出循环
            }
        }
    }
    return ans;
}

int Dcnic()
{
    int ans = 0;
    while(bfs()) {
        memcpy(cur, head, sizeof(head));
        ans += dfs();
    }
    return ans;
}

int main()
{
    memset(head, -1, sizeof(head));
    n = read(), m = read(), s = read(), t = read();
    for(int i = 1; i <= m; ++i) {
        int a, b, c;
        a = read(), b = read(), c = read();
        addedge(a, b, c);
        addedge(b, a, 0);
    }
    printf("%d\n", Dcnic());
    return 0;
}
/*
4 5 4 3
4 2 30
4 3 20
2 3 20
2 1 30
1 3 40
*/
```

时间复杂度为 $O(N^2M)$，其中 $N$ 为顶点数，$M$ 为边数

## $DP$

### $LIS$

$O(n^{2})\ dp$

$code:$

```cpp
int ans = 0;
for(int i = 1; i <= n; ++i){
    dp[i] = 1;
    for(int j = 1; j <= i; ++j)
        if(a[j] < a[i])
            dp[i] = max(dp[j] + 1, dp[i]);
    ans = max(ans, dp[i]);
}
write(ans);
```

$O(nlgn)\ dp$

定义 $dp[i]$ 为 **长度为 $i$ 的子序列的末尾元素的最小值**

```cpp
fill(dp + 1, dp + 1 + n, inf);
for(int i = 1; i <= n; ++i)
    *lower_bound(dp + 1, dp + 1 + n, a[i]) = a[i];
printf("%d\n", lower_bound(dp + 1, dp + 1 + n, inf) - (dp + 1))
```

### $LCS$

给定两个序列，求$LCS$

定义状态 $dp[i][j]$ 表示

到 $s1$ 的第 $i$ 位，到 $s2$ 的第 $j$ 位所得到的 $LCS$ 长度

状态转移方程：

$$
dp[i][j]=\left\{\begin{matrix}
 dp[i-1][j-1]+1,&s1[i]=s2[j] \\
 max\left\{dp[i-1][j], dp[i][j-1]\right\}+1,&s1[i]\neq s2[j]
\end{matrix}\right.
$$

$code:$

```cpp
int l1 = s1.length(), l2 = s2.length();
for(int i = 0; i < l1; ++i){
    for(int j = 0; j < l2; ++j){
        if(s1[i] == s2[j]) dp[i][j] = dp[i - 1][j - 1] + 1;
        else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + 1;
    }
}
cout << dp[l1 - 1][l2 - 1] << endl;
```

给定两个 $n$ 以内的排列，求 $LCS$

考虑对 $b$ 数组做映射

将 $b_{i}$ 映射成 $a$ 数组中相应值的下标 $j$，然后跑 $LIS$ 即可

$code$

```cpp
int n, a[N], dp[N], vis[N];
int main()
{
    n=read();
    for(int i = 1; i <= n; ++i){
        int x; x = read();
        vis[x] = i;
    }
    for(int i = 1; i <= n; ++i){
        int x; x = read();
        a[i] = vis[x];
    }
    memset(dp, inf, sizeof(dp));
    for(int i = 1; i <= n; ++i){
        *lower_bound(dp + 1, dp + 1 + n, a[i]) = a[i];
    }
    printf("%d\n", lower_bound(dp + 1, dp + 1 + n, inf) - (dp + 1));
    return 0;
}
```

### 背包问题

$01$ 背包

定义 $dp[i][j]$

选取第 $i$ 个物品，背包容量为 $j$ 时产生的最大价值

状态转移方程

$$
dp[i][j]=\left\{dp[i-1][j], dp[i-1][j-t[i]]+v[i]\right\}
$$

采用滚动数组优化

内层循环倒序枚举，因为每次更新 $dp[j]$，都要参考上一层的 $dp[j]$ 和 $dp[j-t[i]]$

倘若正序枚举，上一层的 $dp[j-t[i]]$ 将先于 $dp[j]$ 被更新，以至于 $dp[j]$ 无限递增

```cpp
int T, m, t[N], v[N], dp[N];

int main()
{
    T = read(), m = read();
    for(int i = 1; i <= m; ++i)
        t[i] = read(), v[i] = read();
    for(int i = 1; i <= m; ++i)
        for(int j = T; j >= t[i]; --j)
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
    printf("%d\n", dp[T]);
    return 0;
}
```

完全背包

$$
dp[i][j]=max\left\{dp[i-1][j], dp[i-1][j-k*t[i]]+k*v[i]\right\}, k\in [0, T/t[i]]
$$

滚动数组优化，顺序枚举，无需在意 $dp[j-t[i]]$ 已被优化，因为物品可以重复选取，相当于在原来基础上再选一个而已

```cpp
int T, m, t[N], v[N], dp[N];

int main()
{
    T = read(), m = read();
    for(int i = 1; i <= m; ++i)
        t[i] = read(), v[i] = read();
    for(int i = 1; i <= m; ++i)
        for(int j = t[i]; j <= T; ++j)
            dp[j] = max(dp[j], dp[j - t[i]] + v[i]);
    printf("%d\n", dp[T]);
    return 0;
}
```

多重背包

二进制拆分

如果当前物品数 $*$ 当前物品重量大于背包容量，跑完全背包

如果当前物品数 $*$ 当前物品重量小于背包容量，二进制拆分跑 $01$ 背包

```cpp
int n, V, v[N], w[N], num[N], dp[N];

void zeroOnePackage(int cost, int volume, int value)
{
    for(int i = volume; i >= cost; --i)
        dp[i] = max(dp[i], dp[i - cost] + value);
}

void completePackage(int cost, int volume, int value)
{
    for(int i = cost; i <= volume; ++i)
        dp[i] = max(dp[i], dp[i - cost] + value);
}

int multiplePackage()
{
    for(int i = 1; i <= n; ++i){
        if(w[i] * num[i] > V) completePackage(w[i], V, v[i]);//背包装不下所有此物品，跑一遍多重背包
        else {
            int k = 1;
            while(k <= num[i]){
                zeroOnePackage(k * w[i], V, k * v[i]);//二进制拆分
                num[i] -= k;
                k <<= 1;
            }
            if(num[i]) zeroOnePackage(w[i] * num[i], V, v[i] * num[i]);//最后单独跑一遍01背包
        }
    }
    return dp[V];
}
int main()
{
    n = read(), V = read();
    for(int i = 1; i <= n; ++i)
        v[i] = read(), w[i] = read(), num[i] = read();
    cout << multiplePackage() << endl;
    return 0;
}
```

## 字符串

### $KMP$

查询模式串 $pattern$ 在文本串 $text$ 中的位置，时间复杂度 $O(n)$

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
#define dbg(a, l, r) for(int i = l; i <= r; ++i) printf("%d%c", a[i], " \n"[i == r])
typedef long long LL;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const LL MOD = 11092019;
const int inf = 0x3f3f3f3f;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N = 1e6 + 7;
const double PI = acos(-1);
const double EPS = 1e-6;
using namespace std;
using namespace std;

inline LL read() //读入函数
{
    char c = getchar();
    LL ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}

char text[N], pattern[N];
int Next[N];
void KMP(char *text, char *pattern, int *Next)
{
    int L1 = strlen(text + 1), L2 = strlen(pattern + 1);
    Next[1] = 0;
    for(int i = 2, j = 0; i <= L2; ++i) {
        while(j && pattern[i] != pattern[j + 1]) j = Next[j];
        if(pattern[i] == pattern[j + 1]) Next[i] = ++j;
    }
    for(int i = 1, j = 0; i <= L1; ++i) {
        while(j && text[i] != pattern[j + 1]) j = Next[j];
        if(text[i] == pattern[j + 1]) ++j;
        if(j == L2) printf("%d\n", i - L2 + 1);
    }
    dbg(Next, 1, L2);
}
int main()
{
    scanf("%s %s", text + 1, pattern + 1);
    KMP(text, pattern, Next);
    return 0;
}
```

### 马拉车

计算字符串的最大回文子串长度，时间复杂度 $O(n)$

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
#define arrayDebug(a, l, r) for(int i = l; i <= r; ++i) printf("%d%c", a[i], " \n"[i == r])
typedef long long LL;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const LL MOD = 11092019;
const int inf = 0x3f3f3f3f;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N = 4e7 + 7;
const double PI = acos(-1);
const double EPS = 1e-6;
using namespace std;
inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}

char s[N], str[N];
int L, p[N];
void manacher()
{
    for(int i = 1; i <= L; ++i) str[2 * i] = s[i], str[2 * i + 1] = '$';
    L = L * 2 + 1, str[0] = str[1] = '$', str[L + 1] = '\0';
    int mid = 0, maxr = 0;
    for(int i = 1; i <= L; ++i) {
        if(i < maxr) p[i] = min(p[2 * mid - i], maxr - i);
        while(str[i - p[i] - 1] == str[i + p[i] + 1]) ++p[i];
        if(i + p[i] > maxr) maxr = i + p[i], mid = i;
    }
}
int main()
{
    scanf("%s", s + 1);
    L = strlen(s + 1);
    manacher();
    int ans = 0;
    for(int i = 1; i <= L; ++i) ans = max(ans, p[i]);
    cout << ans << endl;
    return 0;
}
```

#### 求最长回文前缀

用 $manacher$ 预处理 $p[i]$ 数组

对于新字符串 $str$ 的每一个位置 $i$，判断其回文半径是否触及左端点 $1$，即 $i - p[i] = 1$，若可以触及，说明是一个回文前缀，更新长度即可

代码如下

```cpp
#include <bits/stdc++.h>
#define fi first
#define se second
#define pii pair<int, int>
#define pb push_back
#define arrayDebug(a, l, r) for(int i = l; i <= r; ++i) printf("%d%c", a[i], " \n"[i == r])
typedef long long LL;
typedef unsigned long long ULL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const LL MOD = 11092019;
const int inf = 0x3f3f3f3f;
const int DX[] = {0, -1, 0, 1, 0, -1, -1, 1, 1};
const int DY[] = {0, 0, 1, 0, -1, -1, 1, 1, -1};
const int N = 4e7 + 7;
const double PI = acos(-1);
const double EPS = 1e-6;
using namespace std;
inline int read()
{
    char c = getchar();
    int ans = 0, f = 1;
    while(!isdigit(c)) {if(c == '-') f = -1; c = getchar();}
    while(isdigit(c)) {ans = ans * 10 + c - '0'; c = getchar();}
    return ans * f;
}

char s[N], str[N];
int L, p[N];
void manacher()
{
    for(int i = 1; i <= L; ++i) str[2 * i] = s[i], str[2 * i + 1] = '$';
    L = L * 2 + 1, str[0] = str[1] = '$', str[L + 1] = '\0';
    int mid = 0, maxr = 0;
    for(int i = 1; i <= L; ++i) {
        if(i < maxr) p[i] = min(p[2 * mid - i], maxr - i);
        while(str[i - p[i] - 1] == str[i + p[i] + 1]) ++p[i];
        if(i + p[i] > maxr) maxr = i + p[i], mid = i;
    }
}
int main()
{
    scanf("%s", s + 1);
    L = strlen(s + 1);
    manacher();
    int ans = 0;
    for(int i = 1; i <= L; ++i) 
        if(i - p[i] == 1) ans = max(ans, p[i]);
    cout << ans << endl;
    return 0;
}
```
