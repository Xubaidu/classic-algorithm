# 数学 $01$

[toc]

## 知识点

### 最大公因数 $gcd$

> 给定整数 $a,\ b,\ c$，若 $c\mid a,\ c\mid b$（其中 $\mid$ 是整除符），则称 $c$ 是 $a,\ b$ 的公因数，若 $c$ 是最大的，则称 $c$ 为最大公因数，记为 $c = (a,\ b)$

### 最小公倍数 $lcm$

> 给定整数 $a,\ b,\ c$，若 $a\mid c,\ b\mid c$（其中 $\mid$ 是整除符），则称 $c$ 是 $a,\ b$ 的公倍数，若 $c$ 是最小的，则称 $c$ 为最小公倍数，记为 $c = [a,\ b]$

### 最小公倍数与最大公因数的关系

给定整数 $a,\ b$，则

$$
[a,\ b] = \frac{a\cdot b}{(a,\ b)}
$$

### $gcd$ 的性质

给定整数 $a,\ b,\ c$，关于 $gcd$ 的常用性质如下

- **结合律** $a,\ b,\ c$ 的最大公因数即为 $((a,\ b),\ c)$
- **交换律** $(a,\ b) = (b,\ a)$
- **辗转相除** $(a,\ b) = (b,\ a\ mod\ b)$
- **辗转相减** $(a,\ b) = (b,\ a- b)$
- **$0$ 被任何数整除** $(a,\ 0) = |a|$
- **消去负号** $(a,\ -b) = (a,\ b)$

### 欧几里得算法

欧几里得算法用来求解最大公因数，也称之为辗转相除法

算法原理基于性质 $(a,\ b) = (b,\ a\ mod\ b)$，如此不断辗转相除下去，$a\ mod\ b$ 最终会为 $0$，此时输出对应的 $b$ 即为最大公因数

时间复杂度为 $O(logb)$，代码如下

```cpp
int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
```

### 扩展欧几里得算法

记 $(a,\ b)$ 表示 $gcd(a,\ b)$，根据贝祖等式有

$$
ax + by = (a,\ b)
$$

扩展欧几里得算法不仅可以计算出 $(a,\ b)$，还可以计算出系数 $x,\ y$

时间复杂度为 $O(logb)$

#### 扩展欧几里得求法

我们知道，当 $(a,\ b)$ 递归到最深处时，有 $a = (a,\ b),\ b = 0$

所以 $a\cdot 1 + b\cdot 0 = a$，即 $x = 1,\ y = 0$

考虑已经求出 $(b,\ a\% b)$ 下的 $x',\ y'$ ，即

$$
b\cdot x' + (a\%b)\cdot y' = (b,\ a\%b)
$$

由 $a\%b = a - \left \lfloor \frac{a}{b} \right \rfloor\cdot b$，代入上式得到

$$
a\cdot y' + b\cdot (x' - \left \lfloor \frac{a}{b} \right \rfloor\cdot y') = (b,\ a\%b)
$$

再根据 $(b,\ a\%b) = (a,\ b)$，得到

$$
a\cdot x + b\cdot y = a\cdot y' + b\cdot (x' - \left \lfloor \frac{a}{b} \right \rfloor\cdot y')$$

所以 $x = y',\ y = x' - \left \lfloor \frac{a}{b} \right \rfloor\cdot y'$

如此回溯，可以得到 $a$ 和 $b$ 的最大公因数 $r = (a,\ b)$，以及贝祖等式的一组系数 $x_{0},\ y_{0}$，满足 $ax_{0} + by_{0} = (a,\ b)$

为了得到通解，设 $x = x_{0} + s,\ y = y_{0} + t$，代入贝祖等式，得到 $as = -bt$，

取 $q\in \mathbb{Z}$，观察知道

$$
s = q\cdot \frac{b}{r},\ t = -q\cdot \frac{a}{r}
$$

所以通解为

$$
\begin{aligned}
x & = x_{0} + q\cdot \frac{b}{r}\\
y &= y_{0} - q\cdot \frac{a}{r}
\end{aligned}
$$

面对更加一般的等式 $ax + by = c$，当且仅当 $(a,\ b)\mid c$ 时方程有解，若设 $k = \frac{c}{(a,\ b)}$，则通解为

$$
\begin{aligned}
x & = k\cdot(x_{0} + q\cdot \frac{b}{r})\\
y & = k\cdot(y_{0} - q\cdot \frac{a}{r})
\end{aligned}
$$

