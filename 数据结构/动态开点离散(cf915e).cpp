///链接：https://codeforces.com/problemset/problem/915/E
/*题意: n个初始为1的序列，q次操作，每次操作为给一个区间，如果op==1，则让给出区间的都变成0
        如果op==2，则让给出区间都变为1
  题解：注意到n很大，但是q不是特别大，所以我们可以动态开点进行维护，实际上，这也就是动态开点的模板题了。
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

const int N = 3000110 * 5;
int n,m;
int root,lson[N],rson[N],tot;
int laze[N],sum[N];

void push_down(int rt,int L,int R){
    if(laze[rt] == -1) return ;
    int mid = (L + R) >> 1;
    if(!lson[rt]) lson[rt] = ++ tot;
    if(!rson[rt]) rson[rt] = ++ tot;
    sum[lson[rt]] = (mid - L + 1) * laze[rt];
    sum[rson[rt]] = (R - mid) * laze[rt];
    laze[lson[rt]] = laze[rson[rt]] = laze[rt];
    //val[lson[rt]] = val[lson[rt]] = laze[rt];
    laze[rt] = -1;
}
void Update(int &rt,int L,int R,int l,int r,int x){
   if(R < L) return ;
   if(!rt) rt = ++ tot;
   if(l <= L && r >= R) {
      sum[rt] = (R - L + 1) * x;
      laze[rt] = x; // val[rt] = x;
      return ;
   }
   push_down(rt,L,R);
   int mid = (L + R) >> 1;
   if(l <= mid) Update(lson[rt],L,mid,l,r,x);
   if(r > mid) Update(rson[rt],mid + 1,R,l,r,x);
   sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}

int main(){
    n = read();int  q = read();
    for(int i = 0; i <= 40 * q;i ++) laze[i] = -1;
    while(q --) {
       int l = read(),r = read(),op = read();
       if(op == 1){
         Update(root,1,n,l,r,1);
       } else Update(root,1,n,l,r,0);
       printf("%d\n",n - sum[root]);
    }
}
