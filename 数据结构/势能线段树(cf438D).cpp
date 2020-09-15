///链接：https://codeforces.com/problemset/problem/438/D
/*题意: 三种操作，1，求和，2，区间取模，3，单点修改
  题解：线段树，考虑保存最大值，如果t大于当前最大值了，就一定不要继续递归了
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <set>
#include"queue"
#include <vector>
#define inf 107374182
#define M 10010001
#define ll long long
#define PII pair<int,int>
using namespace std;
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}

const int N = 1000010;
int n,m;
int root,lson[N << 2],rson[N << 2],tot,maxx[N << 2],val[N << 2];
ll sum[N << 2];
int a[N];

void push_up(int rt){
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
    maxx[rt] = max(maxx[lson[rt]],maxx[rson[rt]]);
}
void Build_Tree(int &rt,int l,int r){
  rt = ++ tot;sum[rt] = 0; maxx[rt] =-1;
  if(l == r){
    sum[rt] = maxx[rt] = val[rt] = a[l];
    return ;
  }
  int mid = (l + r) >> 1;
  Build_Tree(lson[rt],l,mid);
  Build_Tree(rson[rt],mid + 1,r);
  push_up(rt);
}

void Update(int rt,int L,int R,int pos,int x){
   if(L == R){
     val[rt] = x;
     sum[rt] = maxx[rt] = x;
     return ;
   }
   int mid = (L + R) >> 1;
   if(pos <= mid) Update(lson[rt],L,mid,pos,x);
   else Update(rson[rt],mid + 1,R,pos,x);
   push_up(rt);
}
void Update_mod(int rt,int L,int R,int l,int r,int x){
    if(maxx[rt] < x)return ;
 //   if(l <= L && r >= R && maxx[rt] < x) return ;
    if(L == R){
        val[rt] %= x;maxx[rt] = sum[rt] = val[rt]; return ;
    }
    int mid = (L + R) >> 1;
    if(l <= mid) Update_mod(lson[rt],L,mid,l,r,x);
    if(r > mid) Update_mod(rson[rt],mid + 1,R,l,r,x);
    push_up(rt);
}
ll query(int rt,int L,int R,int l,int r){
  //  if(R < L) return 0;
    if(l <= L && r >= R) return sum[rt];
    int mid = (L + R) >> 1;
    ll ans = 0;
    if(l <= mid) ans = ans + query(lson[rt],L,mid,l,r);
    if(r > mid) ans = ans + query(rson[rt],mid + 1,R,l,r);
    return ans;
}

int main(){
    n = read(); m = read();
    for(int i = 1 ;i <= n; i ++) a[i] = read();
    Build_Tree(root,1,n);
    while(m --){
         int op = read(); int l = read(),r = read();
         if(op == 1) {
            ll ans = query(root,1,n,l,r);
            printf("%lld\n",ans);
         }
         if(op == 2) {
            int t = read();
            Update_mod(root,1,n,l,r,t);
         }
         if(op == 3){
            Update(root,1,n,l,r);
         }
    }
}
