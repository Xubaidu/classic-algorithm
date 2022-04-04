# problems

## 2587. 同余方程

给定正整数 $a,\ b,\ m$，计算同余方程 $ax\equiv b\ (mod\ m)$ 的最小正整数解

输入保证

对于 $40\%$ 数据，$2\leq a,\ b\leq m\leq 1,000$

对于 $60\%$ 数据，$2\leq a,\ b\leq m\leq 10,000,000$

对于 $100\%$ 数据，$2\leq a,\ b\leq m\leq 1,000,000,000$

## 2545. 中国剩余定理

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

## 2553. 扩展中国剩余定理（选做）

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

## 2545. 构造函数（选做）

给定质数 $p$，整数 $n$ 和 $n$ 个互不相同整数 $a_i$，以及整数 $k$

计算整数对 $(i,\ j)(1\leq i < j\leq n)$ 的数量，使得 $(a_{i} + a_{j})(a_{i}^2 + a_{j}^2)\equiv k\ (mod\ p)$

输入保证，$2\leq n\leq 3\cdot 10^5,\ 2\leq p\leq 10^9,\ 0\leq k\leq p - 1$, $0\leq a_{i}\leq p - 1$
