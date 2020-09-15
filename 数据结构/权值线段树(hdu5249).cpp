///链接：http://acm.hdu.edu.cn/showproblem.php?pid=5249
/*题意: n个值，每次有插入，查询当前数据量的中间值，或者删除最前面插入的那个数
  题解：观察到插入的范围是很大的，所以肯定要离散化，离散化后建线段树
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

const int N = 3000110;
typedef struct Node{
    char str[100];
    int x;
}Node;

int n,m,len;
int root,lson[N],rson[N],tot;
int sum[N];
Node node[N];
int a[N],top;

void Build_Tree(int &rt,int L,int R){
    rt = ++ tot; sum[rt] = 0;
    if(L == R) return ;
    int mid = (L + R) >> 1;
    Build_Tree(lson[rt],L,mid);
    Build_Tree(rson[rt],mid + 1,R);
}

void Update(int rt,int L,int R,int pos,int val){
    if(R < L) return ;
    if(L == R){
        sum[rt] += val; return ;
    }
    int mid = (L + R) >> 1;
    if(pos <= mid) Update(lson[rt],L,mid,pos,val);
    if(pos > mid) Update(rson[rt],mid + 1,R,pos,val);
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
int query(int rt,int L,int R,int num){
    if(L == R) {
      return L;
    }
    int mid = (L + R) >> 1;
    if(sum[lson[rt]] >= num) return query(lson[rt],L,mid,num);
    return query(rson[rt],mid + 1,R,num - sum[lson[rt]]);
}
int main(){
    int cont = 1;
    while(~scanf("%d",&n)){
        queue<int> Q; tot = 0; top = 0;
        printf("Case #%d:\n",cont ++);
        for(int i = 1; i <= n; i ++){
            scanf("%s",node[i].str);
            if(node[i].str[0] == 'i') {
                node[i].x = read();a[++ top] = node[i].x;
            }
        }
        sort(a + 1,a + top + 1);
        len = unique(a + 1,a + top + 1) - a - 1;
        Build_Tree(root,1,len);
        for(int i = 1; i <= n; i ++){
            if(node[i].str[0] == 'i'){
                int x = node[i].x;
                Q.push(x);
                int idx = lower_bound(a + 1,a + len + 1,x) - a;
                Update(root,1,len,idx,1);
            }
            if(node[i].str[0] == 'o'){
                int x = Q.front(); Q.pop();
                int idx = lower_bound(a + 1,a + len + 1,x) - a;
                Update(root,1,len,idx,-1);
            }
            if(node[i].str[0] == 'q'){
               int m = Q.size();
               int id = floor(m / 2.0) + 1;
               printf("%d\n",a[query(root,1,len,id)]);
            }
        }
    }
}
