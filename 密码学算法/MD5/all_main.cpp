#include <bits/stdc++.h>
#define word unsigned int
using namespace std;

class MD5
{
private:
    string bit;
    int group;
    word num[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
    word M[16];
    int S[4][4] = {
        {7, 12, 17, 22},
        {5, 9,  14, 20},
        {4, 11, 16, 23},
        {6, 10, 15, 21}};
    const word T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

public:
    MD5();
    MD5(string &_input);
    string calc();
    word shift(word x, unsigned int k);
    word F(word X, word Y, word Z);
    word G(word X, word Y, word Z);
    word H(word X, word Y, word Z);
    word I(word X, word Y, word Z);
    void FF(word &a, word b, word c, word d, word M, int s, word t);
    void GG(word &a, word b, word c, word d, word M, int s, word t);
    void HH(word &a, word b, word c, word d, word M, int s, word t);
    void II(word &a, word b, word c, word d, word M, int s, word t);
    void mainloop(word M[]);
    string preProcessInput(string s);
    string getMD5();
    string transEndian(bitset<32> w);
    string Bin2Hex(string Bin);
};

int main()
{
    /*
    vector<string> test = {
        "",
        "a",
        "abc",
        "message digest",
        "abcdefghijklmnopqrstuvwxyz",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    vector<string> ans = {
        "0xd41d8cd98f00b204e9800998ecf8427e",
        "0x0cc175b9c0f1b6a831c399e269772661",
        "0x900150983cd24fb0d6963f7d28e17f72",
        "0xf96b697d7cb7938d525a2f31aaf161d0",
        "0xc3fcd3d76192e4007dfb496cca67e13b",
        "0xd174ab98d277d9f5a5611c2c9f419d9f",
        };
    for (int i = 0; i < test.size(); ++i) {
        MD5 md5(test[i]);
        string my_ans = md5.calc();
        puts((my_ans == ans[i]) ? "Accepted" : "Wrong Answer");
    }
    */
   string s;
   puts("input the string to be hashed");
   cin >> s;
   puts("the hashed string");
   cout << MD5(s).calc() << endl;
    return 0;
}

MD5::MD5() {}

MD5::MD5(string &_input)
{
    bit = preProcessInput(_input);
    group = bit.length() / 512;
}

string MD5::calc()
{
    word M[16];
    for (int i = 0; i < group; ++i) {
        string sub_bit = bit.substr(i * 512, 512);
        for (int j = 0; j < 16; ++j) {
            string temp = transEndian(bitset<32>(sub_bit.substr(j * 32, i + 32)));
            M[j] = bitset<32>(temp).to_ulong();
            //printf("%d %d\n", j, M[j]);
        }
        mainloop(M);
        //printf("%u\n%u\n%u\n%u\n\n", num[0], num[1], num[2], num[3]);
    }

    return getMD5();
}

word MD5::shift(word x, unsigned int k)
{
    return (x << k) | (x >> (32 - k));
}

word MD5::F(word X, word Y, word Z)
{
    return (X & Y) | ((~X) & Z);
}

word MD5::G(word X, word Y, word Z)
{
    return (X & Z) | ((~Z) & Y);
}

word MD5::H(word X, word Y, word Z)
{
    return X ^ Y ^ Z;
}

word MD5::I(word X, word Y, word Z)
{
    return Y ^ (X | (~Z));
}

void MD5::FF(word &a, word b, word c, word d, word M, int s, word t)
{
    a = b + shift((a + F(b, c, d) + M + t), s);
}

void MD5::GG(word &a, word b, word c, word d, word M, int s, word t)
{
    a = b + shift((a + G(b, c, d) + M + t), s);
}

void MD5::HH(word &a, word b, word c, word d, word M, int s, word t)
{
    a = b + shift((a + H(b, c, d) + M + t), s);
}

void MD5::II(word &a, word b, word c, word d, word M, int s, word t)
{
    a = b + shift((a + I(b, c, d) + M + t), s);
}

string MD5::transEndian(bitset<32> w)
{
    string w_str = w.to_string();
    string ans;
    for (int i = 3; i >= 0; --i) {
        ans += w_str.substr(i * 8, 8);
    }
    return ans;
}

void MD5::mainloop(word M[])
{
    // register
    word a = num[0], b = num[1], c = num[2], d = num[3];
    
    FF(a, b, c, d, M[0], 7, 0xd76aa478);
    FF(d, a, b, c, M[1], 12, 0xe8c7b756);
    FF(c, d, a, b, M[2], 17, 0x242070db);
    FF(b, c, d, a, M[3], 22, 0xc1bdceee);
    FF(a, b, c, d, M[4], 7, 0xf57c0faf);
    FF(d, a, b, c, M[5], 12, 0x4787c62a);
    FF(c, d, a, b, M[6], 17, 0xa8304613);
    FF(b, c, d, a, M[7], 22, 0xfd469501);
    FF(a, b, c, d, M[8], 7, 0x698098d8);
    FF(d, a, b, c, M[9], 12, 0x8b44f7af);
    FF(c, d, a, b, M[10], 17, 0xffff5bb1);
    FF(b, c, d, a, M[11], 22, 0x895cd7be);
    FF(a, b, c, d, M[12], 7, 0x6b901122);
    FF(d, a, b, c, M[13], 12, 0xfd987193);
    FF(c, d, a, b, M[14], 17, 0xa679438e);
    FF(b, c, d, a, M[15], 22, 0x49b40821);

    GG(a, b, c, d, M[1], 5, 0xf61e2562);
    GG(d, a, b, c, M[6], 9, 0xc040b340);
    GG(c, d, a, b, M[11], 14, 0x265e5a51);
    GG(b, c, d, a, M[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, M[5], 5, 0xd62f105d);
    GG(d, a, b, c, M[10], 9, 0x02441453);
    GG(c, d, a, b, M[15], 14, 0xd8a1e681);
    GG(b, c, d, a, M[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, M[9], 5, 0x21e1cde6);
    GG(d, a, b, c, M[14], 9, 0xc33707d6);
    GG(c, d, a, b, M[3], 14, 0xf4d50d87);
    GG(b, c, d, a, M[8], 20, 0x455a14ed);
    GG(a, b, c, d, M[13], 5, 0xa9e3e905);
    GG(d, a, b, c, M[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, M[7], 14, 0x676f02d9);
    GG(b, c, d, a, M[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, M[5], 4, 0xfffa3942);
    HH(d, a, b, c, M[8], 11, 0x8771f681);
    HH(c, d, a, b, M[11], 16, 0x6d9d6122);
    HH(b, c, d, a, M[14], 23, 0xfde5380c);
    HH(a, b, c, d, M[1], 4, 0xa4beea44);
    HH(d, a, b, c, M[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, M[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, M[10], 23, 0xbebfbc70);
    HH(a, b, c, d, M[13], 4, 0x289b7ec6);
    HH(d, a, b, c, M[0], 11, 0xeaa127fa);
    HH(c, d, a, b, M[3], 16, 0xd4ef3085);
    HH(b, c, d, a, M[6], 23, 0x04881d05);
    HH(a, b, c, d, M[9], 4, 0xd9d4d039);
    HH(d, a, b, c, M[12], 11, 0xe6db99e5);
    HH(c, d, a, b, M[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, M[2], 23, 0xc4ac5665);

    II(a, b, c, d, M[0], 6, 0xf4292244);
    II(d, a, b, c, M[7], 10, 0x432aff97);
    II(c, d, a, b, M[14], 15, 0xab9423a7);
    II(b, c, d, a, M[5], 21, 0xfc93a039);
    II(a, b, c, d, M[12], 6, 0x655b59c3);
    II(d, a, b, c, M[3], 10, 0x8f0ccc92);
    II(c, d, a, b, M[10], 15, 0xffeff47d);
    II(b, c, d, a, M[1], 21, 0x85845dd1);
    II(a, b, c, d, M[8], 6, 0x6fa87e4f);
    II(d, a, b, c, M[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, M[6], 15, 0xa3014314);
    II(b, c, d, a, M[13], 21, 0x4e0811a1);
    II(a, b, c, d, M[4], 6, 0xf7537e82);
    II(d, a, b, c, M[11], 10, 0xbd3af235);
    II(c, d, a, b, M[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, M[9], 21, 0xeb86d391);
    
    num[0] += a, num[1] += b, num[2] += c, num[3] += d;
    //printf("%u\n%u\n%u\n%u\n\n", num[0], num[1], num[2], num[3]);
}

string MD5::preProcessInput(string s)
{
    string bit;
    for (auto &i: s) bit += bitset<8>(i).to_string();
    int L = bit.length();
    if (L % 512 < 448) {
        bit += '1';
        bit += string(448 - 1 - L, '0');
    }
    else {
        bit += '1';
        bit += string(512 - 1 - (L - 448), '0');
    }

    // 获取长度，用小端法存储
    string tail = bitset<64>(L).to_string();
    string tail1 = transEndian(bitset<32>(tail.substr(0, 32)));
    string tail2 = transEndian(bitset<32>(tail.substr(32, 32)));
    bit += tail2, bit += tail1;

    /*
    for (int i = 0; i <= 64; ++i) {
        if (i && i % 8 == 0) cout << endl;
        if (i < 64) cout << bit.substr(i * 8, 8) << ' ';
    }
    */

    return bit;
}

string MD5::getMD5()
{
    string ans;
    for (int i = 0; i < 4; ++i)
        ans += transEndian(bitset<32>(num[i])); // get the small endian and output it
    return Bin2Hex(ans);
}

string MD5::Bin2Hex(string Bin)
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
