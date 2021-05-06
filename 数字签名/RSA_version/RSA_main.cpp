/*
 * @author: Xu Chenyang
 * @date: 2021.4.24
 * @email: 1127862434@qq.com
 * @institute: ECNU
 */

#include <bits/stdc++.h> 
#include "MD5.h"
#define int128 string
#define pb push_back
using namespace std;

/* big Integer */
bool operator < (const string &a, const string &b);
bool operator <= (const string &a, const string &b);
bool operator > (const string &a, const string &b);
bool operator >= (const string &a, const string &b);
string operator + (const string& a, const string& b);
string operator - (const string& a, const string& b);
string operator * (const string& a, const string& b);
string operator / (const string& a, const string& b);
string operator % (const string& a, const string& b);

/* miller-rabin */
string genRandString(int L);
int128 stringToInt(string s);
string intToString(int128 n);
int128 randInt128(int128 a, int128 b);
int128 qpow(int128 a, int128 b, int128 p);
bool miller_rabin(int128 n, int k);
bool isPrime(int128 n);

/* RSA */
struct PBK
{
    int128 n, e;
    PBK() {}
    PBK(int128 _n, int128 _e):
        n(_n), e(_e) {}
};

struct PRK
{
    int128 p, q, d;
    PRK() {}
    PRK(int128 _p, int128 _q, int128 _d):
        p(_p), q(_q), d(_d) {}
};

void genBigInt(const int num, const int L, vector<int128> &vec);
int128 exgcd(int128 a, int128 b, int128 &x, int128 &y);
int128 get_inv(int128 &a, int128 &m);
void genKey(PBK &pbk, PRK &prk, const int &L);
int128 plain2num(const string &plaintext);
string num2plain(const int128 &num);
string dec2bin(const int128 &num);
int128 hex2dec(const string &num);
string dec2hex(const int128 &num);
string bin2hex(string bin);
void showInfo(const string &plaintext, const int128 &hash_num, const int128 &cipher, const int128 &decrypted_hash_num);
void solve(const string &plaintext, const int &key_length);

int main()
{
    const string plain = "math";
    const int key_length = 128;
    solve(plain, key_length);
    return 0;
}

bool operator < (const string &a, const string &b)
{
    if (a[0] == '-' && b[0] != '-') return 1; // negative < positive
    else if (a[0] != '-' && b[0] == '-') return 0; // positive > negative
    else {
        int flag = (a[0] == '-') ? 0 : 1;
        string A = (a[0] == '-') ? a.substr(1, a.length()) : a.substr(0, a.length());
        string B = (b[0] == '-') ? b.substr(1, b.length()) : b.substr(0, b.length());
        if (a.length() < b.length()) return flag;
        else if (a.length() > b.length()) return flag ^ 1;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i]) return flag;
            else if (a[i] > b[i]) return flag ^ 1;
            else continue;
        }
    }
    return 0;
}

bool operator <= (const string &a, const string &b)
{
    if (a[0] == '-' && b[0] != '-') return 1; // negative <= positive
    else if (a[0] != '-' && b[0] == '-') return 0; // positive >= negative
    else {
        int flag = (a[0] == '-') ? 0 : 1;
        string A = (a[0] == '-') ? a.substr(1, a.length()) : a.substr(0, a.length());
        string B = (b[0] == '-') ? b.substr(1, b.length()) : b.substr(0, b.length());
        if (a.length() < b.length()) return flag;
        else if (a.length() > b.length()) return flag ^ 1;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i]) return flag;
            else if (a[i] > b[i]) return flag ^ 1;
            else continue;
        }
    }
    return 1;
}

bool operator > (const string &a, const string &b)
{
    if (a[0] == '-' && b[0] != '-') return 0; // negative < positive
    else if (a[0] != '-' && b[0] == '-') return 1; // positive > negative
    else {
        int flag = (a[0] == '-') ? 1 : 0;
        string A = (a[0] == '-') ? a.substr(1, a.length()) : a.substr(0, a.length());
        string B = (b[0] == '-') ? b.substr(1, b.length()) : b.substr(0, b.length());
        if (a.length() < b.length()) return flag;
        else if (a.length() > b.length()) return flag ^ 1;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i]) return flag;
            else if (a[i] > b[i]) return flag ^ 1;
            else continue;
        }
    }
    return 0;
}

