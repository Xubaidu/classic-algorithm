## $1.$ 背景

### $1.1$ 生成公钥密钥

随机选取大素数 $p,\ q$，计算 $n = pq,\ \lambda = [p - 1,\ q - 1]$，保证 $(pq,\ (p - 1)\cdot (q - 1)) = 1$，即 $(n,\ \phi(n)) = 1$

随机选取 $g\in \mathbb{Z_{n^2}^{*}}$，计算 $\mu = [L(g^{\lambda}\ mod\ n^2)]^{-1}\ mod\ n$，其中 $L(x) = \frac{x - 1}{n}$

令 $(n,\ g)$ 为公钥，$(p,\ q,\ \lambda)$ 为私钥

多说一嘴，很多人无法理解为何保证了 $(p,\ q) = 1$，还要保证 $(n,\ \phi(n)) = 1$，事实上如果构造出 $p = kq + 1$，那么 $n$ 和 $\phi(n)$ 就出现了 $q$ 这个公因子

### $1.2$ 加密

将明文 $m$ 映射成正整数

选取 $r\in \mathbb{Z_{n}^{*}}$，这意味着 $(r,\ n) = 1$

计算密文 $c = g^{m}\cdot r^{n}\ (mod\ n^2)$

### $1.3$ 解密

计算 $m = L(c^{\lambda}\ mod\ n^2)\cdot \mu\ (mod\ n)$

### $1.4$ 正确性

>$paillier$ 算法的正确性基于以下事实
$$
(1 + n)^{x}\equiv 1 + nx\ (mod\ n^2)
$$

由

$$
\lambda = [p - 1,\ q - 1] = \frac{(p - 1)(q - 1)}{(p - 1,\ q - 1)}
$$

所以对于 $\forall v\in \mathbb{Z}$，满足

$$
v^{\lambda}\equiv 1\ (mod\ p),\ v^{\lambda}\equiv 1\ (mod\ q)
$$

所以 $v^{\lambda}\equiv 1\ (mod\ n)$，这是因为 $n = pq$ 且 $(p, q) = 1$

所以有 $g^{\lambda}\equiv 1\ (mod\ n),\ r^{\lambda}\equiv 1\ (mod\ n)$

不妨设 $g^{\lambda} = 1 + qn,\ r^{\lambda} = 1 + q'n$，满足 $q,\ q'\in \mathbb{Z}$

计算

