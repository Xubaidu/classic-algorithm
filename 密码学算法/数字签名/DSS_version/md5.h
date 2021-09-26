#include <bits/stdc++.h>
using namespace std;

#define F(x, y, z)(((x)&(y))|((~x)&(z)))
#define G(x, y, z)(((x)&(z))|((y)&(~z)))
#define H(x, y, z)((x)^(y)^(z))
#define I(x, y, z)((y)^((x)|(~z)))
#define ROTATELEFT(num, n)(((num)<<(n))|((num)>>(32-(n))))
#define FF(a, b, c, d, x, s, ac) { \
 (a)+=F((b),(c),(d))+(x)+ac;\
 (a)=ROTATELEFT((a),(s));\
 (a)+=(b);\
}
#define GG(a, b, c, d, x, s, ac) { \
 (a)+=G((b),(c),(d))+(x)+ac;\
 (a)=ROTATELEFT((a),(s));\
 (a)+=(b);\
}
#define HH(a, b, c, d, x, s, ac) { \
 (a)+=H((b),(c),(d))+(x)+ac;\
 (a)=ROTATELEFT((a),(s));\
 (a)+=(b);\
}
#define II(a, b, c, d, x, s, ac) { \
 (a)+=I((b),(c),(d))+(x)+ac;\
 (a)=ROTATELEFT((a),(s));\
 (a)+=(b);\
}

bool finished;
unsigned int state[4], num[2];
unsigned char buffer[64], digest[16];
const unsigned char PADDING[64] = {0x80};
const char HEX_NUMBERS[16] =
        {
                '0', '1', '2', '3',
                '4', '5', '6', '7',
                '8', '9', 'a', 'b',
                'c', 'd', 'e', 'f'
        };

void encode(const unsigned int *input, unsigned char *output, size_t length) {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[j] = (unsigned char) (input[i] & 0xff);
        output[j + 1] = (unsigned char) ((input[i] >> 8) & 0xff);
        output[j + 2] = (unsigned char) ((input[i] >> 16) & 0xff);
        output[j + 3] = (unsigned char) ((input[i] >> 24) & 0xff);
    }
}

void decode(const unsigned char *input, unsigned int *output, size_t length) {
    for (size_t i = 0, j = 0; j < length; ++i, j += 4) {
        output[i] = ((unsigned int) input[j]) | (((unsigned int) input[j + 1]) << 8)
                    | (((unsigned int) input[j + 2]) << 16) | (((unsigned int) input[j + 3]) << 24);
    }
}