bool operator >= (const string &a, const string &b)
{
    if (a[0] == '-' && b[0] != '-') return 0;
    else if (a[0] != '-' && b[0] == '-') return 1;
    else {
        int flag = (a[0] == '-') ? 1 : 0;
        string A = (a[0] == '-') ? a.substr(1, a.length()) : a.substr(0, a.length());
        string B = (b[0] == '-') ? b.substr(1, b.length()) : b.substr(0, b.length());
        if (a.length() < b.length()) return flag;
        else if (a.length() > b.length()) return flag ^ 1;
        for (int i = 0; i < a.length(); ++i) {
            if (a[i] < b[i]) return flag;
            else if (a[i] > b[i]) return flag ^ 1;
            else continue;
        }
    }
    return 1;
}

string operator + (const string& a, const string& b)
{
    int flag = 0;
    if (a[0] == '-' && b[0] == '-') flag = 1; // (-a) + (-b) = -(a + b)
    else if (a[0] == '-' && b[0] != '-') return b - a.substr(1, a.length()); // -a + b = b - a
    else if (a[0] != '-' && b[0] == '-') return a - b.substr(1, b.length()); // a + (-b) = a - b
    else flag = 0; // a + b
    string A = flag ? a.substr(1, a.length()) : a;
    string B = flag ? b.substr(1, b.length()) : b;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    if (A.length() < B.length()) swap(A, B);
    int L1 = A.length(), L2 = B.length();
    string C;
    int now = 0, up = 0;
    for (int i = 0; i < L1; ++i) {
        if (i < L2) now = up + A[i] - '0' + B[i] -'0';
        else now = up + A[i] - '0';
        up = now / 10;
        now %= 10;
        C += now + '0';
    }
    while (up) C += up % 10 + '0', up /= 10;
    if (flag) C += '-';
    reverse(C.begin(), C.end());
    return C;
}

string operator - (const string& a, const string& b)
{
    string A;
    string B;
    if (a[0] == '-' && b[0] == '-') { // -a - (-b) = b - a
        A = a.substr(1, a.length());
        B = b.substr(1, b.length());
        return B - A;
    }
    else if (a[0] == '-' && b[0] != '-') { // -a - b = -(a + b)
        A = a.substr(1, a.length());
        B = b;
        //cout << A + B << endl;
        return (A + B).insert(0, "-");
    }
    else if (a[0] != '-' && b[0] == '-') { // a - (-b) = a + b
        A = a;
        B = b.substr(1, b.length());
        return A + B;
    }
    else { // a - b
        A = a, B = b;
        int flag = 0;
        if (A < B) swap(A, B), flag = 1;
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
        int L1 = A.length(), L2 = B.length();
        int now = 0, lend = 0;
        string C;
        for (int i = 0; i < L1; ++i) {
            if (i < L2) now = lend + (A[i] - '0') - (B[i] - '0');
            else now = lend + (A[i] - '0');
            if (now < 0) now += 10, lend = -1;
            else lend = 0;
            C += now + '0';
        }
        int pos = C.length() - 1;
        while (C[pos] == '0' && pos > 0) --pos;
        C = C.substr(0, pos + 1);
        if (flag) C += '-';
        reverse(C.begin(), C.end());
        return C;
    }
}

