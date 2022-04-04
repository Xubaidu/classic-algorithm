# problems

## 2631. 整除分块

给定正整数 $n$，计算

$$
\sum_{i = 1}^{n}\left\lfloor \frac{n}{i} \right \rfloor\ mod\ 998244353
$$

数据规定

$30\%: 1\leq n\leq 10^{5}$

$60\%: 1\leq n\leq 10^{8}$

$100\%: 1\leq n\leq 10^{12}$

## 2630. 因数个数筛

现在给定正整数 $n$，希望计算

$$
\sum_{i = 1}^{n}d(i)\ mod\ 998244353
$$

和

$$
\sum_{i = 1}^{n}i\cdot d(i)\ mod\ 998244353
$$

数据规定

$1\leq n\leq 10,000,000$

## 2632 区间因数和

我们用 $\sigma(n)$ 表示 $n$ 的所有因数的和

例如 $\sigma(6) = 1 + 2 + 3 + 6 = 12$

例如 $\sigma(10) = 1 + 2 + 5 + 10 = 18$

现在给定 $L,\ R$，计算

$$
\sum_{i = L}^{R}\sigma(i)
$$

数据规定

$30\%: 1\leq L < R \leq 10^5$

$60\%: 1\leq L < R \leq 10^7$

$100\%: 1\leq L < R \leq 2\cdot 10^9$
