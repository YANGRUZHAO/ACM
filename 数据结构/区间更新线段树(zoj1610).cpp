///链接：https://zoj.pintia.cn/problem-sets/91827364500/problems/91827365109
/*题意: 给一段区间进行染色;在经过多次染色之后，问每种颜色有多少段
  题解：线段树，区间更新赋值，在最后统计；
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

const int N = 8010;
int n,m,OK;
int root,lson[N << 2],rson[N << 2],tot,col[N << 2];
int laze[N << 2],ans[N << 2],id[N << 2];

void push_down(int rt){
    if(col[rt] == -1) return ;
    col[lson[rt]] = col[rson[rt]] = col[rt];
    col[rt] = -1;
}
void Build_Tree(int &rt,int l,int r){
    rt = ++ tot;
    laze[rt] = 0;col[rt] = -1;
    if(l == r) {
        return ;
    }
    int mid = (l + r) >> 1;
    Build_Tree(lson[rt],l,mid);
    Build_Tree(rson[rt],mid + 1,r);
}
void Update(int rt,int L,int R,int l,int r,int x){
     if(l <= L && r >= R){
       // printf("l = %d r = %d x = %d\n",l,r,x);
        col[rt] = x; return ;
     }
     if(col[rt] == x) return ;
     push_down(rt);
     int mid = (L + R) >> 1;
     if(l <= mid) Update(lson[rt],L,mid,l,r,x);
     if(r > mid) Update(rson[rt],mid + 1,R,l,r,x);
}
void query(int rt,int L,int R){
    if(col[rt] >= 0){
        for(int i = L; i <= R; i ++) id[i] = col[rt];
        return ;
    }
    if(L == R) return ;
    //push_down(rt);
    int mid = (L + R) >> 1;
    query(lson[rt],L,mid);
    query(rson[rt],mid + 1,R);
}
int main(){
    while(~scanf("%d",&n)){
        tot = 0;
        for(int i = 0; i <= 8010; i ++) id[i] = -1,col[i] = -1,ans[i] = 0;
        Build_Tree(root,1,N);
        for(int i = 1; i <= n; i ++){
            int l = read(),r = read(),col = read();
            if(l == r) continue;
            ++ l;
            Update(root,1,N,l,r,col);
        }
        query(root,1,N);

        for(int i = 1; i <= N; i ++){
            int j = i;
            if(id[j] == -1) {continue;}
            while(j + 1 <= N && id[j] == id[j + 1]){
                j ++;
            }
            ans[id[j]] ++;
            i = j;
        }
        for(int i = 0; i <= 8005; i ++){
            if(ans[i] == 0) continue;
            printf("%d %d\n",i,ans[i]);
        }
        printf("\n");
    }
}
