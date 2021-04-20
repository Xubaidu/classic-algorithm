#include <bits/stdc++.h>
#define int128 string
using namespace std;

int cmp(string A, string B);
string operator + (const string& a, const string& b);
string operator - (const string& a, const string& b);
string operator * (const string& a, const string& b);
string operator / (const string& a, const string& b);
string operator % (const string& a, const string& b);

string genRandString(int L);
int128 stringToInt(string s);
string intToString(int128 n);
int128 randInt128(int128 a, int128 b);
int128 qpow(int128 a, int128 b, int128 p);
bool miller_rabin(int128 n, int k);
bool isPrime(int128 n);
void solve();

int main()
{
    solve();
    return 0;
}

int cmp(string A, string B)
{
    if (A.length() < B.length()) return -1;
    else if (A.length() > B.length()) return 1;
    else {
        for (int i = 0; i < A.length(); ++i) {
            if (A[i] < B[i]) return -1;
            else if (A[i] > B[i]) return 1;
        }
        return 0;
    }
}

string operator + (const string& a, const string& b)
{
    int flag = 0;
    if (a[0] == '-' && b[0] == '-') flag = 1; // (-a) + (-b) = -(a + b)
    else if (a[0] == '-' && b[0] != '-') return b - a.substr(1, a.length()); // -a + b = b - a
    else if (a[0] != '-' && b[0] == '-') return a - b.substr(1, b.length()); // a + (-b) = a - b
    else flag = 0; // a + b
    string A = "", B = "";
    A = flag ? a.substr(1, a.length()) : a;
    B = flag ? b.substr(1, b.length()) : b;
    reverse(A.begin(), A.end());
    reverse(B.begin(), B.end());
    if (A.length() < B.length()) swap(A, B);
    int L1 = A.length(), L2 = B.length();
    string C = "";
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
    string A = "";
    string B = "";
    if (a[0] == '-' && b[0] == '-') { // -a - (-b) = b - a
        A = a.substr(1, a.length());
        B = b.substr(1, b.length());
        return B - A;
    }
    else if (a[0] == '-' && b[0] != '-') { // -a - b = (-a) + (-b)
        A = a;
        B = b;
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
        if (cmp(A, B) == -1) swap(A, B), flag = 1;
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
        int L1 = A.length(), L2 = B.length();
        int now = 0, lend = 0;
        string C = "";
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
    string C = "";
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
    if (cmp(A, B) < 0) return "0";
    else if (cmp(A, B) == 0) return "1";
    else {
        int L1 = A.length(), L2 = B.length();
        string C = "";
        string temp = "0";
        for (int i = 0; i < L1; ++i) {
            string x = string(1, A[i]);
            temp = temp + x;
            int cnt = 0;
            while (cmp(temp, B) >= 0) temp = temp - B, cnt++;
            temp = temp * "10";
            C += cnt + '0';
        }
        int pos = 0;
        while (C[pos] == '0') pos++;
        return C.substr(pos, C.length() - pos + 1);
    }
}


string operator % (const string& a, const string& b)
{
    if (b == "0") return "false";
    return a - a / b * b;
}


string genRandString(int L)
{
    string ans = "";
    ans += '1';
    for (int i = 0; i < L - 2; ++i) ans += '0' + rand() % 2;
    ans += '1';
    return ans;
}

int128 stringToInt(string s)
{
    int128 ans = "0";
    for (int i = 0; i < s.length(); ++i) {
        string x = "";
        x += s[i];
        ans = ans * "2", ans = ans + x;
    }
    return ans;
}

/*
int128 randInt128(int128 a, int128 b)
{
    mt19937 eng(time(0));
    uniform_int_distribution<int128> dis(a, b);
    return dis(eng);
}
*/

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

void solve()
{
    auto s = clock();
    srand((unsigned)time(0));
    int L = 120;
    int cnt = 0;
    while (cnt <= 10) {
        string s = genRandString(L);
        int128 n = stringToInt(s);
        //cout << s << endl;
        //cout << n << endl;
        int flag = isPrime(n);
        //puts(flag == 1 ? "Prime" : "Not prime");
        if (flag == 1) {
            cout << n << endl;
            cnt++;
        }
    }
    auto t = clock();
    cout << (double)(t - s) / CLOCKS_PER_SEC << endl;
}
/*
1291788562261213160815581951691991111
1071395667483194815238373915161450183
747191062361807887059318397063372873
1157293507237000392514477442218928617
779506605273809951673192958774854571
716475163499517949953323826055242397
1270049270688505857111099079466802359
799308036980022966805389139783875431
1278898030746379540284876690280892987
1280315986990421377916715100430704991
1023063733211930129981052520776272087
*/
