# 数学 $02$

[toc]

## 知识点

### 快速幂

用于快速计算 $a^{b}\ mod\ m$，时间复杂度为 $O(logb)$

#### 快速幂求法

>举例来讲，为了计算 $3^7$，就是计算 $3^{(111)_{2}} = 3^4\cdot 3^2\cdot 3^1$
也就是说，只要知道了 $3^4,\ 3^2,\ 3^1$ 的值，就可以快速计算出答案
事实上，除了最后一个 $3^1$，每一位都是后面的平方，即 $3^4 = (3^2)^2,\ 3^2 = (3^1)^2$

形式化地讲，若将指数 $b$ 写成 $(b_{t}b_{t - 1}...b_{0})_{2}$ 的形式，其中 $b_{i}\in \left\{0,\ 1\right\},\ t = \left\lfloor logb\right\rfloor$，于是有

$$
b = b_{t}2^{t} + b_{t - 1}2^{t - 1} + ... + b_{0}2^{0}
$$

那么答案可以写成

$$
\begin{aligned}
a^{n} & = a^{b_{t}2^{t} + b_{t - 1}2^{t - 1} + ... + b_{0}2^{0}}\\
& = a^{b_{0}2^{0}}\cdot a^{b_{1}2^{1}}\cdots a^{b_{t - 1}2^{t - 1}}\cdot a^{b_{t}2^{t}}
\end{aligned}
$$

其中每一项都可以由前一项递推，即 $a^{2^{i}} = (a^{2^{i - 1}})^2$，当 $b_{i} = 1$ 时，计算贡献，当 $b_{i} = 0$ 时，跳过计算

算法时间复杂度为 $O(logb)$

```cpp
int qpow(int a, int b, int m)
{
    int ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}
```

### 快速乘

用于计算 $a\cdot b\ mod\ m$，时间复杂度为 $O(logb)$

细心的同学会发现，计算机中乘法计算是 $O(1)$ 的，快速乘反而更慢了，应该称之为龟速乘才对

既然如此，为何需要快速乘呢？

因为在算法竞赛中，偶尔会遇到整数相乘爆精度问题，例如两个 $64$ 位整数相乘会爆 $long\ long\ int$，所以我们需要牺牲一定的时间复杂度来保证准确性，从而有了快速乘的说法

#### 快速乘求法

与快速幂相似，我们只需要把乘法换成加法即可

算法时间复杂度为 $O(logb)$

```cpp
int qmul(int a, int b, int m)
{
    int ans = 0;
    while(b) {
        if(b & 1) ans += a, ans %= m;
        a += a, a %= m, b >>= 1;
    }
    return ans;
}
```

### 矩阵类与矩阵快速幂

矩阵快速幂是一种快速计算递推式的算法，但是对代码能力要求较高，需要正确编写矩阵类，然后调用矩阵快速幂函数

矩阵快速幂简单来讲，就是把快速幂的基换成单位矩阵，乘法换成矩阵乘法

直接上模板

```cpp
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
```

### 矩阵加速

考虑如下问题

>$f_{x}=a_{1}f_{x-1}+a_{2}f_{x-2}+a_{3}f_{x-3}+...+a_{n}f_{x-n}$
>
>给定 $t$，求 $f_{t}$，注意：$t$ 通常很大，线性递推难以计算

构造矩阵递推式：

$$
\begin{bmatrix}
f_{x}\\
f_{x-1}\\
f_{x-2}\\
...\\
f_{x-n+1}\\
\end{bmatrix}=
\begin{bmatrix}
a_{1}& a_{2}& a_{3}& ... & a_{n - 1} & a_{n}\\
1& 0& 0& ... & 0 & 0\\
0& 1& 0& ... & 0 & 0\\
...& ...& ...& ... & ... & ...\\
0& 0& 0& ...  & 1 & 0\\
\end{bmatrix}
*
\begin{bmatrix}
f_{x-1}\\
f_{x-2}\\
f_{x-3}\\
...\\
f_{x-n}\\
\end{bmatrix}
=...
=\begin{bmatrix}
a_{1}& a_{2}& a_{3}& ... & a_{n - 1} & a_{n}\\
1& 0& 0& ... & 0 & 0\\
0& 1& 0& ... & 0 & 0\\
...& ...& ...& ... & ... & ...\\
0& 0& 0& ...  & 1 & 0\\
\end{bmatrix}^{x-n}
*\begin{bmatrix}
f_{n}\\
f_{n-1}\\
f_{n-2}\\
...\\
f_{1}\\
\end{bmatrix}
$$

即 $F(x)=A\cdot F(x-1)=A^2\cdot F(x-2)=...=A^{x-n}F(n)$

其中：

$$
F(x)=\begin{bmatrix}
f_{x}\\
f_{x-1}\\
f_{x-2}\\
...\\
f_{x-n+1}\\
\end{bmatrix}
,\ F(n)=\begin{bmatrix}
f_{n}\\
f_{n-1}\\
f_{n-2}\\
...\\
f_{1}\\
\end{bmatrix}
,\ A = \begin{bmatrix}
a_{1}& a_{2}& a_{3}& ... & a_{n - 1} & a_{n}\\
1& 0& 0& ... & 0 & 0\\
0& 1& 0& ... & 0 & 0\\
...& ...& ...& ... & ... & ...\\
0& 0& 0& ...  & 1 & 0\\
\end{bmatrix}
$$

利用矩阵快速幂，计算递推式第 $t$ 项，可以在 $O(n^{3}logt)$ 时间内求出答案，**记得特判前几项**

## 题目

### 653. 快速幂取模

#### 题意

输入三个正整数 $x,\ p,\ m$，计算 $x^{p}\ mod\ m$

规定 $1\leq x\leq 10000,\ 2\leq m\leq 10000,\ 1\leq p\leq 10^{15}$

#### 题解

模板题

```cpp
#include <bits/stdc++.h>
#define inf 2147483647
#define fi first
#define se second
#define pii pair<int, int>
typedef long long LL;
const int N = 100 + 7;
const int mod = 1e9 + 7;
using namespace std;

LL qpow(LL a, LL b, LL m)
{
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}

int main() {
    LL x, p, m;
    cin >> x >> p >> m;
    cout << qpow(x, p, m) << endl;
    return 0;
}
```

### 2560. 矩阵，加速！

#### 题意

给定数列 $a$，$a_{1} = a_{2} = a_{3} = 1$，当 $i > 3$ 时，有 $a_{i} = a_{i - 1} + a_{i - 3}$，求 $a$ 的第 $n$ 项对 $10^9 + 7$ 取余的值

规定，$1\leq n\leq 2,000,000,000$

#### 题解

构造矩阵如下

$$
\begin{bmatrix}
a_{x}\\
a_{x - 1}\\
a_{x - 2}\\
\end{bmatrix}
= \begin{bmatrix}
1 & 0 & 1\\
1 & 0 & 0\\
0 & 1 & 0\\
\end{bmatrix}\cdot
\begin{bmatrix}
a_{x - 1}\\
a_{x - 2}\\
a_{x - 3}\\
\end{bmatrix}
$$

接下来用矩阵快速幂递推即可，时间复杂度 $O(logn)$

```cpp
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
```