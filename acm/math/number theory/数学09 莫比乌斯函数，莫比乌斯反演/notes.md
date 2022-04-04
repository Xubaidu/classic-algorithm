# 数学 $09$

[toc]

## 知识点

### 提取公因数

提取公因数与整除分块一样，是数论题的常用科技

给定 $n,\ m$，考虑化简

$$
\sum_{i = 1}^{n}\sum_{j = 1}^{m}\gcd(i,\ j)
$$

注意到 $1\leq \gcd(i,\ j)\leq \min(n,\ m)$，当且仅当 $i = j = \min(n,\ m)$ 时取到等号

枚举 $d = \gcd(i,\ j)$，考虑贡献，于是上式变为

$$
\sum_{d = 1}^{\min(n,\ m)}d\sum_{i = 1}^{n}\sum_{j = 1}^{m}[\gcd(i,\ j) = d]
$$

其中 $[x]$ 表示指示函数，取值如下所示

$$
[x]=
\begin{cases}
1&x=1\\
0&x=0\\
\end{cases}
$$

我们知道，$d\mid i,\ d\mid j$，令 $x = \frac{i}{d},\ y = \frac{j}{d}$，于是 $\frac{1}{d}\leq x\leq \frac{n}{d},\ \frac{1}{d}\leq y\leq \frac{m}{d}$

结合 $x,\ y \in \mathbb{Z^{+}}$，于是 $1\leq x\leq \left\lfloor {\frac{n}{d}}\right\rfloor,\ 1\leq y\leq \left\lfloor {\frac{m}{d}}\right\rfloor$

$$
\sum_{d = 1}^{\min(n,\ m)}d\sum_{x = 1}^{\left\lfloor {\frac{n}{d}}\right\rfloor}\sum_{y = 1}^{\left\lfloor {\frac{m}{d}}\right\rfloor}[\gcd(x,\ y) = 1]
$$

至于计算

$$
\sum_{x = 1}^{\left\lfloor {\frac{n}{d}}\right\rfloor}\sum_{y = 1}^{\left\lfloor {\frac{m}{d}}\right\rfloor}[\gcd(x,\ y) = 1]
$$

等介绍完莫比乌斯反演后，一切就都会揭晓

### 莫比乌斯函数

本讲我们介绍莫比乌斯函数，这也是一个常见的积性函数，其定义式如下所示

$$
\mu(n)=
\begin{cases}
1&n=1\\
0&n\text{ 含有平方因子}\\
(-1)^k&k\text{ 为 }n\text{ 的本质不同质因子个数}\\
\end{cases}
$$

#### 常数函数的狄利克雷卷积逆元

莫比乌斯函数 $\mu$ 是常数函数 $1$ 的狄利克雷卷积逆元，即

$$
\mu * 1 = \varepsilon
$$

##### 从验证的角度着手

我们来验证一下莫比乌斯函数是否是常数函数的狄利克雷卷积逆元，回顾一下狄利克雷卷积逆元

当 $n = 1$ 时

$$
g(n) = \frac{1}{f(1)}
$$

当 $n > 1$ 时

$$
g(n) = -\frac{\sum\limits_{d\mid n,\ d > 1}f(d)g(\frac{n}{d})}{f(1)}
$$

设 $g * 1 = \varepsilon$，我们来验证 $g$ 是否等于 $\mu$

注意到 $1(n) = 1$，当 $n = 1$ 时，代入便能验证

$$
g(1) = \frac{1}{1(1)} = 1
$$

当 $n\neq 1$ 时

$$
g(n) = -\sum\limits_{d\mid n,\ d > 1}g(\frac{n}{d})
$$

考虑两种特殊的情形

- 当 $n$ 为质数，即 $n = p$，有 $g(p) = -g(1) = -1$
- 当 $n$ 为质数幂，即 $n = p^{k}$，有 $g(p^k) = -\sum\limits_{i = 1}^{k - 1}g(p^i)$，我们可以先考虑 $k = 2$ 的情形，发现 $g(p^2) = -g(p) - g(1) = 0$，由此往 $k\geq 3$ 的情况做数学归纳，可以得到 $g(p^k) = 0$

如果你还记得之前介绍的结论：积性函数的狄利克雷卷积逆元仍然是积性函数

那么当 $n$ 为质数乘积，即 $n = \prod\limits_{i = 1}^{k}p_{i}$ 时

$$
\begin{aligned}
g(n) & = g(\prod_{i = 1}^{k}p_{i})\\
& = \prod_{i = 1}^{k}g(p_{i})\\
& = (-1)^k
\end{aligned}
$$

当 $n$ 中至少含有一个质因数两次时，乘积中就会出现 $0$，此时 $g(n) = 0$

我们发现，每一种情况 $g$ 的取值都与 $\mu$ 如出一辙，因此 $g = \mu$，是 $1$ 的狄利克雷卷积

##### 从狄利克雷卷积角度探索

考虑计算狄利克雷卷积

$$
\begin{aligned}
(\mu * 1)(n) & = \sum_{d\mid n}\mu(d)1(\frac{n}{d})\\
& = \sum_{d\mid n}\mu(d)\\
\end{aligned}
$$

