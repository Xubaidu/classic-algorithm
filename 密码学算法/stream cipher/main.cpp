#include <bits/stdc++.h>
#include <algorithm>
#include <iostream>
using namespace std;

int dp[15];

void init()
{
    dp[0] = 0, dp[1] = 0, dp[2] = 0, dp[3] = 1;
    for (int i = 4; i < 15; ++i)
        dp[i] = (dp[i - 1] + dp[i - 4]) % 2;
}

string input(string msg)
{
    string ans = "";
    for (int i = 0; i < msg.length(); ++i) {
        char x = msg[i];
        //cout << x << endl;
        string temp = "";
        while (x) {
            temp += x % 2 + '0';
            x /= 2;
        }
        for (int i = temp.length(); i < 8; ++i) temp += '0';
        reverse(temp.begin(), temp.end());
        ans += temp;
    }
    return ans;
}

pair<string, string> encry(string msg)
{
    int L = msg.length();
    int x = L / 15, y = L % 15;
    string key = "";
    for (int i = 1; i <= x; ++i)
        for (int j = 0; j < 15; ++j)
            key += dp[j] + '0';
    for (int i = 0; i < y; ++i)
        key += dp[i] + '0';
    string cipher = "";
    for (int i = 0; i < L; ++i)
        cipher += '0' + (msg[i] - '0') ^ (key[i] - '0');
    return {cipher, key};
}

string decry(string c, string k)
{
    string temp = "";
    int L = c.length();
    for (int i = 0; i < L; ++i)
        temp += '0' + (c[i] - '0') ^ (k[i] - '0');
    int res = temp[0] - '0';
    string ans = "";
    for (int i = 1; i <= L; ++i) {
        if (i % 8 == 0) ans += char(res), res = temp[i] - '0';
        else res = res * 2 + temp[i] - '0';
    }
    return ans;
}
int main()
{
    init();
    cout << "Please input the cipher text" << endl;
    string s;
    getline(cin, s);
    string msg = input(s);
    pair<string, string> pss = encry(msg);
    string cipher = pss.first;
    string key = pss.second;
    cout << "The cipher text is:\n" << cipher << endl;
    cout << "The key is:\n" << key << endl;
    string plain = decry(cipher, key);
    cout << "The decrypted plain text is:\n" << plain << endl;
    return 0;
}

/*
000111101011001
000101001101110
*/
