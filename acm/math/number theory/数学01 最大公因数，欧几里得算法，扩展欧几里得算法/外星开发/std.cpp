#include<bits/stdc++.h>
using namespace std;

const int SIZE=109;
int x[SIZE],y[SIZE],q[SIZE],r[SIZE],zero[SIZE];
void copy(int *a, int *b) {
    for (int i=0;i<SIZE;i++) a[i]=b[i];
}
void converts(int *a,string s){
    int i,len=(int)s.size();
    for (i=0;i<len;i++) a[i]=s[len-i-1]-'0';
    for (;i<SIZE;i++) a[i]=0;
}
bool le(int *a,int *b,int len=SIZE) {
    int i;
    for (i=len-1;i>=0 && a[i]==b[i]; i--);
    return i<0 || a[i]<b[i];
}
void sub(int *a,int *b,int len=SIZE) {
    for(int i=0;i<len;i++)
        if((a[i]-=b[i])<0) a[i+1]--,a[i]+=10;
}
void print(int *a){
    int i;
    for(i=SIZE-1;i>0;i--) if(a[i]>0) break;
    for(;i>=0;i--) cout<<a[i]; cout<<endl;
}
void div(int *q,int *r,int *a,int *b){
    converts(q,"0");
    copy(r,a);
    int j;
    for (j=SIZE-1;b[j]==0;j--);
    for (int i=SIZE-1-j;i>=0;i--)
        for (;le(b,r+i,SIZE-i);q[i]++)
            sub(r+i,b,SIZE-i);
}
void gcd(int *a,int *b){
//    print(a),print(b);
    div(q,r,a,b);
    if (le(r,zero)) { print(b); return; }
    copy(a,b),copy(b,r);
    gcd(a,b);
}

int main(){
    string s1,s2;
    cin>>s1>>s2;
    converts(x,s1),converts(y,s2);
    gcd(x,y);
    return 0;
}
