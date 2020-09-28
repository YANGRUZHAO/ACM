#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include"set"
#include"map"
using namespace std;
typedef long long ll;
#define PII pair<int,int>
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}
const int inf=1e9;
const int N = 3e5 + 10;
const int mod = 998244353;
typedef struct Node{
    int l,r,x;
    Node(){}
    Node(int a,int b,int c){
        l = a; r = b; x = c;
    }
}Node;

int n,k,a[N],c[N],b[N],last[N],pre[N],ans1[N],m;
map<int,int> Q;
int main(){
    int T = 1; T = read();
    while(T --){
      n = read();m = read();
      for(int i = 1; i <= n; i ++) a[i] = read();
      a[n + 1] = 0;
      ll ans = 0;
      for(int i = n; i >= 1; i --){
          c[i] = a[i] - a[i + 1];
          ans += max(c[i],0);
      }
      printf("%lld\n",ans);
      while(m --){
        int l = read(),r = read();
        if(l > r) swap(l,r);
        for(int i = max(1,l - 1);i <= min(l + 1,n); i ++){
            if(c[i] > 0) ans -= c[i];
        }
        for(int i = max(l + 2,r - 1); i <= min(n,r + 1); i ++){
            if(c[i] > 0) ans -= c[i];
        }
        swap(a[l],a[r]);
        for(int i = max(1,l - 1);i <= min(l + 1,n); i ++){
            c[i] = a[i] - a[i + 1];
        }
        for(int i = max(l + 2,r - 1); i <= min(n,r + 1); i ++){
            c[i] = a[i] - a[i + 1];
        }
        for(int i = max(1,l - 1);i <= min(l + 1,n); i ++){
            if(c[i] > 0) ans += c[i];
        }
        for(int i = max(l + 2,r - 1); i <= min(n,r + 1); i ++){
            if(c[i] > 0) ans += c[i];
        }
        printf("%lld\n",ans);
      }
    }
}
