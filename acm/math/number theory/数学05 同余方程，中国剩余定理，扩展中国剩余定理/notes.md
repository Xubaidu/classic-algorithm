# 数学 $05$

[toc]

## 知识点

### 同余下的加减乘除

同余下的加减乘除特别注意减法和除法

同余下的加法

$$
(a + b) \% m = (a \% m + b \% m) \% m
$$

同余下的减法，算法竞赛不考虑负数，所以要把负数变正

$$
(a - b) \% m = (a \% m - b \% m + m) \% m
$$

同余下的乘法

$$
(a\times b) \% m = (a \% m \times b \% m) \% m
$$

同余下的除法，乘以乘法逆元

$$
\frac{a}{b} \% m = (a \% m \times b^{-1} \% m) \% m
$$

### 一次同余方程

一次同余方程形如

$$
ax\equiv b\ (mod\ m)
$$

设方程的一个特解为 $x_{0}$，那么方程的通解即为

$$
x\equiv x_{0}\ (mod\ m)
$$

若最大公因数 $(a,\ m) = 1$，则 $x_0\equiv b\cdot a^{-1}\ (mod\ m)$，若 $(a,\ m)\neq 1$，方程无解

乘法逆元可以使用扩欧和快速幂计算，当然，后者只适用于模数 $m$ 为素数的情况

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

中国剩余定理可以计算上述方程组的通解

#### 中国剩余定理 $CRT$ 概述

设

$$
m = \prod_{i = 1}^{n}m_{i}
$$

以及

$$
M_{i} = \frac{m}{m_{i}},\ i = 1,\ 2,\ ...,\ n
$$

则上述同余方程组的通解为

$$
x\equiv \sum_{i=1}^{n}a_{i}\cdot M_{i}^{-1}\cdot M_{i}\ (mod\ m)
$$

#### $CRT$ 解的求解与证明

考虑对于每一个线性同余方程
$$
x_{i}\equiv a_{i}\ (mod\ m_{i})
$$

