///链接：https://codeforces.com/problemset/problem/444/C
/*题意: 初始序列为a[i]=i；有两种操作，1，给一个区间和值x，把区间里面的数全部改为值x
        改动每个位置的代价是abs（a[i] - x）;2，给一个区间，问这个区间到现在累计了多少代价
  题解：线段树，同时我们可以用same[rt]来表示这个区间里面的值是不是一样，如果是一样的，那就没有必要一直更新下去；
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
#define inf 1e9
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

const int N = 1000100;
int n,m,OK;
int root,lson[N << 2],rson[N << 2],tot,num[N << 2]; ll sum[N << 2];
ll same[N << 2],val[N << 2],a[N],laze[N << 2];

void push_down(int rt,int L,int R){
    if(same[rt] == 0) return ;
    int mid = (L + R) >> 1;
    sum[lson[rt]] += (ll)(mid - L + 1) * laze[rt];
    sum[rson[rt]] += (ll)(R - mid) * laze[rt];
    laze[lson[rt]] += laze[rt];
    laze[rson[rt]] += laze[rt];
    same[lson[rt]] = same[rson[rt]] = same[rt];
    same[rt] = 0; laze[rt] = 0;
}
void Build_Tree(int &rt,int l,int r){
    rt = ++ tot; laze[rt] = 0;
    same[rt] = 0; val[rt] = 0; num[rt] = 0; sum[rt] = 0;
    if(l == r) {
        same[rt] = a[l];
        num[rt] = a[l]; return ;
    }
    int mid = (l + r) >> 1;
    Build_Tree(lson[rt],l,mid);
    Build_Tree(rson[rt],mid + 1,r);
    if(same[lson[rt]] == same[rson[rt]]) same[rt] = same[lson[rt]];
    else same[rt] = 0;
}

ll query(int rt,int L,int R,int l,int r){
    if(l <= L && r >= R) return sum[rt];
    push_down(rt,L,R);
    int mid = (L + R) >> 1;
    ll ans = 0;
    if(l <= mid) ans += query(lson[rt],L,mid,l,r);
    if(r > mid) ans += query(rson[rt],mid + 1,R,l,r);
    return ans;
}
void Update(int rt,int L,int R,int l,int r,int x){
     if(l <= L && r >= R && same[rt]){
        sum[rt] += abs(same[rt] - x) * (ll)(R - L + 1);
        laze[rt] += abs(same[rt] - x);same[rt] = x;
        return ;
     }
     push_down(rt,L,R);
     int mid = (L + R) >> 1;
     if(l <= mid) Update(lson[rt],L,mid,l,r,x);
     if(r > mid) Update(rson[rt],mid + 1,R,l,r,x);
     sum[rt] = sum[lson[rt]] + sum[rson[rt]];
     if(same[lson[rt]] == same[rson[rt]]) same[rt] = same[lson[rt]];
     else same[rt] = 0;
}
int main(){
    n = read(); m = read();
    for(int i = 1; i <= n; i ++){
        a[i] = i;
    }
    Build_Tree(root,1,n);
    while(m --){
        int op = read(),l = read(),r = read();
        if(op == 1){
            int x = read();
            Update(root,1,n,l,r,x);
            continue;
        }
        ll ans = query(root,1,n,l,r);
        printf("%lld\n",ans);
    }
}
