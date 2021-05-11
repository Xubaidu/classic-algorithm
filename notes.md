# 数学 07

## 知识点

### 高斯消元

#### 从简单的方程组入手

给定二元一次方程

$$
\left\{\begin{matrix}
x + 3y = 16\\
x - 3y = 10
\end{matrix}\right.
$$

将两个方程相减，消元 $x$ 得到

$$
6y = 6
$$

从而计算出

$$
y = 1
$$

将 $y = 1$ 随意带入两个方程，都可以计算出 $x = 13$

#### 用系数矩阵表示三元一次方程组的消元过程

给定三元一次方程

$$
\left\{\begin{matrix}
x + 3y + 4z = 272\\
x - 3y - 5z = 170\\
x + 6y - 4z = 204\\
\end{matrix}\right.
$$

我们省略未知数，将其写成系数矩阵的形式，最后一列为等号右边的数值，具体如下所示

$$
\begin{bmatrix}
1 & 3 & 4 & 1\\
1 & -3 & -5 & 2\\
1 & 6 & -4 & 3
\end{bmatrix}
$$

我们手动模拟一下消元的过程

$$
\begin{aligned}
\begin{bmatrix}
1 & 3 & 4 & 1\\
1 & -3 & -5 & 2\\
1 & 6 & -4 & 3
\end{bmatrix}
& \xrightarrow[r_{3} - r_{1}]{r_{2} - r_{1}}
\begin{bmatrix}
1 & 3 & 4 & 1\\
0 & -6 & -9 & 1\\
0 & 3 & -8 & 1
\end{bmatrix}\\
& \xrightarrow[]{r_{2}\times -\frac{1}{6}}
\begin{bmatrix}
1 & 3 & 4 & 272\\
0 & 1 & \frac{3}{2} & 17\\
0 & 3 & -8 & -68
\end{bmatrix}\\
& \xrightarrow[r_{3} - 3r_{2}]{r_{1} - 3r_{2}}
\begin{bmatrix}
1 & 0 & -\frac{1}{2} & 221\\
0 & 1 & \frac{3}{2} & 17\\
0 & 0 & -\frac{17}{2} & -119
\end{bmatrix}\\
& \xrightarrow[]{r_{3}\times -\frac{2}{17}}
\begin{bmatrix}
1 & 0 & -\frac{1}{2} & 221\\
0 & 1 & \frac{3}{2} & 17\\
0 & 0 & 1 & 14
\end{bmatrix}\\
& \xrightarrow[r_{2} - \frac{3}{2}r_{3}]{r_{1} - (-\frac{1}{2})r_{3}}
\begin{bmatrix}
1 & 0 & 0 & 228\\
0 & 1 & 0 & -4\\
0 & 0 & 1 & 14
\end{bmatrix}\\
\end{aligned}
$$

从而计算出

$$
x = 228,\ y = -4,\ z = 14
$$

#### 行阶梯形矩阵

事实上，上面的操作将原方程组变换成如下形式，我们称这个形式为 **行阶梯形矩阵**

$$
\begin{bmatrix}
1 & 0 & 0 & \frac{228}{17}\\
0 & 1 & 0 & -\frac{4}{17}\\
0 & 0 & 1 & \frac{14}{17}
\end{bmatrix}
$$

#### 一些误差




#### 

### 拉格朗日插值

## 题目选讲

### 1. 高斯消元

### 2. 拉格朗日插值