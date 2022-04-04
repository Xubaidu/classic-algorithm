# 2554. 扩展中国剩余定理

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