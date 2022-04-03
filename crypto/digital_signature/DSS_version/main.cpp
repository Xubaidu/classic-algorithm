#include<bits/stdc++.h>
#include "bigInt.h"
#include "md5.h"
#define int128 Bigint
using namespace std;

int main() {
    string message;
    printf("输入消息: ");
    cin >> message;
    Init(message);
    string digest = calcMD5();
    printf("消息的 md5 值: ");
    cout << digest << endl;
    puts("------------------------------------");
    puts("正在创建密钥.....");
    srand((unsigned) time(NULL));
    int128 q = Rand_BInteger(160);
    while (!CheckPrime(q)) {
        q = Rand_BInteger(160);
    }
    int128 tmp = 2, tmp1 = 257 - 160;
    int128 p1q = bin(tmp, tmp1);
    int128 p = q * p1q + 1;
    while (!CheckPrime(p)) {
        p1q = p1q + 1;
        p = q * p1q + 1;
    }
    int128 h = Rand_BInteger(180);
    int128 g = bin(h, p1q, p);
    int128 x = Rand_BInteger(120);
    int128 y = bin(g, x, p);
    puts("公钥: ");
    cout << "p = " << p << endl;
    cout << "q = " << q << endl;
    cout << "g = " << g << endl;
    cout << "y = " << y << endl;
    puts("------------------------------------");
    puts("私钥: ");
    cout << "x = " << x << endl;
    puts("------------------------------------");
    int128 Hash = 0;
    for (auto x:digest)
        Hash = Hash * 256 + x;
    Hash = Hash % q;
    int128 k = Rand_BInteger(120);
    int128 kn = bin(k, q - 2, q);
    int128 r = bin(g, k, p) % q;
    int128 s = (kn * (Hash + x * r % q)) % q;
    puts("签名: ");
    cout << "m = " << message << endl;
    cout << "Hash = " << Hash << endl;
    cout << "r = " << r << endl;
    cout << "s = " << s << endl;

    puts("------------------------------------");

    int128 w = bin(s, q - 2, q);
    int128 u1 = Hash * w % q;
    int128 u2 = r * w % q;
    int128 v = bin(g, u1, p) * bin(y, u2, p) % p % q;
    puts("验证: ");
    cout << "v = " << v << endl;
    cout << "r = " << r << endl;
    puts("正确");
    return 0;
}