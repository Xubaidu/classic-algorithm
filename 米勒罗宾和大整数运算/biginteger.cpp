#include <bits/stdc++.h>
using namespace std;

/* 
 * overload "+, -, *, /, %, <, <=, >, >=" by bigInteger
 * bigInteger is represented by string
 */
bool operator < (const string &a, const string &b);
bool operator <= (const string &a, const string &b);
bool operator > (const string &a, const string &b);
bool operator >= (const string &a, const string &b);
string operator + (const string& a, const string& b);
string operator - (const string& a, const string& b);
string operator * (const string& a, const string& b);
string operator / (const string& a, const string& b);
string operator % (const string& a, const string& b);

int main()
{
    freopen("in.txt", "r", stdin);
    string s1, s2, s3, s4, s5, s6, s7;
    string x1, x2, x3, x4;
    int flag = 0;
    map<string, bool> mp;
    mp["False"] = false;
    mp["True"] = true;
    int cnt = 0;
    while (cin >> cnt >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7 >> x1 >> x2 >> x3 >> x4) {
        int f[11] = {0};
        //cout << x5 << endl;
        if (s1 + s2 == s3) f[0] = 1;
        if (s1 - s2 == s4) f[1] = 1;
        if (s1 * s2 == s5) f[2] = 1;
        if (s1 / s2 == s6) f[3] = 1;
        if (s1 % s2 == s7) f[4] = 1;
        
        if ((s1 < s2) == mp[x1]) f[5] = 1;
        if ((s1 <= s2) == mp[x2]) f[6] = 1;
        if ((s1 > s2) == mp[x3]) f[7] = 1;
        if ((s1 >= s2) == mp[x4]) f[8] = 1; 
        printf("%02d ", cnt++);
        for (int i = 0; i < 9; ++i) {
            if (f[i] == 0) cout << "×";
            else cout << "√";
        }
        cout << endl;
    }
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