string operator * (const string& a, const string& b)
{
    int flag = 0;
    if (a[0] == '-' && b[0] == '-') flag = 0;
    else if (a[0] == '-' && b[0] != '-') flag = 1;
    else if (a[0] != '-' && b[0] == '-') flag = 1;
    else flag = 0;
    string A = a[0] == '-' ? a.substr(1, a.length()) : a;
    string B = b[0] == '-' ? b.substr(1, b.length()) : b;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    if (A.length() < B.length()) swap(A, B);
    int L1 = A.length(), L2 = B.length();
    vector<int> arr(L1 + L2, 0);
    for (int i = 0; i < L1; ++i)
        for (int j = 0; j < L2; ++j)
            arr[i + j] += (A[i] - '0') * (B[j] - '0');
    string C;
    int up = 0;
    for (int i = 0; i < L1 + L2; ++i) {
        int now = up + arr[i];
        C += now % 10 + '0';
        up = now / 10;
    }
    while (up) {
        C += up % 10;
        up = up / 10;
    }
    int pos = C.length() - 1;
    while (C[pos] == '0' && pos > 0) --pos;
    C = C.substr(0, pos + 1);
    if (flag) C += '-';
    reverse(C.begin(), C.end());
    return C;
}

string operator / (const string& a, const string& b)
{
    string A = a;
    string B = b;
    if (B == "0") return "false";
    if (A < B) return "0";
    else if (A == B) return "1";
    else {
        int L1 = A.length(), L2 = B.length();
        string C;
        string temp = "0";
        for (int i = 0; i < L1; ++i) {
            string x = string(1, A[i]);
            temp = temp + x;
            int cnt = 0;
            while (temp >= B) {
                temp = temp - B, cnt++;
            }
            temp = temp * "10";
            C += cnt + '0';
        }
        int pos = 0;
        while (C[pos] == '0') pos++;
        //cout << C << endl;
        return C.substr(pos, C.length() - pos + 1);
    }
}

string operator % (const string& a, const string& b)
{
    if (b == "0") return "false";
    string A = a;
    while (A[0] == '-') A = A + b;
    return A - A / b * b;
}

string genRandString(int L)
{
    string ans;
    ans += '1';
    for (int i = 0; i < L - 2; ++i) ans += '0' + rand() % 2;
    ans += '1';
    return ans;
}

int128 stringToInt(string s)
{
    int128 ans = "0";
    for (int i = 0; i < s.length(); ++i) {
        string x;
        x += s[i];
        ans = ans * "2", ans = ans + x;
    }
    return ans;
}

int128 qpow(int128 a, int128 b, int128 p)
{
    int128 ans = "1";
    while (b != "0") {
        if (b % "2" == "1") ans = ans * a % p;
        a = a * a % p, b = b / "2";
    }
    return ans;
}

bool miller_rabin(int128 n)
{
    int128 t = n - "1";
    int s = 0;
    while (t % "2" == "0") t = t / "2", s++;
    vector<int128> base = {"2", "325", "9375", "28178", "450775", "9780504", "1795265022"};
    for (int i = 0; i < base.size(); ++i) {
        int128 a = base[i];
        int128 temp = qpow(a, t, n);
        if (temp % n == "1" || temp % n == n - "1") continue; // 本轮检测通过
        int flag = 0;
        for (int j = 1; j < s; ++j) {
            temp = temp * temp % n;
            if (temp % n == n - "1") {flag = 1; break;}
        }
        if (flag) continue; // 本轮检测通过
        return 0; // 检测不通过
    }
    return 1;
}

bool isPrime(int128 n)
{
    if (n == "1") return 0; // 判断 1
    if (n == "2") return 1; // 判断 2
    if (n % "2" == "0") return 0; // 判断偶数
    return miller_rabin(n);
}

void genBigInt(const int num, const int L, vector<int128> &vec)
{
    srand((unsigned)time(0));
    int cnt = 0;
    while (cnt < num) {
        string s = genRandString(L);
        int128 n = stringToInt(s);
        //cout << s << endl;
        //cout << n << endl;
        int flag = isPrime(n);
        //puts(flag == 1 ? "Prime" : "Not prime");
        if (flag == 1) {
            vec.pb(n);
            cnt++;
        }
    }
}

int128 exgcd(int128 a, int128 b, int128 &x, int128 &y)
{
    if (b == "0") {x = "1", y = "0"; return a;}
    int128 r = exgcd(b, a % b, y, x);
    y = y - (a / b) * x;
    return r;
}

int128 get_inv(int128 &a, int128 &m)
{
    int128 x, y;
    int128 A = a, M = m;
    int128 r = exgcd(A, M, x, y);
    if (r != "1") return "-1";
    return x % m;
}

