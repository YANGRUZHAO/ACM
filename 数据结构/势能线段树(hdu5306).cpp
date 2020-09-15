///链接：http://acm.hdu.edu.cn/showproblem.php?pid=5306
/*题意 对一个序列执行查询和修改三种操作，其中修改比较奇特；
  题解：这个如果暴力执行修改操作，那么一定会超时，所以我们考虑引入第二小的值，从而达到目的。减少复杂度
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
int max_val[N << 2],seg[N << 2],num[N << 2],tot,root,lson[N << 2],rson[N << 2];
int a[N];

void push_up(int rt){
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
    max_val[rt] = max(max_val[lson[rt]],max_val[rson[rt]]);
    if(max_val[lson[rt]]  == max_val[rson[rt]]){
        num[rt] = num[lson[rt]] + num[rson[rt]];
        seg[rt] = max(seg[lson[rt]],seg[rson[rt]]);
        return ;
    }
    if(max_val[rt] == max_val[lson[rt]]){
        num[rt] = num[lson[rt]];
        seg[rt] = max(seg[lson[rt]],max_val[rson[rt]]);
        return ;
    }
    num[rt] = num[rson[rt]];
    seg[rt] = max(seg[rson[rt]],max_val[lson[rt]]);
    return ;
}
void Tag_dwon(int rt,int maxx){
    if(max_val[rt] <= maxx) return ;
    sum[rt] = sum[rt] - (ll)num[rt] * (max_val[rt] - maxx);
    max_val[rt] = maxx;
}
void push_down(int rt){
    Tag_dwon(lson[rt],max_val[rt]);
    Tag_dwon(rson[rt],max_val[rt]);
}
void Build_Tree(int &rt,int l,int r){
    rt = ++ tot;
    max_val[rt] = seg[rt] = -1;
    num[rt] = sum[rt] = 0;
    if(l == r) {
        num[rt] = 1; sum[rt] = a[l];
        max_val[rt] = a[l];
        return ;
    }
    int mid = (l + r) >> 1;
    Build_Tree(lson[rt],l,mid);
    Build_Tree(rson[rt],mid + 1,r);
    push_up(rt);
}
void Update(int rt,int L,int R,int l,int r,int val){
    if(L > R) return ;
    if(max_val[rt] <= val) return ;
    if(l <= L && r >= R && val > seg[rt]){
       sum[rt] = sum[rt] - (ll)num[rt] * (max_val[rt] - val);
       max_val[rt] = val;
       return ;
    }
    push_down(rt);
    int mid = (L + R) >> 1;
    if(l <= mid) Update(lson[rt],L,mid,l,r,val);
    if(r > mid) Update(rson[rt],mid + 1,R,l,r,val);
    push_up(rt);
}
int get_maxx(int rt,int L,int R,int l,int r){
    if(L > R) return 0;
    if(l <= L && r >= R) {
        return max_val[rt];
    }
    push_down(rt);
    int mid = (L + R) >> 1;
    int maxx = 0;
    if(l <= mid) maxx = max(maxx,get_maxx(lson[rt],L,mid,l,r));
    if(r> mid) maxx = max(maxx,get_maxx(rson[rt],mid + 1,R,l,r));
    return maxx;
}
ll get_sum(int rt,int L,int R,int l,int r){
    if(L > R) return 0;
    if(l <= L && r >= R) {
        return sum[rt];
    }
    push_down(rt);
    int mid = (L + R) >> 1;
    ll ans = 0;
    if(l <= mid) ans += get_sum(lson[rt],L,mid,l,r);
    if(r > mid) ans += get_sum(rson[rt],mid + 1,R,l,r);
    return ans;
}
void init(){
    tot = 0;
}
int main(){
    int T = read();
    while(T --){
        n = read(); m = read();
        init();
        for(int i = 1; i <= n; i ++) a[i] = read();
        Build_Tree(root,1,n);
        while(m --){
            int op = read(),l = read(),r = read();
            if(op == 0){
                int t = read();
                Update(root,1,n,l,r,t);
            } else if(op == 1){
                printf("%d\n",get_maxx(root,1,n,l,r));
            } else {
                printf("%lld\n",get_sum(root,1,n,l,r));
            }
        }
    }
}
