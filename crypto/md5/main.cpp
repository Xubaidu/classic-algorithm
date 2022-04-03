#include <bits/stdc++.h>
#include "MD5.h"
#define word unsigned int
using namespace std;

int main()
{
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
        cout << "test string:\n" << test[i] << endl;
        cout << "expected ans:\n" << ans[i] << endl;
        cout << "my ans:\n" << my_ans << endl;
        puts((my_ans == ans[i]) ? "Accepted" : "Wrong Answer");
        puts("");
    }
    return 0;
}
