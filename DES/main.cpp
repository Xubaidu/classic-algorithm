#include <bits/stdc++.h>

using namespace std;

// 初始置换表，置换 64 位明文
int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9, 1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7};

// 密钥置换表，将 64 位密钥变成 56 位
int PC_1[] = {57, 49, 41, 33, 25, 17, 9,
              1, 58, 50, 42, 34, 26, 18,
              10, 2, 59, 51, 43, 35, 27,
              19, 11, 3, 60, 52, 44, 36,
              63, 55, 47, 39, 31, 23, 15,
              7, 62, 54, 46, 38, 30, 22,
              14, 6, 61, 53, 45, 37, 29,
              21, 13, 5, 28, 20, 12, 4};

// 压缩置换，将 56 位密钥压缩成 48 位子密钥
int PC_2[] = {14, 17, 11, 24, 1, 5,
              3, 28, 15, 6, 21, 10,
              23, 19, 12, 4, 26, 8,
              16, 7, 27, 20, 13, 2,
              41, 52, 31, 37, 47, 55,
              30, 40, 51, 45, 33, 48,
              44, 49, 39, 56, 34, 53,
              46, 42, 50, 36, 29, 32};

// 每轮左移的位数
int shiftBits[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// 扩展置换表，将 bitset<32> 扩展至 bitset<48>
int E[] = {32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1};


// S盒，每个S盒是4x16的置换表，6位 -> 4位
int S_BOX[8][4][16] = {
        {
                {14, 4,  13, 1,  2,  15, 11, 8,  3,  10, 6,  12, 5,  9,  0,  7},
                {0,  15, 7,  4,  14, 2,  13, 1,  10, 6, 12, 11, 9,  5,  3,  8},
                {4,  1,  14, 8,  13, 6,  2,  11, 15, 12, 9,  7,  3,  10, 5,  0},
                {15, 12, 8,  2,  4,  9,  1,  7,  5,  11, 3,  14, 10, 0, 6,  13}
        },
        {
                {15, 1,  8,  14, 6,  11, 3,  4,  9,  7,  2,  13, 12, 0,  5,  10},
                {3,  13, 4,  7,  15, 2,  8,  14, 12, 0, 1,  10, 6,  9,  11, 5},
                {0,  14, 7,  11, 10, 4,  13, 1,  5,  8,  12, 6,  9,  3,  2,  15},
                {13, 8,  10, 1,  3,  15, 4,  2,  11, 6,  7,  12, 0,  5, 14, 9}
        },
        {
                {10, 0,  9,  14, 6,  3,  15, 5,  1,  13, 12, 7,  11, 4,  2,  8},
                {13, 7,  0,  9,  3,  4,  6,  10, 2,  8, 5,  14, 12, 11, 15, 1},
                {13, 6,  4,  9,  8,  15, 3,  0,  11, 1,  2,  12, 5,  10, 14, 7},
                {1,  10, 13, 0,  6,  9,  8,  7,  4,  15, 14, 3,  11, 5, 2,  12}
        },
        {
                {7,  13, 14, 3,  0,  6,  9,  10, 1,  2,  8,  5,  11, 12, 4,  15},
                {13, 8,  11, 5,  6,  15, 0,  3,  4,  7, 2,  12, 1,  10, 14, 9},
                {10, 6,  9,  0,  12, 11, 7,  13, 15, 1,  3,  14, 5,  2,  8,  4},
                {3,  15, 0,  6,  10, 1,  13, 8,  9,  4,  5,  11, 12, 7, 2,  14}
        },
        {
                {2,  12, 4,  1,  7,  10, 11, 6,  8,  5,  3,  15, 13, 0,  14, 9},
                {14, 11, 2,  12, 4,  7,  13, 1,  5,  0, 15, 10, 3,  9,  8,  6},
                {4,  2,  1,  11, 10, 13, 7,  8,  15, 9,  12, 5,  6,  3,  0,  14},
                {11, 8,  12, 7,  1,  14, 2,  13, 6,  15, 0,  9,  10, 4, 5,  3}
        },
        {
                {12, 1,  10, 15, 9,  2,  6,  8,  0,  13, 3,  4,  14, 7,  5,  11},
                {10, 15, 4,  2,  7,  12, 9,  5,  6,  1, 13, 14, 0,  11, 3,  8},
                {9,  14, 15, 5,  2,  8,  12, 3,  7,  0,  4,  10, 1,  13, 11, 6},
                {4,  3,  2,  12, 9,  5,  15, 10, 11, 14, 1,  7,  6,  0, 8,  13}
        },
        {
                {4,  11, 2,  14, 15, 0,  8,  13, 3,  12, 9,  7,  5,  10, 6,  1},
                {13, 0,  11, 7,  4,  9,  1,  10, 14, 3, 5,  12, 2,  15, 8,  6},
                {1,  4,  11, 13, 12, 3,  7,  14, 10, 15, 6,  8,  0,  5,  9,  2},
                {6,  11, 13, 8,  1,  4,  10, 7,  9,  5,  0,  15, 14, 2, 3,  12}
        },
        {
                {13, 2,  8,  4,  6,  15, 11, 1,  10, 9,  3,  14, 5,  0,  12, 7},
                {1,  15, 13, 8,  10, 3,  7,  4,  12, 5, 6,  11, 0,  14, 9,  2},
                {7,  11, 4,  1,  9,  12, 14, 2,  0,  6,  10, 13, 15, 3,  5,  8},
                {2,  1,  14, 7,  4,  10, 8,  13, 15, 12, 9,  0,  3,  5, 6,  11}
        }
};

// P置换，32位 -> 32位
int P[] = {16, 7, 20, 21,
           29, 12, 28, 17,
           1, 15, 23, 26,
           5, 18, 31, 10,
           2, 8, 24, 14,
           32, 27, 3, 9,
           19, 13, 30, 6,
           22, 11, 4, 25};

// 尾置换表
int IP_inverse[] = {40, 8, 48, 16, 56, 24, 64, 32,
                    39, 7, 47, 15, 55, 23, 63, 31,
                    38, 6, 46, 14, 54, 22, 62, 30,
                    37, 5, 45, 13, 53, 21, 61, 29,
                    36, 4, 44, 12, 52, 20, 60, 28,
                    35, 3, 43, 11, 51, 19, 59, 27,
                    34, 2, 42, 10, 50, 18, 58, 26,
                    33, 1, 41, 9, 49, 17, 57, 25};

/* 重载 bitset<28> 的加法运算符 */
bitset<56> operator+(const bitset<28> &bt1, const bitset<28> &bt2)
{
    string s1 = bt1.to_string(), s2 = bt2.to_string();
    s1 += s2;
    return bitset<56>(s1);
}

/* 重载 bitset<32> 的加法运算符 */
bitset<64> operator+(const bitset<32> &bt1, const bitset<32> &bt2)
{
    string s1 = bt1.to_string(), s2 = bt2.to_string();
    s1 += s2;
    return bitset<64>(s1);
}

/* 鉴于 bitset 实际下标从低位（从右往左）算起，因此对逻辑下标（从左往右）做一个转换，下标从零开始计数 */
/* input: bitset 的长度 n，逻辑下标 pos */
/* output: 实际下标 */
int TransIndex(int n, int pos)
{
    return n - pos - 1;
}

/* 利用 IP 对输入的 bitset<64> input 进行初始置换 */
/* input: 初始明文 input */
/* output: 置换后的两个 bitset<32> 明文组成的 vector */
vector<bitset<32>> InitialPermutation(const bitset<64> &input)
{
    string str = "";
    for (int i = 0; i < 64; ++i)
        str += input[TransIndex(64, IP[i] - 1)] + '0';
    string substr1 = str.substr(0, 32);
    string substr2 = str.substr(32, 32);
    vector<bitset<32>> ret;
    ret.emplace_back(bitset<32>(substr1));
    ret.emplace_back(bitset<32>(substr2));
    return ret;
}

/* 利用 PC_1 对输入的 bitset<64> key 进行密钥置换 */
/* input: 密钥 key */
/* output: 置换压缩后的 key */
bitset<56> KeyPermutation(const bitset<64> &key)
{
    string str = "";
    for (int i = 0; i < 56; ++i)
        str += key[TransIndex(64, PC_1[i] - 1)] + '0';
    return bitset<56>(str);
}

/* 对 bitset<28> 的密钥进行循环左移 */
/* input: bitset<28> key, 左移轮数 round */
/* output: 左移后的 bitset<28> */
bitset<28> LeftShift(const bitset<28> &key, int round)
{
    int shift = shiftBits[round];
    return ((key << shift) | (key >> (28 - shift)));
}

/* 先将输入的 bitset<28> key1, key2 进行拼接，再利用 PC_2 对输入的 bitset<56> 进行密钥压缩 */
/* key1, key2 可修改 */
/* input: 两个子密钥 bitset<28> key1, key2，左移轮数 round */
/* output: 合成压缩后的长度为 48 的密钥 */
bitset<48> GetSubKey(bitset<28> &key1, bitset<28> &key2, int round)
{
    key1 = LeftShift(key1, round);
    key2 = LeftShift(key2, round);
    bitset<56> key = key1 + key2;
    string str = "";
    for (int i = 0; i < 48; ++i)
        str += key[TransIndex(56, PC_2[i] - 1)] + '0';
    return bitset<48>(str);
}

/* 生成 16 轮密钥 */
/* 每一轮的 subKey1, subKey2 都由上一轮修改给出 */
/* input: 用来存储 16 轮密钥的 vector，初始密钥 bitset<64> key */
/* output: none */
void GenKey(vector<bitset<48>> &K, const bitset<64> &key)
{
    /* 对密钥进行置换 */
    bitset<56> handledKey = KeyPermutation(key);
    bitset<28> subKey1(handledKey.to_string().substr(0, 28));
    bitset<28> subKey2(handledKey.to_string().substr(28, 28));
    /* 生成每一轮的密钥 */
    for (int i = 1; i <= 16; ++i) {
        bitset<48> subKey = GetSubKey(subKey1, subKey2, i - 1);
        K[i] = subKey;
    }
}

/* 用每一轮的密钥加密每一轮的输入 */
/* input: 每一轮的输入明文 input, 每一轮的密钥 key */
/* output: 每一轮的密文 */
bitset<32> func(const bitset<32> &input, const bitset<48> &key)
{
    /* 生成 bitset<48> 扩展明文 */
    string str = "";
    for (int i = 0; i < 48; ++i) str += input[TransIndex(32, E[i] - 1)] + '0';
    bitset<48> expandedInput(str);

    /* 生成异或值 */
    bitset<48> xorRes = expandedInput ^key;

    /* 将异或值分成 8 组 bitset<6> */
    vector<bitset<6>> xorResGroup(8);
    string temp = "";
    for (int i = 47; i >= 0; --i) {
        temp += xorRes[i] + '0';
        if (i % 6 == 0) {
            xorResGroup[i / 6] = bitset<6>(temp);
            temp = "";
        }
    }
    reverse(xorResGroup.begin(), xorResGroup.end());

    /* 根据 bitset<6> 查询 S 盒，转化为 8 组 bitset<4> */
    vector<bitset<4>> retGroup(8);
    for (int i = 0; i < 8; ++i) {
        bitset<6> xorResGroupMember = xorResGroup[i];
        int x = 0, y = 0;
        for (int j = 5; j >= 0; --j) { // 根据秦九韶算法从高位往第位计算
            if (j == 0 || j == 5) x *= 2, x += xorResGroupMember[j];
            else y *= 2, y += xorResGroupMember[j];
        }
        int target_val = S_BOX[i][x][y];
        bitset<4> retGroupMember(target_val);
        retGroup[i] = retGroupMember;
    }

    /* 将 8 组 bitset<4> 组成 bitset<32> */
    str = "";
    for (int i = 0; i < 8; ++i) {
        str += retGroup[i].to_string();
    }
    string str2 = "";

    /* 对输出的 bitset<32> 进行 P 置换 */
    for (int i = 0; i < 32; ++i)
        str2 += str[P[i] - 1];
    return bitset<32>(str2);
}

/* 将 bitset<32> L, R 合并后逆置换输出 */
/* input: bitset<32> L, R */
/* output: 合并并且逆置换后的 bitset<64> 结果*/
bitset<64> InversePermutation(bitset<32> &L, bitset<32> &R)
{
    bitset<64> res = L + R;
    string str = "";
    for (int i = 0; i < 64; ++i)
        str += res[TransIndex(64, IP_inverse[i] - 1)] + '0';
    return bitset<64>(str);
}

/* 加密 */
/* input: 明文 message，密钥 key*/
/* output: 密文 */
bitset<64> Encrypt(const bitset<64> &message, const vector<bitset<48>> &K)
{
    /* 置换明文 */
    vector<bitset<32>> handledMessage = InitialPermutation(message);

    /* 生成 16 轮 L, R */
    vector<bitset<32>> L(17);
    vector<bitset<32>> R(17);
    L[0] = handledMessage[0];
    R[0] = handledMessage[1];
    for (int i = 1; i <= 16; ++i) {
        L[i] = R[i - 1];
        R[i] = L[i - 1] ^ func(R[i - 1], K[i]);
    }

    /* 逆置换明文 */
    bitset<64> ret = InversePermutation(R[16], L[16]);
    return ret;
}

/* 解密 */
/* input: 密文 message，密钥 key*/
/* output: 明文 */
bitset<64> Decrypt(const bitset<64> &secret, const vector<bitset<48>> &K)
{
    /* 置换明文 */
    vector<bitset<32>> handledMessage = InitialPermutation(secret);

    /* 生成 16 轮 L, R */
    vector<bitset<32>> L(17);
    vector<bitset<32>> R(17);
    L[0] = handledMessage[0];
    R[0] = handledMessage[1];
    for (int i = 1; i <= 16; ++i) {
        L[i] = R[i - 1];
        R[i] = L[i - 1] ^ func(R[i - 1], K[17 - i]);
    }

    /* 逆置换明文 */
    bitset<64> ret = InversePermutation(R[16], L[16]);
    return ret;
}

/* 二进制转十六进制 */
/* input: 二进制串 */
/* output: 十六进制串 */
string Bin2Hex(string Bin)
{
    string Hex = "0x";
    int temp = Bin[0] - '0';
    for (int i = 1; i <= Bin.length(); ++i) {
        if (i % 4 == 0) {
            Hex += temp >= 10 ? temp - 10 + 'a' : temp + '0';
            temp = 0;
        }
        if (i < Bin.length()) temp *= 2, temp += Bin[i] - '0';
    }
    return Hex;
}


int main()
{
    bitset<64> m("0111001001101111011011010110000101101110011101000110100101100011");
    bitset<64> k("0001001100110100010101110111100110011011101111001101111111110001");

    /* 生成 16 轮 key */
    vector<bitset<48>> K(17);
    GenKey(K, k);

    cout << "input:               " << Bin2Hex(m.to_string()) << endl;
    cout << "key:                 " << Bin2Hex(k.to_string()) << endl;

    bitset<64> secret = Encrypt(m, K);
    bitset<64> plaintext = Decrypt(secret, K);
    cout << "secret:              " << Bin2Hex(secret.to_string()) << endl;
    cout << "Decrypted plaintext: " << Bin2Hex(plaintext.to_string()) << endl;

    return 0;
}
