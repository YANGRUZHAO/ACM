///链接：http://poj.org/problem?id=3321
/*题意：统计一颗子树上的苹果数量，同时还有m次的对子树上的苹果进行更改的操作
        需要实时回答
  题解：通过dfs序列，我们可以得到每咳子树的dfs序列，从而用树状数组进行维护
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

const int N = 2001000;
int head[N],ver[N << 1],Next[N << 1],tot;
int n,m,in[N],out[N],top;
int C[N],a[N];

int lowbit(int x){
    return x&(-x);
}
void add(int x,int y){
    ver[++ tot] = y; Next[tot] = head[x]; head[x] = tot;
}
void Update(int x,int val){
    for(int i = x; i <=  n; i += lowbit(i)){
       C[i] += val;
    }
}
int query(int x){
    int ans = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        ans += C[i];
    }
    return ans;
}
void dfs(int x,int far){
    in[x] = ++ top;
    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i];
        if(y == far) continue;
        dfs(y,x);
    }
    out[x] = top;
}

int main(){
    n = read();
    for(int i = 1;i < n; i ++){
        int x = read(),y = read();
        add(x,y); add(y,x);
        a[i] = 1;
    }
    a[n] = 1;
    dfs(1,0);
    for(int i = 1; i <= n; i ++){
        Update(i,1);
    }
    int q = read();
    while(q --){
        char str[N]; scanf("%s",str + 1);
        int x = read();
        if(str[1] == 'Q'){
            printf("%d\n",query(out[x]) - query(in[x] - 1));
        } else {
            int val = 1;
            if(a[x] == 1){
                a[x] = 0; val = -1;
            } else {
                a[x] = 1; val =1;
            }
            Update(in[x],val);
        }
    }

}