求出对应的一个特解 $x_{i}$ ，且这个 $x_{i}$ 要满足
$$
\left\{\begin{matrix}
x_{i}\equiv a_{j}\ (mod\ m_{j}),\ i=j
\\x_{i}\equiv 0\ (mod\ m_{j}),\ i\neq j
\end{matrix}\right.
$$

把 $n$ 个这样的 $x_{i}$ 求和，就可以得到方程组的一个特解 $x$

设

$$
m = \prod_{i = 1}^{n}m_{i}
$$

以及

$$
M_{i} = \frac{m}{m_{i}},\ i = 1,\ 2,\ ...,\ n
$$

分析 $x_{i}$ ，其必然是 $M_{i}$ 的整数倍，且满足
$$
x_{i}\equiv a_{i}\ (mod\ m_{i})
$$

设
$$
x_{i}=y\cdot M_{i},\ y\in \mathbb{Z}
$$

有
$$
y\cdot M_{i}\equiv a_{i}\ (mod\ m_{i})
$$

只要能够解出 $y$ ，便能得到 $x$ 的特解；反之，线性同余方程组无解

因为最大公因数 $(M_{i},\ m_{i}) = 1$，因此上述方程一定有解

由于不保证 $m_{i}$ 是素数，所以根据扩欧算法得到乘法逆元

$$
y\equiv a_{i}\cdot M_{i}^{-1}\ (mod\ m_{i})
$$

所以

$$
x_{i} = a_{i}\cdot M_{i}^{-1}\ (mod\ m_{i})\cdot M_{i}
$$

将 $n$ 个 $x_{i}$ 求和得到 $x$ 的一个特解
$$
x=\sum_{i=1}^{n}a_{i}\cdot M_{i}^{-1}\ (mod\ m_{i})\cdot M_{i}
$$

为了满足题意， $x$ 的通解为
$$
x\equiv \sum_{i=1}^{n}a_{i}\cdot M_{i}^{-1}\ (mod\ m_{i})\cdot M_{i}\ (mod\ m)
$$

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

### 扩展中国剩余定理（选讲）

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

扩展中国剩余定理是为了处理模数不互质的情况

#### 扩展中国剩余定理概述

设

$$
m = [m_{1}m_{2}...m_{n}]
$$

则上述方程组通解为

$$
x = x_{0} + q\cdot \frac{m_{i}}{gcd(m, m_{i})},\ q\in Z
$$

其中 $x_{0}$ 是同余方程组的一个特解，通过 $n - 1$ 次扩欧算法计算得出

#### 计算 $EXCRT$ 的解

考虑已经解出前 $k-1$ 个方程的解 $x_{1}$

习惯的，我们设
$$
m=\prod_{i=1}^{k-1}m_{i}
$$

但为了防止溢出，设
$$
m=[m_{1},\ m_{2},..,\ m_{k - 1}]
$$

设前 $k-1$ 个方程的通解为
$$
x\equiv x_{1}\ (mod\ m)
$$

再设 $x_{2} = x_{1} + t\cdot m,\ t\in \mathbb{Z}$

将 $x_{2}$ 代入第 $k$ 个式子
$$
x_{1} + t\cdot m\equiv a_{k}\ (mod\ m_{k})
$$

即

$$
t\cdot m\equiv a_{k} - x_{1}\ (mod\ m_{k})
$$

若
$$
(m,\ m_{k})\nmid a_{k} - x_{1}
$$

则线性同余方程组无解

若
$$
(m,\ m_{k})\mid a_{k} - x_{1}
$$

由扩欧算法解出 $t$，得到特解 $x_{2}$

那么新的通解为

$$
x\equiv x_{2}\ (mod\ m_{k})
$$

如此循环

$excrt$ 的本质便是合并方程

对于 $n$ 个方程的线性同余方程组，本质上是作 $n-1$ 次扩展欧几里得算法

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

## 题目选讲

### 2587. 同余方程

#### 题意

给定正整数 $a,\ b,\ m$，计算同余方程 $ax\equiv b\ (mod\ m)$ 的最小正整数解

输入保证

对于 $40\%$ 数据，$2\leq a,\ b\leq m\leq 1,000$

对于 $60\%$ 数据，$2\leq a,\ b\leq m\leq 10,000,000$

对于 $100\%$ 数据，$2\leq a,\ b\leq m\leq 1,000,000,000$

#### 题解

利用扩欧计算 $a^{-1}\ (mod\ m)$，然后计算 $b\cdot a^{-1}\ (mod\ m)$ 即可

```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x); // y 的值被修改为 x', x 的值被修改为 y'
    y -= 1LL * (a / b) * x;
    return r;
}

int getInv(int a, int m)
{
    int x, y;
    int r = exgcd(a, m, x, y);
    if(r != 1) return -1; // 不存在逆元
    while(x < 0) x += m;
    return x % m;
}

int solve(int a, int b, int m)
{
    return 1LL * b * getInv(a, m) % m;
}

int main()
{
    int a, b, m; cin >> a >> b >> m;
    cout << solve(a, b, m) << endl;
    return 0;
}
```

### 2545. 中国剩余定理

#### 题意

给定正整数 $n$，以及 $n$ 个 $a_{i},\ m_{i}$，保证 $m_{i}$ 互质，计算如下方程组的最小正整数解

$$
\left\{\begin{matrix}
x_{1}\equiv a_{1}\ (mod\ m_{1})
\\x_{2}\equiv a_{2}\ (mod\ m_{2})
\\...
\\x_{n}\equiv a_{n}\ (mod\ m_{n})
\end{matrix}\right.
$$

保证 $2\leq n\leq 10,\ 0\leq a_{i} < m_{i}\leq 10^2,\ 1\leq \prod{a_{i}}\leq 10^{18}$，保证 $m_{i}$ 互质，保证 $a_{i}$ 不全为 $0$

#### 题解

$CRT$ 模板题

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;


int n;
LL m[12], a[12];

LL qpow(LL a, LL b, LL m)
{
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}

LL exgcd(LL a, LL b, LL &x, LL &y)
{
    if(!b) {x = 1, y = 0; return a;}
    LL r = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return r;
}

LL getInv(LL a, LL MOD)
{
    LL x, y;
    LL r = exgcd(a, MOD, x, y);
    while(x < 0) x += MOD;
    y = (1 - a * x) / b;
    return x;
}

int main()
{
    scanf("%d", &n);
    LL M = 1;
    for(int i = 1; i <= n; ++i)
        scanf("%lld %lld", &m[i], &a[i]), M *= m[i];
    LL x = 0;
    for(int i = 1; i <= n; ++i) {
        LL Mi = M / m[i];
        LL Xi = 1LL * a[i] * getInv(Mi, m[i]) % m[i] * Mi % M;
        x += Xi, x %= M;
    }
    cout << x << endl;
    return 0;
}
```

### 2553. 扩展中国剩余定理（选做）

#### 题意

给定正整数 $n$，以及 $n$ 个 $a_{i},\ m_{i}$，不保证 $m_{i}$ 互质，计算如下方程组的最小正整数解

$$
\left\{\begin{matrix}
x_{1}\equiv a_{1}\ (mod\ m_{1})
\\x_{2}\equiv a_{2}\ (mod\ m_{2})
\\...
\\x_{n}\equiv a_{n}\ (mod\ m_{n})
\end{matrix}\right.
$$

保证 $2\leq n\leq 10^5,\ 1\leq a_{i} < m_{i}\leq 10^{12}$，保证所有 $m_{i}$ 的最小公倍数不超过 $10^{18}$，不保证 $m_{i}$ 互质

#### 题解

$EXCRT$ 模板题，注意数据较大，可能爆 ```long long int```，使用快速乘防止溢出

```cpp
#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
typedef long long LL;
using namespace std;

const int N = 1e5 + 7;
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
    LL M = p[1]; // 维护LCM
    LL x = a[1]; // 维护解
    for(int i = 2; i <= n; ++i){
        LL xx = 0, yy = 0;
        LL gcd = exgcd(M, p[i], xx, yy);
        LL c = (a[i] - x % p[i] + p[i]) % p[i];
        LL ag = p[i] / gcd;
        if(c % gcd) return -1;
        c /= gcd;
        LL t = qmul(xx, c, ag); // 若数据较大，使用快速乘防止溢出
        //LL t = (xx * c) % ag;
        x += t * M; // 得到新的特解
        M *= ag; // 更新LCM
        x = (x % M + M) % M; // 将x更新到最小
    }
    return x;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%lld %lld", &a[i], &p[i]);
    LL ans = excrt(n, a, p);
    if(ans == -1) puts("-1");
    else printf("%lld\n", ans);
    return 0;
}

```

### 2545. 构造函数（选做）

#### 题意

给定质数 $p$，整数 $n$ 和 $n$ 个互不相同整数 $a_i$，以及整数 $k$

计算整数对 $(i,\ j)(1\leq i < j\leq n)$ 的数量，使得 $(a_{i} + a_{j})(a_{i}^2 + a_{j}^2)\equiv k\ (mod\ p)$

输入保证，$2\leq n\leq 3\cdot 10^5,\ 2\leq p\leq 10^9,\ 0\leq k\leq p - 1$, $0\leq a_{i}\leq p - 1$

#### 题解

难点在于对式子的变形，具体有

$$
(a_i - a_j)(a_{i} + a_{j})(a_{i}^2 + a_{j}^2)\equiv k(a_i - a_j)\ (mod\ p)
$$

即

$$
a_{i}^4 - ka_{i}\equiv a_{j}^4 - ka_{j}\ (mod\ p)
$$

下面只需要对每一个 $a_{i}$ 计算 $a_{i}^4 - ka_{i}\ (mod\ p)$，用哈希表 ```unordered_map<int, int> mp``` 维护，统计答案，时间复杂度 $O(n)$

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
typedef long long LL;
using namespace std;

const int N = 3e5 + 7;
int n, p, k, a[N];
LL qpow(LL a, LL b, LL p)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= p;
        a *= a, a %= p, b >>= 1;
    }
    return ans;
}

int main()
{
    scanf("%d%d%d", &n, &p, &k);
    for(int i = 1; i <= n; ++i) scanf("%d", &a[i]);
    map<LL, LL> mp;
    for(int i = 1; i <= n; ++i) {
        LL temp = (qpow(a[i], 4, p) - 1LL * k * a[i] % p + p) % p;
        mp[temp]++;
    }
    LL ans = 0;
    for(map<LL, LL>::iterator it = mp.begin(); it != mp.end(); ++it)
        ans += (*it).se * ((*it).se - 1) / 2;
    printf("%lld\n", ans);
    return 0;
}
```