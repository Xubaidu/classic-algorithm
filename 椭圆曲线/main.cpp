#include <bits/stdc++.h>
#define pii pair<int, int>
#define fi first
#define se second
#define pb push_back
#define inf 0x3f3f3f3f
using namespace std;

class EllipticCurve
{
private:
    int a, b, MOD;
    pii O = {inf, inf};
    vector<pii> ans;
public:
    int getA();
    int getB();
    int getMOD();
    EllipticCurve();
    EllipticCurve(int _a, int _b, int _MOD);
    void showEllipticCurver();
    void getAllPoints(); // 获取椭圆曲线上所有的点
    void showAllPoints(); // 输出椭圆曲线上所有的点
    int getTangentAtPoint(pii &P); // 获取点 P 处的切线斜率
    int getTangentOfP1P2(pii &P1, pii &P2); // 获取割线 P1P2 的斜率
    pii handleTangent(pii &P); // 处理切线
    pii handleSecant(pii &P1, pii &P2); // 处理割线
    pii addP1P2(pii &P1, pii &P2); // 计算 P1P2 与 E 的第三个交点
    pii getNP(pii &P, int n); // 点幂普通算法
    pii qGetNP(pii &P, int n); // 点幂快速幂算法
    int getOrder(pii &P); // 获取点 P 的阶
};

struct publicKey
{
    EllipticCurve E;
    pii P, Q;
    publicKey() {}
    publicKey(pii _P, pii _Q, EllipticCurve &_E):
        P(_P), Q(_Q), E(_E) {}
};

struct privateKey
{
    int s;
    privateKey() {}
    privateKey(int _s):
        s(_s) {}
};

struct cipherText
{
    int x, y, c;
    cipherText() {}
    cipherText(int _x, int _y, int _c): x(_x), y(_y), c(_c) {}
};

int qpow(int a, int b, int MOD);
int addMOD(int a, int b, int MOD);
int subMOD(int a, int b, int MOD);
int mulMOD(int a, int b, int MOD);
int getInv(int x, int MOD);
void out(pii &P);

void genKey(publicKey &pbk, privateKey &prk, pii P, EllipticCurve &E);
cipherText encryption(publicKey &pbk, int m);
int decryption(publicKey &pbk, privateKey &prk, cipherText &cipher);

int cnt;
int main()
{
    srand((unsigned)time(nullptr));
    pii P = {13, 24};
    EllipticCurve E(20, 4, 29);
    E.showAllPoints();
    E.showEllipticCurver();
    publicKey pbk;
    privateKey prk;
    puts("|待加密明文 | 解密的明文|");
    puts("|---------- | ----------|");
    for (int m = 2; m < 29; ++m) {
        genKey(pbk, prk, P, E);
        cipherText cipher = encryption(pbk, m);
        int plain = decryption(pbk, prk, cipher);
        printf("|    %02d     |     %02d    |\n", m, plain);
    }
    puts("|---------- | ----------|");
    return 0;
}

int qpow(int a, int b, int MOD)
{
    if(!a) return 0;
    int ans = 1;
    while(b) {
        if(b & 1) ans *= a, ans %= MOD;
        a *= a, a %= MOD, b >>= 1;
    }
    return ans;
}

int addMOD(int a, int b, int MOD) {return (a + b) % MOD;}
int subMOD(int a, int b, int MOD) {return (a % MOD - b % MOD + MOD) % MOD;}
int mulMOD(int a, int b, int MOD) {return a * b % MOD;}
int getInv(int x, int MOD) {return qpow(x, MOD - 2, MOD);}

void out(pii &P) {printf("(%d, %d)\n", P.fi, P.se);}

int EllipticCurve::getA() {return a;}
int EllipticCurve::getB() {return b;}
int EllipticCurve::getMOD() {return MOD;}

EllipticCurve::EllipticCurve() {}
EllipticCurve::EllipticCurve(int _a, int _b, int _MOD):
    a(_a), b(_b), MOD(_MOD) {}

