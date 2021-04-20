#include <bits/stdc++.h>
using namespace std;

int cmp(string A, string B);
string operator + (const string& a, const string& b);
string operator - (const string& a, const string& b);
string operator * (const string& a, const string& b);
string operator / (const string& a, const string& b);
string operator % (const string& a, const string& b);

int main()
{
    freopen("in.txt", "r", stdin);
    string s1, s2, s3, s4, s5, s6, s7;
    int f = 0;
    while (cin >> s1 >> s2 >> s3 >> s4 >> s5 >> s6 >> s7) {
        int f[5] = {0};
        if (s1 + s2 == s3) f[0] = 1;
        if (s1 - s2 == s4) f[1] = 1;
        if (s1 * s2 == s5) f[2] = 1;
        if (s1 / s2 == s6) f[3] = 1;
        if (s1 % s2 == s7) f[4] = 1;
        for (int i = 0; i < 5; ++i) {
            if (f[i] == 0) cout << "×";
            else cout << "√";
        }
        cout << endl;
    }
    //puts(!f ? "AC" : "WA");
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