void transform(const unsigned char block[64]) {
    unsigned int a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode(block, x, 64);
    FF(a, b, c, d, x[0], 7, 0xd76aa478);
    FF(d, a, b, c, x[1], 12, 0xe8c7b756);
    FF(c, d, a, b, x[2], 17, 0x242070db);
    FF(b, c, d, a, x[3], 22, 0xc1bdceee);
    FF(a, b, c, d, x[4], 7, 0xf57c0faf);
    FF(d, a, b, c, x[5], 12, 0x4787c62a);
    FF(c, d, a, b, x[6], 17, 0xa8304613);
    FF(b, c, d, a, x[7], 22, 0xfd469501);
    FF(a, b, c, d, x[8], 7, 0x698098d8);
    FF(d, a, b, c, x[9], 12, 0x8b44f7af);
    FF(c, d, a, b, x[10], 17, 0xffff5bb1);
    FF(b, c, d, a, x[11], 22, 0x895cd7be);
    FF(a, b, c, d, x[12], 7, 0x6b901122);
    FF(d, a, b, c, x[13], 12, 0xfd987193);
    FF(c, d, a, b, x[14], 17, 0xa679438e);
    FF(b, c, d, a, x[15], 22, 0x49b40821);

    GG(a, b, c, d, x[1], 5, 0xf61e2562);
    GG(d, a, b, c, x[6], 9, 0xc040b340);
    GG(c, d, a, b, x[11], 14, 0x265e5a51);
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa);
    GG(a, b, c, d, x[5], 5, 0xd62f105d);
    GG(d, a, b, c, x[10], 9, 0x2441453);
    GG(c, d, a, b, x[15], 14, 0xd8a1e681);
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8);
    GG(a, b, c, d, x[9], 5, 0x21e1cde6);
    GG(d, a, b, c, x[14], 9, 0xc33707d6);
    GG(c, d, a, b, x[3], 14, 0xf4d50d87);
    GG(b, c, d, a, x[8], 20, 0x455a14ed);
    GG(a, b, c, d, x[13], 5, 0xa9e3e905);
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8);
    GG(c, d, a, b, x[7], 14, 0x676f02d9);
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a);

    HH(a, b, c, d, x[5], 4, 0xfffa3942);
    HH(d, a, b, c, x[8], 11, 0x8771f681);
    HH(c, d, a, b, x[11], 16, 0x6d9d6122);
    HH(b, c, d, a, x[14], 23, 0xfde5380c);
    HH(a, b, c, d, x[1], 4, 0xa4beea44);
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9);
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60);
    HH(b, c, d, a, x[10], 23, 0xbebfbc70);
    HH(a, b, c, d, x[13], 4, 0x289b7ec6);
    HH(d, a, b, c, x[0], 11, 0xeaa127fa);
    HH(c, d, a, b, x[3], 16, 0xd4ef3085);
    HH(b, c, d, a, x[6], 23, 0x4881d05);
    HH(a, b, c, d, x[9], 4, 0xd9d4d039);
    HH(d, a, b, c, x[12], 11, 0xe6db99e5);
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8);
    HH(b, c, d, a, x[2], 23, 0xc4ac5665);

    II(a, b, c, d, x[0], 6, 0xf4292244);
    II(d, a, b, c, x[7], 10, 0x432aff97);
    II(c, d, a, b, x[14], 15, 0xab9423a7);
    II(b, c, d, a, x[5], 21, 0xfc93a039);
    II(a, b, c, d, x[12], 6, 0x655b59c3);
    II(d, a, b, c, x[3], 10, 0x8f0ccc92);
    II(c, d, a, b, x[10], 15, 0xffeff47d);
    II(b, c, d, a, x[1], 21, 0x85845dd1);
    II(a, b, c, d, x[8], 6, 0x6fa87e4f);
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0);
    II(c, d, a, b, x[6], 15, 0xa3014314);
    II(b, c, d, a, x[13], 21, 0x4e0811a1);
    II(a, b, c, d, x[4], 6, 0xf7537e82);
    II(d, a, b, c, x[11], 10, 0xbd3af235);
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb);
    II(b, c, d, a, x[9], 21, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void init(const unsigned char *input, size_t len) {
    unsigned int i, index, partLen;
    finished = false;
    index = (unsigned int) ((num[0] >> 3) & 0x3f);
    if ((num[0] += ((unsigned int) len << 3)) < ((unsigned int) len << 3)) {
        ++num[1];
    }
    num[1] += ((unsigned int) len >> 29);
    partLen = 64 - index;
    if (len >= partLen) {
        memcpy(&buffer[index], input, partLen);
        transform(buffer);
        for (i = partLen; i + 63 < len; i += 64)
            transform(&input[i]);
        index = 0;
    } else i = 0;
    memcpy(&buffer[index], &input[i], len - i);
}

void Init(const string &message) {
    finished = false;
    num[0] = 0;
    num[1] = 0;
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
    init((const unsigned char *) message.c_str(), message.length());
}

const unsigned char *getDigest() {
    if (!finished) {
        finished = true;
        unsigned char bits[8];
        unsigned int oldState[4];
        unsigned int oldnum[2];
        unsigned int index, padLen;
        memcpy(oldState, state, 16);
        memcpy(oldnum, num, 8);
        encode(num, bits, 8);
        index = (unsigned int) ((num[0] >> 3) & 0x3f);
        padLen = (index < 56) ? (56 - index) : (120 - index);
        init(PADDING, padLen);
        init(bits, 8);
        encode(state, digest, 16);
        memcpy(state, oldState, 16);
        memcpy(num, oldnum, 8);
    }
    return digest;
}

string calcMD5() {
    const unsigned char *digest_ = getDigest();
    string str;
    str.reserve(16 << 1);
    for (size_t i = 0; i < 16; ++i) {
        int t = digest_[i];
        int a = t / 16;
        int b = t % 16;
        str.append(1, HEX_NUMBERS[a]);
        str.append(1, HEX_NUMBERS[b]);
    }
    return str;
}