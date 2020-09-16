///链接：http://acm.hdu.edu.cn/showproblem.php?pid=4630
/*题意: 一个序列，m次查询，每次查询区间内的任意两数的最大gcd是什么。
  题解：注意到这个题没有修改，所以可以离散化；那么线段树合并，合并什么东西呢？gcd很明显不好合并
  所以我们把查询按node[i].r < node[j].r进行排序；
  我们考虑维护一颗线段树，维护的值是当前区间的最大gcd。首先肯定要预处理所以因子，然后从左到右进行扫描；
  假设k<i<j;每扫描一个值a[i]，我们查看a[i]的所有因子，对一个因子x，如果之前存在过，假设a[k]存在x;
  那么很明显区间k--i这个区间的gcd是有x的，我们可以比较x和原有的ans，并取大值；即可以更新区间[k,i]；
  如果a[j]，也存在一个x，那么很明显k--j和i--j都是可更新区间，但是我们只要更新i--j就可以了。注意到我峨嵋你的查询是按r
  排序的，所以我们只需要保留离r最近的左端点进行更新即可。
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
typedef struct Node{
    int l,r,id;
}Node;
int maxx[N<<4];int n,m;
int tot,root,lson[N << 2],rson[N << 2],num[N << 2];
int a[N],top,pre[N],ans[N];
Node node[N];
vector<int> G[N];

void pre_init(){
    for(int i = 1; i <= 50000; i ++){
        for(int j = i; j <= 50000; j += i){
            G[j].push_back(i);
        }
    }
}
void init(){
    tot = 0; top = 0;
    for(int i = 0; i <= 50000; i ++) pre[i] = 0;
}
int cmp(Node a,Node b){
    return a.r < b.r;
}
void Build_Tree(int &rt,int l,int r){
    rt = ++ tot; maxx[rt] = 0;
    if(l == r) return ;
    int mid = (l + r) >> 1;
    Build_Tree(lson[rt],l,mid);
    Build_Tree(rson[rt],mid + 1,r);
}
void Update(int rt,int l,int r,int pos,int val){
    if(l == r){
        maxx[rt] = max(maxx[rt],val); return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) Update(lson[rt],l,mid,pos,val);
    if(pos > mid) Update(rson[rt],mid + 1,r,pos,val);
    maxx[rt] = max(maxx[lson[rt]],maxx[rson[rt]]);
}
int query(int rt,int L,int R,int l,int r){
    if(l <= L && r >= R) return maxx[rt];
    int mid = (L + R) >> 1;
    int ans = 0;
    if(l <= mid) ans = max(ans,query(lson[rt],L,mid,l,r));
    if(r > mid) ans = max(ans,query(rson[rt],mid + 1,R,l,r));
    return ans;
}
int main(){
   int T = 1; T = read();
   pre_init();
   while(T --){
      n = read();
      init();
      for(int i = 1; i <= n; i ++) a[i] = read();
      m = read();
      for(int i = 1; i <= m; i ++){
        node[i].l = read(); node[i].r = read();node[i].id = i;
      }
      sort(node + 1,node + m + 1,cmp);
      Build_Tree(root,1,n);
      for(int i = 1,j = 1; i <= n; i ++){
         if(j > m) break;
         for(int k = 0; k < G[a[i]].size(); k ++){
            int tmp = G[a[i]][k];
            if(pre[tmp] == 0) {pre[tmp] = i; continue;}
            Update(root,1,n,pre[tmp],tmp);
            pre[tmp] = i;
         }
         while(j <= m && i == node[j].r){
            int x = query(root,1,n,node[j].l,node[j].r);
            ans[node[j].id] = x;
            j ++;
         }
      }
      for(int i = 1; i <= m; i ++)
        printf("%d\n",ans[i]);
   }
}
