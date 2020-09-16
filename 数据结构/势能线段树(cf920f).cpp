///链接：https://codeforces.com/problemset/problem/920/F
/*题意: 一个序列，m次操作，每次操作有两种：1，更改区间内的值，更改值为当前值的因子个数；2，查询区间和
  题解：这个如果暴力执行修改操作，那么一定会超时，所以我们考虑一下，我们发现如果每个位置更改6次以上
        就一定是为1了，所以我们统计一下当前区间更改次数，从而达到目的。减少复杂度
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
ll sum[N<<4];int n,m;
int tot,root,lson[N << 2],rson[N << 2],num[N << 2];
int a[N];

int check(int x){
    int ans = 0;
    for(int i = 1; i * i <= x; i ++){
       if(x % i) continue;
       ans ++;
       if(i == x / i) continue;
       ans ++;
    }
    return ans;
}

void Build_Tree(int &rt,int l,int r){
    rt = ++ tot;
    num[rt] = sum[rt] = 0;
    if(l == r) {
        num[rt] = 0; sum[rt] = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    Build_Tree(lson[rt],l,mid);
    Build_Tree(rson[rt],mid + 1,r);
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}

void Update(int rt,int L,int R,int l,int r){
    if(L > R) return ;
    if(num[rt] >= 6) return ;
    if(L == R){
       int x = sum[rt];
       sum[rt] = check(x);
       num[rt] ++;
       return ;
    }
    int mid = (L + R) >> 1;
    if(l <= mid) Update(lson[rt],L,mid,l,r);
    if(r > mid) Update(rson[rt],mid + 1,R,l,r);

    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
    num[rt] = min(num[lson[rt]],num[rson[rt]]);
}

ll get_sum(int rt,int L,int R,int l,int r){
    if(L > R) return 0;
    if(l <= L && r >= R) {
        return sum[rt];
    }
    int mid = (L + R) >> 1;
    ll ans = 0;
    if(l <= mid) ans += get_sum(lson[rt],L,mid,l,r);
    if(r > mid) ans += get_sum(rson[rt],mid + 1,R,l,r);
    return ans;
}

int main(){
   n = read(); m = read();
   for(int i = 1; i <= n; i ++) a[i] = read();
   Build_Tree(root,1,n);
   while(m --){
     int op = read(),l = read(),r = read();
     if(op == 2){
        ll ans = get_sum(root,1,n,l,r);
        printf("%lld\n",ans);
     } else {
         Update(root,1,n,l,r);
     }
   }
}
