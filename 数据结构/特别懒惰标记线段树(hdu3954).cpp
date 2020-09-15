///链接：http://acm.hdu.edu.cn/showproblem.php?pid=3954
/*题意 打怪升级，但是每次升级的经验值为k（等级）*e(i);
  题解：如果每个结点都进行修改的话，肯定会超时的，所以我们需要考虑如何打懒惰标记。懒惰标记的本质
  还是减少修改次数，我们可以对每个结点维护一个当前区间所需要的的最小经验值；如果这次打怪加的经验都不足以
  让这个区间内的结点升级，那我们就没有必要再往下进行更新了。同时，我们可以通过一个小的数学操作
  （（升级经验要求） - 当前经验）/ 等级 在向上取整，则可以消除等级对我们的懒惰标记的影响。
  所以每个结点需要维护三个值：
        当前区间内升级的最小经验值，当前区间内的最大经验值，当前区间内的最大等级
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
int root,lson[N << 2],rson[N << 2],tot,max_val[N << 2],min_val[N << 2],max_top[N << 2];
int laze[N << 2],a[N];

void push_up(int rt){
    max_val[rt] = max(max_val[lson[rt]],max_val[rson[rt]]);
    min_val[rt] = min(min_val[lson[rt]],min_val[rson[rt]]);
    max_top[rt] = max(max_top[lson[rt]],max_top[rson[rt]]);
}
void push_down(int rt){
    if(laze[rt] == 0) return ;
    laze[lson[rt]] += laze[rt]; laze[rson[rt]] += laze[rt];
    ///码代码时，laze[rt] * max_top[rt];未注意到!!
    max_val[lson[rt]] += laze[rt] * max_top[lson[rt]]; max_val[rson[rt]] += laze[rt] * max_top[rson[rt]];
    ///开始直接就忘记写这行了，既然加了laze[rt]，那所需要的经验就肯定要相应的减去
    min_val[lson[rt]] -= laze[rt]; min_val[rson[rt]] -= laze[rt];
    laze[rt] = 0;
}
void Build_Tree(int &rt,int l,int r){
  rt = ++ tot; laze[rt] = 0;
  if(l == r){
    max_val[rt] = 0; max_top[rt] = 1; laze[rt] = 0;
    min_val[rt] = a[max_top[rt] + 1] - max_val[rt];
    return ;
  }
  int mid = (l + r) >> 1;
  Build_Tree(lson[rt],l,mid);
  Build_Tree(rson[rt],mid + 1,r);
  push_up(rt);
}

void Update(int rt,int L,int R,int l,int r,int val){
   if(l <= L && r >= R && min_val[rt] > val){
       max_val[rt] += val * max_top[rt];
       ///同上
       min_val[rt] -= val;
       laze[rt] += val; return ;
   }
   if(L == R){
     max_val[rt] += val * max_top[rt];
    // printf("%d max_val =%d\n",L,max_val[rt]);
     while(max_top[rt] + 1 <= m && a[max_top[rt] + 1] <= max_val[rt]) max_top[rt] += 1;
     min_val[rt] = (a[max_top[rt] + 1] - max_val[rt]) / max_top[rt];
     if((a[max_top[rt] + 1] - max_val[rt]) % max_top[rt]) min_val[rt] ++;
     return ;
   }
   push_down(rt);
   int mid = (L + R) >> 1;
   if(l <= mid) Update(lson[rt],L,mid,l,r,val);
   if(r > mid) Update(rson[rt],mid + 1,R,l,r,val);
   push_up(rt);
}

int query(int rt,int L,int R,int l,int r){
    if(R < L) return 0;
    if(l <= L && r >= R) return max_val[rt];
    push_down(rt);
    int mid = (L + R) >> 1;
    int ans = 0;
    if(l <= mid) ans = max(ans,query(lson[rt],L,mid,l,r));
    if(r > mid) ans = max(ans,query(rson[rt],mid + 1,R,l,r));
    return ans;
}

void init(){
    tot = 0;
}
int main(){
    int T = read(); int cont = 1;
    while(T --){

        n = read(); m = read(); int q = read();
        init();a[1] = 0;
        for(int i = 2; i <= m; i ++) a[i] = read();
        a[m + 1] = 1<<30;
        Build_Tree(root,1,n);
        printf("Case %d:\n",cont ++);
        while(q --){
            char str[5]; scanf("%s",str);
            int l = read(),r = read();
            if(str[0] == 'W'){
               int x = read();
               Update(root,1,n,l,r,x);
            } else if(str[0] == 'Q'){
               int sum = query(root,1,n,l,r);
               printf("%d\n",sum);
            }
        }
        printf("\n");
    }
}
