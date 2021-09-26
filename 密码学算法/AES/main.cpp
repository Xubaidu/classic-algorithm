/*
 * @author: Xu Chenyang
 * @date: 2021.4.20
 * @email: 1127862434@qq.com
 * @institute: ECNU
 */

#include <bits/stdc++.h>
using namespace std;

const static uint8_t s_box[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},  // 0
	{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},  // 1
	{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},  // 2
	{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},  // 3
	{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},  // 4
	{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},  // 5
	{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},  // 6
	{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},  // 7
	{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},  // 8
	{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},  // 9
	{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},  // a
	{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},  // b
	{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},  // c
	{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},  // d
	{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},  // e
	{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}}; // f

const static uint8_t inv_s_box[16][16] = {
	// 0     1     2     3     4     5     6     7     8     9     a     b     c     d     e     f
	{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},  // 0
	{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},  // 1
	{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},  // 2
	{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},  // 3
	{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},  // 4
	{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},  // 5
	{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},  // 6
	{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},  // 7
	{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},  // 8
	{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},  // 9
	{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},  // a
	{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},  // b
	{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},  // c
	{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},  // d
	{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},  // e
	{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}}; // f

const static uint8_t mix_array[4][4] = {
    {0x02, 0x03, 0x01, 0x01},
    {0x01, 0x02, 0x03, 0x01},
    {0x01, 0x01, 0x02, 0x03},
    {0x03, 0x01, 0x01, 0x02}};

const static uint8_t inv_mix_array[4][4] = {
    {0x0e, 0x0b, 0x0d, 0x09},
    {0x09, 0x0e, 0x0b, 0x0d},
    {0x0d, 0x09, 0x0e, 0x0b},
    {0x0b, 0x0d, 0x09, 0x0e}};

const static uint8_t Rcon[11][4] = {
    {0x00, 0x00, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0x00},
    {0x02, 0x00, 0x00, 0x00},
    {0x04, 0x00, 0x00, 0x00},
    {0x08, 0x00, 0x00, 0x00},
    {0x10, 0x00, 0x00, 0x00},
    {0x20, 0x00, 0x00, 0x00},
    {0x40, 0x00, 0x00, 0x00},
    {0x80, 0x00, 0x00, 0x00},
    {0x1b, 0x00, 0x00, 0x00},
    {0x36, 0x00, 0x00, 0x00}};

/* convert 4 bytes(8-bit) into a word(32-bit)
 * input: a byte(8-bit) array of length 4
 * output: a word(32-bit)
*/
uint32_t uint8_to_uint32(uint8_t *u)
{
    uint32_t ans = u[0];
    for (int i = 1; i < 4; ++i)
        ans <<= 8, ans |= u[i];
    return ans;
}

/* convert a word(32-bit) into a byte(32-bit) array of length 4
 * input: a word(32-bit)
 * output: a byte(8-bit) array of length 4
*/
uint8_t *uint32_to_uint8(uint32_t x)
{
    uint8_t *ans = (uint8_t *)malloc(sizeof(char) * 4);
    ans[0] = (x >> 24);
    ans[1] = ((x << 8) >> 24);
    ans[2] = ((x << 16) >> 24);
    ans[3] = ((x << 24) >> 24);
    return ans;
}

void debug(uint8_t out[][4])
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            printf("0x%02x%c", out[i][j], " \n"[j == 3]);
    puts("-----");
}

void assign_b_to_a(uint8_t a[][4], uint8_t b[][4])
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            a[i][j] = b[i][j];
}

/* add the state matrix with key of the current round
 * input: state matrix(4 × 4), expanded key w[44], and the round number round
 * output: a new state matrix(4 × 4)
 * {state[0][0], state[1][0], state[2][0], state[3][0]} ^ w[4 * round + 0]
 * {state[0][1], state[1][1], state[2][1], state[3][1]} ^ w[4 * round + 1]
 * {state[0][2], state[1][2], state[2][2], state[3][2]} ^ w[4 * round + 2]
 * {state[0][3], state[1][3], state[2][3], state[3][3]} ^ w[4 * round + 3]
*/
void add_round_key(uint8_t state[][4], uint32_t w[44], int round)
{
    for (int i = 0; i < 4; ++i) {
        uint8_t *u = (uint8_t *)malloc(sizeof(uint8_t) * 4);
        for (int j = 0; j < 4; ++j)
            u[j] = state[j][i];
        uint32_t new_u = uint8_to_uint32(u);
        new_u ^= w[4 * round + i];
        u = uint32_to_uint8(new_u);
        for (int j = 0; j < 4; ++j)
            state[j][i] = u[j];
    }
}

/* left shift a word by a byte(8-bit)
 * input: a byte array of length 4
 * output: the array after rotation
*/
void rot_word(uint8_t *input)
{
    uint8_t temp = input[0];
    for (int i = 0; i < 3; ++i)
        input[i] = input[(i + 1) % 4];
    input[3] = temp;
}

