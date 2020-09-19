///链接：http://acm.hdu.edu.cn/showproblem.php?pid=6430
/*题意: 给定一颗树，每个点本身有一个权值x，现在每个结点有一个val值，x结点的val值为
  lca(u,v)=x，u和v的最大公约数 == x结点的val值；
  题解：数据范围，我们可以发现因子个数最大只有200个，那么我们对每个结点建线段树，然后合并即可；
  同时，我们应该可以对其进行一些优化，我们用一个sum[rt]维护这段区间内的最大公约数；这样在查询结果的时候
  可以通过这个值来判断两个线段树是否有同一个因子；
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

const int N = 200200;
vector<int> G[N];
int n,m,a[N],maxx,ans[N];
int root[N],lson[N * 400],rson[N * 400],top,sum[N * 400];
int head[N],ver[N << 1],Next[N << 1],tot;

void add(int x,int y){
    ver[++ tot] = y; Next[tot] = head[x]; head[x] = tot;
}

void Update(int &rt,int L,int R,int pos,int val){
   if(rt == 0) rt = ++ top;
   if(L == R) {
    sum[rt] = val; return ;
   }
   int mid = (L + R) >> 1;
   if(pos <= mid) Update(lson[rt],L,mid,pos,val);
   else Update(rson[rt],mid + 1,R,pos,val);
   sum[rt] = max(sum[lson[rt]],sum[rson[rt]]);
}
int Merge(int rt1,int rt2,int L,int R,int u){
    if(!rt1 || !rt2) return rt1 | rt2;
    if(sum[rt1] == sum[rt2]){
       ans[u] = max(ans[u],sum[rt1]);// return rt1;
    }
    int mid = (L + R) >> 1;
    lson[rt1] = Merge(lson[rt1],lson[rt2],L,mid,u);
    rson[rt1] = Merge(rson[rt1],rson[rt2],mid + 1,R,u);
    return rt1;
}

void dfs(int x){
    for(int i = 0; i < G[a[x]].size(); i ++){
        Update(root[x],1,maxx,G[a[x]][i],G[a[x]][i]);
    }
    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i];
        dfs(y);
        root[x] = Merge(root[x],root[y],1,maxx,x);
    }
}
int main(){
    for(int i = 1; i < 100100; i ++){
        for(int j = i; j < 100100; j += i){
            G[j].push_back(i);
        }
    }
    n = read();
    for(int i = 2; i <= n; i ++){
        int x = read();
        add(x,i);
    }
    for(int i = 1; i <= n; i ++) {
        a[i] = read(); maxx = max(maxx,a[i]);
        ans[i] = -1;
    }
    dfs(1);
    for(int i = 1; i <= n; i ++){
        printf("%d\n",ans[i]);
    }
}