当 $n = 1$ 时，$(\mu * 1)(1) = \mu(1) = 1$

当 $n\neq 1$ 时，设 $n = \prod\limits_{i = 1}^{k}p_{i}^{\alpha_{i}},\ n' = \prod\limits_{i = 1}^{k}p_{i}$

例如 $n = 12 = 2^2\cdot 3$

则 $n' = 6 = 2\cdot 3$

有 $\sum\limits_{d\mid 12}\mu(12) = \sum\limits_{d\mid 6}\mu(6)$

因此

$$
\begin{aligned}
(\mu * 1)(n) & = \sum_{d\mid n}\mu(d) = \sum_{d\mid n'}\mu(d)\\
& = \sum_{i = 0}^{k}C_{k}^{i}(-1)^{i} = \sum_{i = 0}^{k}C_{k}^{i}(-1)^{i}1^{k - i}\\
& = (1+(-1))^{k}\\
& = 0
\end{aligned}
$$

上面的操作，实际上是在挑选 $n'$ 的质因子，因为 $n'$ 的任意因数，都可以由 $n'$ 的质因子组合乘积而成

综上所述，我们得到一个结论

$$
\mu * 1 = \varepsilon
$$

也就是说，莫比乌斯函数 $\mu$ 是常数函数 $1$ 的狄利克雷卷积逆元

#### 莫比乌斯函数是积性函数

上面也提到了 $\mu$ 是积性函数，这不仅可以从定义式证明，也可以从狄利克雷卷积逆元的角度证明

#### 莫比乌斯函数的性质

对上面提到的结论总一个总结

- $\mu$ 是积性函数
- $
\sum\limits_{d\mid n}\mu(d)=
\begin{cases}
1&n=1\\
0&n\neq 1\\
\end{cases}
$
- $\mu * 1 = \varepsilon$

#### 线性筛莫比乌斯函数

研究积性函数，很重要的一点是研究该积性函数能否被线性筛预处理

是的，莫比乌斯一样可以被线性筛

首先 $\mu(1) = 1$，其次考虑筛的过程，对于质因子 $p$ 和当前枚举的数 $i$

- 如果 $i$ 本身是素数，则 $\mu(i) = -1$
- 如果 $i\equiv 0\ (mod\ p)$，那么说明在 $i$ 中，质因子 $p$ 已经出现了一次，那么 $p\cdot i$ 中至少出现 $p$ 两次，因此 $\mu(p\cdot i) = 0$
- 如果 $i\not\equiv 0\ (mod\ p)$，那么根据积性函数性质，有 $\mu(p\cdot i) = \mu(p)\cdot \mu(i)$

```cpp
mu[1] = 1;
for (int i = 2; i <= n; ++i)
{
    if (!vis[i]) prime[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && prime[j] * i <= n; ++j) {
        vis[i * prime[j]] = 1;
        mu[i * prime[j]] = mu[i] * mu[prime[j]];
        if (i % prime[j] == 0) {
            mu[i * prime[j]] = 0;
            break;
        }
    }
}
```

### 莫比乌斯反演

设 $f(n),\ g(n)$ 为两个数论函数，莫比乌斯反演指的是

如果有

$$
f(n) = \sum_{d\mid n}g(d)
$$

那么有

$$
g(n)=\sum_{d\mid n}\mu(d)f(\frac{n}{d})
$$

#### 从狄利克雷卷积角度推导公式

在介绍了狄利克雷卷积以及莫比乌斯函数之后，我们可以轻易地从狄利克雷卷积角度证明上面的公式，我们将上面的式子写成卷积形式

$$
f = 1 * g
$$

上式两边同时卷积 $\mu$，根据 $\mu$ 是 $1$ 的狄利克雷卷积逆元，再根据结合律，以及 $\varepsilon$ 单位元的性质

$$
\begin{aligned}
\mu * f & = (\mu * 1) * g\\
& = \varepsilon * g\\
& = g
\end{aligned}
$$

于是

$$
g(n) = \sum_{d\mid n}\mu(d)f(\frac{n}{d})
$$

#### 最大公因数遇上莫比乌斯函数

由前面的推导我们知道

$$
\sum\limits_{d\mid n}\mu(d)=
\begin{cases}
1&n=1\\
0&n\neq 1\\
\end{cases}
$$

对于任意两个数 $i,\ j$，我们用 $\gcd(i,\ j)$ 替换 $n$，于是得到下面的结论

$$
[\gcd(i,\ j) = 1]=\sum\limits_{d\mid \gcd(i,\ j)}\mu(d)
$$

上式即为

$$
\varepsilon(\gcd(i,\ j)) = \sum\limits_{d\mid \gcd(i,\ j)}\mu(d)
$$

#### 常见的问题形式

之所以要介绍最大公因数与莫比乌斯函数的结合，是因为在一般情况下，构造一个

$$
f(n) = \sum\limits_{d\mid n}g(d)
$$

形式的式子是比较难的，我们通常把问题化成 $\gcd$ 的形式，然后通过莫比乌斯反演来计算答案

#### 莫比乌斯反演例题

莫比乌斯反演的题大多是凑出 $\gcd$ 的形式，结合提取公因式和整除分块两大技巧，以及线性筛莫比乌斯函数解决问题

纸上得来终觉浅，绝知此事要躬行

##### 例 $1$

给定 $n,\ m$，计算

$$
\sum_{i = 1}^{n}\sum_{j = 1}^{m}[\gcd(i,\ j) = 1]
$$

使用莫比乌斯反演

$$
[\gcd(i,\ j) = 1] = \sum\limits_{d\mid \gcd(i,\ j)}\mu(d)
$$

得到

$$
\sum_{i = 1}^{n}\sum_{j = 1}^{m}\sum_{d\mid \gcd(i,\ j)}\mu(d)
$$

提取公因式，上式变为

$$
\begin{aligned}
& \sum_{d = 1}\mu(d)\sum_{i = 1}^{\left\lfloor {\frac{n}{d}}\right\rfloor}\sum_{j = 1}^{\left\lfloor {\frac{m}{d}}\right\rfloor}1\\
= & \sum_{d = 1}\mu(d)\left\lfloor {\frac{n}{d}}\right\rfloor\left\lfloor {\frac{m}{d}}\right\rfloor
\end{aligned}
$$

线性筛预处理 $\mu$ 的前缀和，结合二维数论分块，便可以在 $O(N + \sqrt{N})$ 时间计算答案，其中 $N = \min(n,\ m)$

##### 例 $2$

给定 $n,\ m,\ k$，计算

$$
\sum_{i = 1}^{n}\sum_{j = 1}^{m}[\gcd(i,\ j) = k]
$$

变换得到

$$
\sum_{x=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{y=1}^{\lfloor\frac{m}{k}\rfloor}[\gcd(x,y)=1]
$$

莫比乌斯反演

$$
\displaystyle\sum_{x=1}^{\lfloor\frac{n}{k}\rfloor}\sum_{y=1}^{\lfloor\frac{m}{k}\rfloor}\sum_{d\mid  \gcd(x,y)}\mu(d)
$$

提取公因数后化简

$$
\displaystyle\sum_{d=1}\mu(d)\lfloor\frac{n}{kd}\rfloor\lfloor\frac{m}{kd}\rfloor
$$

预处理莫比乌斯函数，二维整除分块即可，时间复杂度仍然是 $O(N + \sqrt{N})$

事实上，这题只比上一题在整除分块的分母上多乘以了个 $k$ 而已

## 题目选讲

### 2636 莫比乌斯函数

给定 $n$，计算

$$
\sum_{i = 1}^{n}i\mu(i)
$$

$1\leq n,\ m\leq 10^7$

#### 题解

用线性筛筛莫比乌斯函数后计算

```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 1e7 + 7;
int cnt, mu[N], vis[N], prime[N];
void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < N; ++i)
    {
        if (!vis[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i < N; ++j) {
            vis[i * prime[j]] = 1;
            mu[i * prime[j]] = mu[i] * mu[prime[j]];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
int main()
{
    sieve();
    LL ans = 0;
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        ans += 1LL * i * mu[i];
    }
    cout << ans << endl;
    return 0;
}
```

### 2635 互质对的数量

给定 $n,\ m$，对于所有 $i,\ j$，满足 $1\leq i\leq n,\ 1\leq j\leq m$，计算 $\gcd(i,\ j) = 1$ 的 $(i,\ j)$ 对数量，换句话说，计算所有互质对的数量

$1\leq n,\ m\leq 10^7$

#### 题解

参考上面的例题讲解，最后计算

$$
\sum_{d = 1}^{min(n,\ m)}\mu(d)\lfloor\frac{n}{d}\rfloor\lfloor\frac{m}{d}\rfloor
$$

线性筛预处理莫比乌斯前缀和，然后二维整除分块，时间复杂度为 $O(n + \sqrt{n})$

```cpp
#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

const int N = 5e4 + 7;
int cnt, mu[N], vis[N], prime[N];
void sieve()
{
    mu[1] = 1;
    for (int i = 2; i < N; ++i)
    {
        if (!vis[i]) prime[++cnt] = i, mu[i] = -1;
        for (int j = 1; j <= cnt && prime[j] * i < N; ++j) {
            vis[i * prime[j]] = 1;
            mu[i * prime[j]] = mu[i] * mu[prime[j]];
            if (i % prime[j] == 0) {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}

LL solve(LL n, LL m)
{
    LL ans = 0;
    if (n < m) swap(n, m);
    for (LL l = 1, r; l <= min(n, m); l = r + 1) {
        r = min(n / (n / l), m / (m / l));
        ans += (mu[r] - mu[l - 1]) * (n / l) * (m / l);
    }
    return ans;
}
int main()
{
    sieve();
    for (int i = 1; i < N; ++i) mu[i] += mu[i - 1];
    LL a, b;
    scanf("%lld %lld", &a, &b);
    LL ans = solve(a, b); 
    cout << ans << endl;
    return 0;
}
```