/*
 * replace input_byte with s_box
 * input: input_byte = a7a6a5a4a3a2a1a0
 * output: s_box[a7a6a5a4][a3a2a1a0]
*/
void sub_byte(uint8_t &input_byte)
{
    input_byte = s_box[input_byte >> 4][input_byte & 0x0f];
}

/*
 * replace input_byte with inv_s_box
 * input: input_byte = a7a6a5a4a3a2a1a0
 * output: inv_s_box[a7a6a5a4][a3a2a1a0]
 */
void inv_sub_byte(uint8_t &input_byte)
{
    input_byte = inv_s_box[input_byte >> 4][input_byte & 0x0f];
}

/*
 * the g function
 * input: a word x(32-bit) and a round number round
 * firstly, rotate x, i.e. left shift x with a byte(8-bit)
 * secondly, sub_word x with s_box, i.e. sub_byte each byte of x with s_box
 * thirdly, do xor operation with x and Rcon[round]
*/
uint32_t g(uint32_t x, int round)
{
    uint8_t *u = uint32_to_uint8(x);
    rot_word(u);
    for (int i = 0; i < 4; ++i)
        sub_byte(u[i]);
    for (int i = 0; i < 4; ++i) {
        u[i] ^= Rcon[round][i];
    }
    uint32_t ans = uint8_to_uint32(u);
    return ans;
}

/*
 * left shift by 0, 1, 2, 3 from row_0 to row_3
 * input: state matrix(4 × 4)
 * output: the matrix after left shift
 * {state[0][0], state[0][1], state[0][2], state[0][3]} -> {state[0][0], state[0][1], state[0][2], state[0][3]}
 * {state[1][0], state[1][1], state[1][2], state[1][3]} -> {state[1][1], state[1][2], state[1][3], state[1][0]}
 * {state[2][0], state[2][1], state[2][2], state[2][3]} -> {state[2][2], state[2][3], state[2][0], state[2][1]}
 * {state[3][0], state[3][1], state[3][2], state[3][3]} -> {state[3][3], state[3][0], state[3][1], state[3][2]}
 */
void shift_row(uint8_t state[][4])
{
    for (int i = 0; i < 4; ++i) {
        uint8_t temp[4];
        for (int j = 0; j < 4; ++j) {
            temp[j] = state[i][(j + i) % 4];
        }
        for (int j = 0; j < 4; ++j)
            state[i][j] = temp[j];
    }
}

/*
 * right shift by 0, 1, 2, 3 from row_0 to row_3
 * input: state matrix(4 × 4)
 * output: the matrix after right shift
 * {state[0][0], state[0][1], state[0][2], state[0][3]} -> {state[0][0], state[0][1], state[0][2], state[0][3]}
 * {state[1][1], state[1][2], state[1][3], state[1][0]} -> {state[1][0], state[1][1], state[1][2], state[1][3]}
 * {state[2][2], state[2][3], state[2][0], state[2][1]} -> {state[2][0], state[2][1], state[2][2], state[2][3]}
 * {state[3][3], state[3][0], state[3][1], state[3][2]} -> {state[3][0], state[3][1], state[3][2], state[3][3]}
 */
void inv_shift_row(uint8_t state[][4])
{
    for (int i = 0; i < 4; ++i) {
        uint8_t temp[4];
        for (int j = 0; j < 4; ++j) {
            temp[j] = state[i][(j - i + 4) % 4];
        }
        for (int j = 0; j < 4; ++j)
            state[i][j] = temp[j];
    }
}

/*
 * add and sub in GF(2^8) is xor operation
*/
uint8_t g_add_sub(uint8_t a, uint8_t b)
{
    uint8_t ans = a ^ b;
    return ans;
}

/*
 * multiplication in GF(2^8)
 * i.e. f(x) * g(x) mod p(x), where p(x) = x^8 + x^4 + x^3 + x + 1
 * we use {f(x)} to represent the binary representation of f(x), then xf(x) = {f(x)} << 1
 * if f(x) = x^7 + f'(x) where deg(f') < 7, then xf(x) = x^4 + x^3 + x + 1 + xf'(x)
 * i.e. ({f(x)} << 1) ^ (0x1b), where 0x1b is the binary representation of x^4 + x^3 + x + 1
 * else if f(x) = f'(x) where deg(f') < 7, then xf(x) = xf'(x)
 * i.e. {f(x)} << 1
*/
uint8_t g_mul(uint8_t a, uint8_t b)
{
    uint8_t ans = 0;
    for (int i = 0; i < 8; ++i) {
        if (b & 1) ans ^= a;
        int high_bit = a & 0x80;
        a <<= 1, b >>= 1;
        if (high_bit) a ^= 0x1b;
    }
    return ans;
}