#### 扩欧代码

```cpp
int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x); // y 的值被修改为 x', x 的值被修改为 y'
    y -= (a / b) * x;
    return r;
}

pair<int, int> getXY(int a, int b, int r, int x, int y)
{
    int add = b / r;
    while(x < 0) x += add;
    x %= add;
    y = (r - x * a) / b;
    return {x, y};
}
```

## 题目

### 2559. 蛋糕分享

#### 题意

给定一个长 $x$ 米，宽 $y$ 米的长方形，希望把这个长方形切割成若干个一样大的正方形，请问每个正方形的边长最大多少米

$0 < x,\ y\leq 2^{31}$

#### 题解

要把长方形完美分割成若干个一样大的正方形，那么正方形的边长必须满足是长和宽的公因数，边长最大，即求最大公因数

```cpp
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    cout << gcd(a, b) << endl;
    return 0;
}
```

### 360. 外星开发

#### 题意

给定一个长 $x$ 米，宽 $y$ 米的长方形，把这个长方形切割成若干个一样大的正方形，请问每个正方形的边长最大多少米

$0 < x,\ y\leq 10^{100}$

#### 题解

大数运算 $gcd$

```cpp
#include<bits/stdc++.h>
using namespace std;

const int SIZE=109;
int x[SIZE],y[SIZE],q[SIZE],r[SIZE],zero[SIZE];
void copy(int *a, int *b) {
    for (int i=0;i<SIZE;i++) a[i]=b[i];
}
void converts(int *a,string s){
    int i,len=(int)s.size();
    for (i=0;i<len;i++) a[i]=s[len-i-1]-'0';
    for (;i<SIZE;i++) a[i]=0;
}
bool le(int *a,int *b,int len=SIZE) {
    int i;
    for (i=len-1;i>=0 && a[i]==b[i]; i--);
    return i<0 || a[i]<b[i];
}
void sub(int *a,int *b,int len=SIZE) {
    for(int i=0;i<len;i++)
        if((a[i]-=b[i])<0) a[i+1]--,a[i]+=10;
}
void print(int *a){
    int i;
    for(i=SIZE-1;i>0;i--) if(a[i]>0) break;
    for(;i>=0;i--) cout<<a[i]; cout<<endl;
}
void div(int *q,int *r,int *a,int *b){
    converts(q,"0");
    copy(r,a);
    int j;
    for (j=SIZE-1;b[j]==0;j--);
    for (int i=SIZE-1-j;i>=0;i--)
        for (;le(b,r+i,SIZE-i);q[i]++)
            sub(r+i,b,SIZE-i);
}
void gcd(int *a,int *b){
//    print(a),print(b);
    div(q,r,a,b);
    if (le(r,zero)) { print(b); return; }
    copy(a,b),copy(b,r);
    gcd(a,b);
}

int main(){
    string s1,s2;
    cin>>s1>>s2;
    converts(x,s1),converts(y,s2);
    gcd(x,y);
    return 0;
}
```

### 2545. 传说中的欧几里得

#### 题意

给定 $a,\ b$，计算最小的非负整数 $x$ 和整数 $y$，使得 $ax + by = 1$

数据保证 $0 < a,\ b\leq 2^{31}$

#### 题解

模板题，直接上扩展欧几里得算法

```cpp
#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
#define LL long long
#define pii pair<int, int>
#define fi first
#define se second
using namespace std;

int qpow(int a, int b, int m)
{
    int ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= m;
        a *= a, a %= m, b >>= 1;
    }
    return ans;
}
int exgcd(int a, int b, int &x, int &y)
{
    if(!b) {x = 1, y = 0; return a;}
    int r = exgcd(b, a % b, y, x); // y 的值被修改为 x', x 的值被修改为 y'
    y -= (a / b) * x;
    return r;
}

pair<int, int> getXY(int a, int b, int r, int x, int y)
{
    int add = b / r;
    while(x < 0) x += add;
    x %= add;
    y = (r - 1LL * x * a) / b;
    return {x, y};
}
int main()
{
    int a, b;
    scanf("%d%d", &a, &b);
    int x, y;
    int r = exgcd(a, b, x, y);
    if(r != 1) puts("sorry");
    else {
        pair<int, int> p = getXY(a, b, r, x, y);
        printf("%d %d\n", p.first, p.second);
    }
    return 0;
}
```