void genKey(PBK &pbk, PRK &prk, const int &L)
{
    vector<int128> vec;
    do {
        genBigInt(2, L, vec);
    } while (vec[0] == vec[1]);
    int128 p = vec[0], q = vec[1];
    int128 n = p * q;
    int128 z = (p - "1") * (q - "1");
    int128 e = "2";
    int128 d;
    int128 add = "1";
    while (1) {
        int x, y;
        d = get_inv(e, z);
        if (d != "-1") break;
        else e = e + add;
    }
    pbk = PBK(n, e);
    prk = PRK(p, q, d);
    //cout << p << ' ' << q << ' ' << n <<endl;
    //cout << d << ' ' << e << ' ' << z << endl;
}

int128 plain2num(const string &plaintext)
{
    int128 ans;
    string temp;
    for (auto &i: plaintext)
        temp += bitset<8>(i).to_string();
    int cnt = 0;
    int128 add = "1";
    for (auto &i: temp) {
        ans = ans * "2";
        if (i == '1') ans = ans + add;
    }
    return ans;
}

string num2plain(const int128 &num)
{
    string bin = dec2bin(num);
    string ret;
    int temp = 0;
    for (int i = 1; i <= bin.length(); ++i) {
        if (i % 8 == 0) {
            ret += char(temp);
            if (i < bin.length()) temp = bin[i] - '0';
        }
        else {
            temp *= 2;
            temp += bin[i] - '0';
        }
    }
    return ret;
}

string dec2bin(const int128 &num)
{
    string bin;
    int128 n = num;
    int cnt = 0;
    while (n != "0") {
        cnt++;
        bin += n % "2";
        n = n / "2";
    }
    for (int i = 0; i < 8 - cnt % 8; ++i) bin += '0';
    reverse(bin.begin(), bin.end());
    return bin;
}

int128 hex2dec(const string &num)
{
    int128 ans;
    for (int i = 0; i < num.length(); ++i) {
        int128 add;
        if (num[i] >= '0' && num[i] <= '9') add = string(1, num[i]);
        else if (num[i] == 'a') add = "10";
        else if (num[i] == 'b') add = "11";
        else if (num[i] == 'c') add = "12";
        else if (num[i] == 'd') add = "13";
        else if (num[i] == 'e') add = "14";
        else if (num[i] == 'f') add = "15";
        ans = ans * "16", ans = ans + add;
    }
    return ans;
}

string dec2hex(const int128 &num)
{
    return bin2hex(dec2bin(num));
}

string bin2hex(string bin)
{
    string hex = "0x";
    int temp = bin[0] - '0';
    for (int i = 1; i <= bin.length(); ++i) {
        if (i % 4 == 0) {
            hex += temp >= 10 ? temp - 10 + 'a' : temp + '0';
            temp = 0;
        }
        if (i < bin.length()) temp *= 2, temp += bin[i] - '0';
    }
    return hex;
}

void showInfo(const string &plaintext, const int128 &hash_num, const int128 &cipher, const int128 &decrypted_hash_num)
{
    cout << "the plaintext is:\n" << plaintext << endl;
    cout << "the digest of plaintext is:\n" << hash_num << endl;
    cout << "the ciphertext of digest is:\n" << cipher << endl;
    cout << "the decrypted plaintext is:\n" << decrypted_hash_num << endl;
    cout << "whether the signature is equal to the digest?" << endl;
    if (hash_num == decrypted_hash_num) puts("Yes");
    else puts("No");
}

void solve(const string &plaintext, const int &key_length)
{
    PBK pbk;
    PRK prk;
    MD5 md5;
    genKey(pbk, prk, key_length);
    string hash_num = md5.getMD5(plaintext);
    int128 cipher_hash_num = qpow(hex2dec(hash_num), prk.d, pbk.n);
    string decrypted_hash_num = dec2hex(qpow(cipher_hash_num, pbk.e, pbk.n));
    showInfo(plaintext, hash_num, cipher_hash_num, decrypted_hash_num);
    return;
}