/*
 * mix the column
 * use the input matrix to left multiply a mix matrix
 * notice that all adding and multiplying is in GF(2^8)
 * input: a matrix(4 × 4)
 * output: a matrix after mixing the column
*/
void mix_column(uint8_t input_array[][4])
{
    uint8_t temp_array[4][4] = {0}; // initialization is necessary!
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                temp_array[i][j] = g_add_sub(temp_array[i][j], g_mul(mix_array[i][k], input_array[k][j]));
            }
        }
    }
    assign_b_to_a(input_array, temp_array);
}

/*
 * inversely mix the column
 * use the input matrix to left multiply a inv_mix matrix
 * notice that all adding and multiplying is in GF(2^8)
 * input: a matrix(4 × 4)
 * output: a matrix after inversely mixing the column
*/
void inv_mix_column(uint8_t input_array[][4])
{
    uint8_t temp_array[4][4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                temp_array[i][j] = g_add_sub(temp_array[i][j], g_mul(inv_mix_array[i][k], input_array[k][j]));
            }
        }
    }
    assign_b_to_a(input_array, temp_array);
}

/* expand the initial key(128-bit, represented by a 4 × 4 byte matrix)
 * input: key[4][4], expanded key[44]
 * {key[0][0], key[1][0], key[2][0], key[3][0]} -> w[0]
 * {key[0][1], key[1][1], key[2][1], key[3][1]} -> w[1]
 * {key[0][2], key[1][2], key[2][2], key[3][2]} -> w[2]
 * {key[0][3], key[1][3], key[2][3], key[3][3]} -> w[3]
 * for i = 4 to 43
 * if i % 4 == 0, w[i] = w[i - 4] ^ g(w[i - 1], i / 4)
 * if i % 4 != 0, w[i] = w[i - 4] ^ w[i - 1];
*/
void key_expand(uint8_t key[][4], uint32_t w[44])
{
    for (int i = 0; i < 4; ++i) {
        uint8_t *u = (uint8_t *)malloc(sizeof(uint8_t) * 4);
        for (int j = 0; j < 4; ++j)
            u[j] = key[j][i];
        w[i] = uint8_to_uint32(u);
    }
    for (int i = 4; i < 44; ++i) {
        if (i % 4 == 0) w[i] = w[i - 4] ^ g(w[i - 1], i / 4);
        else w[i] = w[i - 4] ^ w[i - 1];
    }
    //for (int i = 0; i < 44; ++i)
        //printf("w[%d] = %x\n", i, w[i]);
}

void genKey(uint8_t key[][4], uint32_t w[44])
{
    key_expand(key, w);
}

void encrypt(uint8_t plain[][4], uint32_t w[44], uint8_t cipher[][4])
{
    uint8_t state[4][4];
    assign_b_to_a(state, plain);
    add_round_key(state, w, 0);
    for (int round = 1; round <= 10 - 1; ++round) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                sub_byte(state[i][j]);
        shift_row(state);
        mix_column(state);
        add_round_key(state, w, round);

    }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            sub_byte(state[i][j]);
    shift_row(state);
    add_round_key(state, w, 10);
    assign_b_to_a(cipher, state);
}

void decrypt(uint8_t cipher[][4], uint32_t w[44], uint8_t message[][4])
{
    uint8_t state[4][4];
    assign_b_to_a(state, cipher);
    add_round_key(state, w, 10);
    for (int round = 10 - 1; round >= 1; --round) {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                inv_sub_byte(state[i][j]);
        inv_shift_row(state);
        add_round_key(state, w, round);
        inv_mix_column(state);
    }
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            inv_sub_byte(state[i][j]);
    inv_shift_row(state);
    add_round_key(state, w, 0);
    assign_b_to_a(message, state);
}

int main()
{
    uint8_t key[4][4] = {
        {0x2b, 0x28, 0xab, 0x09},
        {0x7e, 0xae, 0xf7, 0xcf},
        {0x15, 0xd2, 0x15, 0x4f},
        {0x16, 0xa6, 0x88, 0x3c}};
    uint8_t plain[4][4] = {
        {0x32, 0x88, 0x31, 0xe0},
        {0x43, 0x5a, 0x31, 0x37},
        {0xf6, 0x30, 0x98, 0x07},
        {0xa8, 0x8d, 0xa2, 0x34}};
    uint8_t cipher[4][4] = {0};
    uint8_t message[4][4] = {0};
    uint32_t w[44];
    genKey(key, w);
    encrypt(plain, w, cipher);
    decrypt(cipher, w, message);
    cout << "the plain text is:\n";
    debug(plain);
    cout << "the key is:\n";
    debug(key);
    cout << "the cipher is:\n";
    debug(cipher);
    cout << "the decrypted message is:\n";
    debug(message);
    return 0;
}