$$
\begin{aligned}
c^{\lambda} & \equiv g^{m\lambda}\cdot r^{n\lambda}\ (mod\ n^2)\\
& \equiv (1 + qn)^{m}\cdot (1 + q'n)^{n}\ (mod\ n^2)\\
& \equiv (1 + qnm)\cdot (1 + q'n^2)\ (mod\ n^2)\\
& \equiv 1 + qnm\ (mod\ n^2)
\end{aligned}
$$

所以

$$
\frac{c^{\lambda} - 1}{n}\equiv qm\ (
mod\ n^2)
$$

同理计算出

$$
\frac{g^{\lambda} - 1}{n}\equiv q\ (mod\ n^2)
$$

所以

$$
m\equiv \frac{\frac{c^{\lambda} - 1}{n}\ mod\ n^2}{\frac{g^{\lambda} - 1}{n}\ mod\ n^2}\equiv qm\cdot q^{-1}\equiv m\ (mod\ n)
$$

### $1.5$ 随机选取 $g$

令 $g = 1 + n$

则 $(1 + n)^n\equiv 1 + n^2\equiv 1\ (mod\ n^2)$，这意味着 $ord(1 + n)\mid n$

而对于 $0 < k < n$，有 $(1 + n)^k\equiv 1 + kn\not\equiv 1\ (mod\ n^2)$，所以 $ord(1 + n) = n$

进一步，令 $g = 1 + kn,\ 0 < k < n$

则 $(1 + kn)^n\equiv 1\ (mod\ n^2)$

对于 $0 < k' < n$，有 $(1 + kn)^{k'}\equiv 1 + k'kn\ (mod\ n^2)$，只需要 $kk'\not\equiv 0\ (mod\ n)$ 即可，即

$$
k\not\equiv p\ (mod\ n),\ k\not\equiv q\ (mod\ n)
$$

所以对 $g$ 的随机选取，转化为对 $k\in \mathbb{Z_{n}^{*}}$ 的随机选取

### $1.6$ 加法同态性

考虑加密 $m_{1} + m_{2}$，得到

$$
c = Enc(m_{1} + m_{2}) \equiv g^{m_{1}+m_{2}}(mod\ n^2)
$$

在考虑分别加密 $m_{1},\ m_{2}$，得到

$$
\begin{aligned}
c_{1} & = Enc(m_{1})\equiv g^{m_{1}}\cdot r_{1}^{n}\ (mod\ n^2)\\
c_{2} & = Enc(m_{2})\equiv g^{m_{2}}\cdot r_{2}^{n}\ (mod\ n^2)
\end{aligned}
$$

所以

$$
c_{1}c_{2}\equiv g^{m_{1} + m_{2}}\cdot (r_{1}\cdot r_{2})^n\ (mod\ n^2)
$$

考虑解密 $c_{1}c_{2}$，设 $g^{\lambda} = 1 + qn,\ q\in \mathbb{Z_{n}}^{*}$

$$
(c_{1}c_{2})^{\lambda}\equiv 1 + qn(m_{1} + m_{2})\ (mod\ n^2)
$$

剩下的计算与之前类似，解密得到明文为 $m_{1} + m_{2}$

也就是说 $c_{1}c_{2}$ 的解密结果为 $m_{1} + m_{2}$，即

$$
Dec(Enc(m_{1})\cdot Enc(m_{2})) = m_{1} + m_{2}
$$

满足加法同态

至于为什么是加法同态，是因为我们对明文的操作是加法

## $2.$ 问题描述

- 随机选择两个 $10$ 位素数，这里指的是 $10$ 位二进制串
- 令 $n = pq$，随机选择 $g$，计算公钥和私钥
- 设消息 $m_{1} = 15,\ m_{2} = 20$，随机选取 $r_{1},\ r_{2}\in \mathbb{Z_{n}^{*}}$，求 $m_{1},\ m_{2}$ 的密文 $c_{1},\ c_{2}$
- 对 $c_{1},\ c_{2}$ 进行解密，求 $m'_{1},\ m'_{2}$
- 对 $c_{1}c_{2}$ 做解密运算，得到 $m'$，验证 $m' = m_{1} + m_{2}$

## $3.$ 问题解与分析

### $3.1$ 随机构造两个 $10$ 位素数 $p,\ q$

用字符串生成，转化为整数，并判断是否是素数，注意字符串的首末位都为 $1$

```cpp
bool isPrime(int x)
{
    if(x == 1) return 0;
    for(int i = 2; i * i <= x; ++i)
        if(x % i == 0) return 0;
    return 1;
}

int getPrime(int L)
{
    int ans = 0;
    do {
        ans = 1;
        for(int i = 0; i < L - 2; ++i)
            ans *= 2, ans += rand() % 2;
        ans *= 2, ans += 1;
    }while(!isPrime(ans));
    return ans;
}
```

### $3.2$ 随机选择 $g$，计算公钥和私钥

$g = 1 + kn,\ k\in \mathbb{Z_{n}^{*}}$，对 $g$ 的随机转化为对 $k$ 的随机

先筛出 $\mathbb{Z_{n}^{*}}$，然后随机返回 $k\in \mathbb{Z_{n}^{*}}$，计算具体的公钥和密钥

```cpp
struct PBK
{
    int n;
    LL g;
    PBK() {}
    PBK(int _n, LL _g): n(_n), g(_g) {}
    void out() { cout << "公钥 <n, g>: <" << n << ", " << g << ">" << endl; }
};

struct SK
{
    int p, q, lambda;
    SK() {}
    SK(int _p, int _q, int _lambda): p(_p), q(_q), lambda(_lambda) {}
    void out() { cout << "私钥 <p, q, lambda>: <" << p << ", " << q << ", " << lambda << ">" << endl; }
};

void getZnStar(vector<int>& ZnStar, int n)
{
    for(int i = 1; i < n; ++i)
        if(__gcd(i, n) == 1)
            ZnStar.pb(i);
}

int getNumOfZnStar(vector<int>& ZnStar) { return ZnStar[rand() % ZnStar.size()]; }

int getLambda(int p, int q) { return (p - 1) * (q - 1) / __gcd(p - 1, q - 1); }

pair<PBK, SK> getPublicKey(int L, vector<int>& ZnStar)
{
    int n, p, q, lambda;
    LL g;
    while(1) {
        p = getPrime(L);
        q = getPrime(L);
        lambda = getLambda(p, q);
        n = p * q;
        if(__gcd(n, lambda) == 1 && p != q) break;
    }
    LL nn = 1LL * n * n;
    getZnStar(ZnStar, n);
    g = (1 + 1LL * n * getNumOfZnStar(ZnStar)) % nn;
    return {PBK(n, g), SK(p, q, lambda)};
}
```

### $3.3$ 加密 $m_{1},\ m_{2}$

根据方案进行模拟，加密函数如下，$qmul()$ 为快速乘算法，避免爆出 $long\ long$ 范围，$qpow()$ 为快速幂算法，$nn$ 为 $n^2$

```cpp
LL encryption(int m, LL g, int n, vector<int>& ZnStar)
{
    LL nn = 1LL * n * n;
    LL r = getNumOfZnStar(ZnStar);
    LL c = qmul(qpow(g, m, nn), qpow(r, n, nn), nn);
    return c;
}
```

### $3.4$ 解密 $m_{1},\ m_{2}$

根据方案进行模拟，解密函数如下

```cpp
LL getLx(LL x, int n, LL nn) { return (x - 1) / n % nn; }

LL decryption(LL c, LL g, int n, int lambda)
{
    LL nn = 1LL * n * n;
    LL x1 = qpow(c, lambda, nn), L1 = getLx(x1, n, nn);
    LL x2 = qpow(g, lambda, nn), L2 = getLx(x2, n, nn);
    LL mu = getInv(L2, n);
    LL plaintext = L1 * mu % n;
    return plaintext;
}
```

### $3.5$ 验证同态

判断 $m_{1} + m_{2} = Dec(m_{1}\cdot m_{2})$ 即可

## $4.$ 代码

```cpp
#include <bits/stdc++.h>
#define LL long long
#define pb push_back
using namespace std;

struct PBK
{
    int n;
    LL g;
    PBK() {}
    PBK(int _n, LL _g): n(_n), g(_g) {}
    void out() { cout << "公钥 <n, g>: <" << n << ", " << g << ">" << endl; }
};

struct SK
{
    int p, q, lambda;
    SK() {}
    SK(int _p, int _q, int _lambda): p(_p), q(_q), lambda(_lambda) {}
    void out() { cout << "私钥 <p, q, lambda>: <" << p << ", " << q << ", " << lambda << ">" << endl; }
};

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

LL qpow(LL a, LL b, LL MOD)
{
    if(!a) return 0;
    LL ans = 1;
    while(b) {
        if(b & 1) ans = qmul(ans, a, MOD), ans %= MOD;
        a  = qmul(a, a, MOD), a %= MOD, b >>= 1;
    }
    return ans;
}

LL phi(LL m)
{
    LL ans = m;
    for(LL i = 2; i * i <= m; ++i) {
        if(m % i == 0) {
            ans -= ans / i;
            while(m % i == 0) m /= i;
        }
    }
    if(m > 1) ans -= ans / m;
    return ans;
}

LL getInv(LL a, LL MOD)
{
    return qpow(a, phi(MOD) - 1, MOD);
}

bool isPrime(int x)
{
    if(x == 1) return 0;
    for(int i = 2; i * i <= x; ++i)
        if(x % i == 0) return 0;
    return 1;
}

int getPrime(int L)
{
    int ans = 0;
    do {
        ans = 1;
        for(int i = 0; i < L - 2; ++i)
            ans *= 2, ans += rand() % 2;
        ans *= 2, ans += 1;
    }while(!isPrime(ans));
    return ans;
}

void getZnStar(vector<int>& ZnStar, int n)
{
    for(int i = 1; i < n; ++i)
        if(__gcd(i, n) == 1)
            ZnStar.pb(i);
}

int getNumOfZnStar(vector<int>& ZnStar) { return ZnStar[rand() % ZnStar.size()]; }

int getLambda(int p, int q) { return (p - 1) * (q - 1) / __gcd(p - 1, q - 1); }

pair<PBK, SK> getPublicKey(int L, vector<int>& ZnStar)
{
    int n, p, q, lambda;
    LL g;
    while(1) {
        p = getPrime(L);
        q = getPrime(L);
        lambda = getLambda(p, q);
        n = p * q;
        if(__gcd(n, lambda) == 1 && p != q) break;
    }
    LL nn = 1LL * n * n;
    getZnStar(ZnStar, n);
    g = (1 + 1LL * n * getNumOfZnStar(ZnStar)) % nn;
    return {PBK(n, g), SK(p, q, lambda)};
}

LL encryption(int m, LL g, int n, vector<int>& ZnStar)
{
    LL nn = 1LL * n * n;
    LL r = getNumOfZnStar(ZnStar);
    LL c = qmul(qpow(g, m, nn), qpow(r, n, nn), nn);
    return c;
}

LL getLx(LL x, int n, LL nn) { return (x - 1) / n % nn; }
LL decryption(LL c, LL g, int n, int lambda)
{
    LL nn = 1LL * n * n;
    LL x1 = qpow(c, lambda, nn), L1 = getLx(x1, n, nn);
    LL x2 = qpow(g, lambda, nn), L2 = getLx(x2, n, nn);
    LL mu = getInv(L2, n);
    LL plaintext = L1 * mu % n;
    return plaintext;
}
int main()
{
    srand((unsigned)time(NULL));
    int L = 10, m1 = 15, m2 = 20;
    vector<int> ZnStar;

    auto i = getPublicKey(L, ZnStar);
    PBK pbk = i.first;
    SK sk = i.second;
    pbk.out();
    sk.out();

    LL ciphertext1 = encryption(m1, pbk.g, pbk.n, ZnStar);
    LL ciphertext2 = encryption(m2, pbk.g, pbk.n, ZnStar);
    cout << "明文 m1 加密为: " << ciphertext1 << endl;
    cout << "明文 m2 加密为: " << ciphertext2 << endl;

    LL plaintext1 = decryption(ciphertext1, pbk.g, pbk.n, sk.lambda);
    LL plaintext2 = decryption(ciphertext2, pbk.g, pbk.n, sk.lambda);
    LL nn = 1LL * pbk.n * pbk.n;
    LL ciphertext = qmul(ciphertext1, ciphertext2, nn);
    LL plaintext = decryption(ciphertext, pbk.g, pbk.n, sk.lambda);
    cout << "秘文 c1 解密为: " << plaintext1 << endl;
    cout << "秘文 c2 解密为: " << plaintext2 << endl;
    cout << "秘文 c1c2 解密为: " << plaintext << endl;
    if(plaintext1 + plaintext2 == plaintext) cout << "满足同态" << endl;
    return 0;
}
```