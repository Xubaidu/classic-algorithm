# 2545. 构造函数

给定质数 $p$，整数 $n$ 和 $n$ 个互不相同整数 $a_i$，以及整数 $k$

计算整数对 $(i,\ j)(1\leq i < j\leq n)$ 的数量，使得 $(a_{i} + a_{j})(a_{i}^2 + a_{j}^2)\equiv k\ (mod\ p)$

输入保证，$2\leq n\leq 3\cdot 10^5,\ 2\leq p\leq 10^9,\ 0\leq k\leq p - 1$, $0\leq a_{i}\leq p - 1$