void EllipticCurve::getAllPoints()
{
    for(int x = 0; x < MOD; ++x) {
        for(int y = 0; y < MOD; ++y) {
            int left = qpow(y, 2, MOD);
            int right = addMOD(qpow(x, 3, MOD), addMOD(mulMOD(a, x, MOD), b, MOD), MOD);
            if(left == right) ans.pb({x, y});
        }
    }
    ans.pb(O);
}
void EllipticCurve::showAllPoints()
{
    getAllPoints();
    printf("椭圆曲线上一共有 %d 个点\n", (int)ans.size());
    for(auto i: ans) out(i);
    puts("");
}


int EllipticCurve::getTangentAtPoint(pii &P)
{
    return mulMOD(addMOD(mulMOD(3, qpow(P.fi, 2, MOD), MOD), a, MOD), getInv(mulMOD(2, P.se, MOD), MOD), MOD);
}


int EllipticCurve::getTangentOfP1P2(pii &P1, pii &P2)
{
    return mulMOD(subMOD(P2.se, P1.se, MOD), getInv(subMOD(P2.fi, P1.fi, MOD), MOD), MOD);
}


pii EllipticCurve::handleTangent(pii &P)
{
    if(P.se == 0) return O;
    int tangentAtP = getTangentAtPoint(P);
    int xr = subMOD(qpow(tangentAtP, 2, MOD), mulMOD(P.fi, 2, MOD), MOD);
    int yr = addMOD(P.se, mulMOD(tangentAtP, subMOD(xr, P.fi, MOD), MOD), MOD);
    return {xr, MOD - yr};
}


pii EllipticCurve::handleSecant(pii &P1, pii &P2)
{
    if(P1.fi == P2.fi) return O;
    int tangentOfP1P2 = getTangentOfP1P2(P1, P2);
    int xr = subMOD(qpow(tangentOfP1P2, 2, MOD), addMOD(P1.fi, P2.fi, MOD), MOD);
    int yr = addMOD(P1.se, mulMOD(tangentOfP1P2, subMOD(xr, P1.fi, MOD), MOD), MOD);
    return {xr, MOD - yr};
}


pii EllipticCurve::addP1P2(pii &P1, pii &P2)
{
    if(P1 == O || P2 == O) return P1 == O ? P2 : P1;
    else if(P1 == P2) return handleTangent(P1);
    else if(P1 != P2) return handleSecant(P1, P2);
}


pii EllipticCurve::getNP(pii &P, int n)
{
    pii nP = O;
    for(int i = 0; i < n; ++i) {
        nP = addP1P2(nP, P);
        //cout << nP.fi << ' ' << nP.se << endl;
    }
    return nP;
}


pii EllipticCurve::qGetNP(pii &P, int n)
{
    if(P == O) return O;
    pii ans = O;
    while(n) {
        if(n & 1) ans = addP1P2(ans, P);
        P = addP1P2(P, P), n >>= 1;
    }
    return ans;
}

int EllipticCurve::getOrder(pii &P)
{
    pii temp = P;
    int order = 0;
    while (1) {
        order++;
        temp = addP1P2(temp, P);
        if (temp == P) return order;
    }
}


void EllipticCurve::showEllipticCurver()
{
    puts("椭圆曲线解析式");
    cout << "y^2 = " << "x^3 + " << a << "x + " << b << " mod " << MOD << endl;
    puts("");
}

void genKey(publicKey &pbk, privateKey &prk, pii P, EllipticCurve &E)
{
    int order = E.getOrder(P);
    int s = rand() % (order - 2) + 2;
    pii Q = E.getNP(P, s);
    pbk = publicKey(P, Q, E);
    prk = privateKey(s);
}

cipherText encryption(publicKey &pbk, int m)
{
    int order = pbk.E.getOrder(pbk.P);
    int r = rand() % (order - 2) + 2;
    cnt = r;
    pii rP = pbk.E.getNP(pbk.P, r);
    pii rQ = pbk.E.getNP(pbk.Q, r);
    int c = mulMOD(m, rQ.fi, pbk.E.getMOD());
    cipherText ciphertext = cipherText(rP.fi, rP.se, c);
    return ciphertext;
}

int decryption(publicKey &pbk, privateKey &prk, cipherText &cipher)
{
    pii temp = {cipher.x, cipher.y};
    pii srP = pbk.E.getNP(temp, prk.s);
    int plain = mulMOD(cipher.c, getInv(srP.fi, pbk.E.getMOD()), pbk.E.getMOD());
    return plain;
}

