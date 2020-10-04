///链接：https://ac.nowcoder.com/acm/contest/7831/H
/*题意：n结点树，每个结点有一颜色，两种操作，1，查询包含所有x颜色的结点最起码要多少条边
        2，修改v顶点颜色改为x；
  题解：对每种颜色的点用一个set来存，set的排序规则按照dfs序，能发现每修改一个点的颜色
  对该颜色的答案的贡献只和其在set中前后的两个点l,r有关，set中增加一个点x对答案的贡献为
  dis(l,x)+dis(x,r)−dis(l,r)，删除一个点对答案的贡献为dis(l,r)−dis(l,x)−dis(x,r)，能发
  现这样得到的每个颜色的答案再加上set中第一个点start和最后一个点end之间的距离
  dis(start,end)刚好是正确答案的两倍。对与每个询问答案的操作输出(ans[i]+dis(start,end))/2。
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
int n,m,a[N],dfn[N],top;
int f[N][22],d[N],dist[N],t;
int ans[N];
queue<int> q;
struct cmp{
    bool operator()(const int &x,const int &y) const {
        return dfn[x] < dfn[y];
    }
};
set<int,cmp> G[N];

void add(int x,int y){
    ver[++ tot] = y; Next[tot] = head[x]; head[x] = tot;
}

void bfs(){
    q.push(1); d[1] = 1;
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = Next[i]){
            int y = ver[i];
            if(d[y]) continue;
            d[y] = d[x] + 1;
            dist[y] = dist[x] + 1;
            f[y][0] = x;
            for(int j = 1; j <= t; j ++)
                f[y][j] = f[f[y][j - 1]][j - 1];
            q.push(y);
        }
    }
}
int lca(int x,int y){
    if(d[x] > d[y]) swap(x,y);
    for(int i = t; i >= 0;i --)
        if(d[f[y][i]] >= d[x]) y = f[y][i];
    if(x == y) return x;
    for(int i = t; i >= 0;i --)
        if(f[x][i] != f[y][i]) x = f[x][i],y = f[y][i];
    return f[x][0];
}
int dis(int x,int y){
	return d[x]+d[y]-2*d[lca(x,y)];
}
void dfs(int x,int f){
    dfn[x] = ++ top;
    for(int i = head[x]; i; i = Next[i]){
        int y = ver[i];
        if(y == f) continue;
        dfs(y,x);
    }
}
void Add(int x){
    G[a[x]].insert(x);
    auto it = G[a[x]].find(x);
    int l = 0,r = 0;
    ++ it;
    if(it != G[a[x]].end()){
        r = *it;
    }
    -- it;
    if(it != G[a[x]].begin()){
        -- it;
        l = *it;
    }
    if(l && r) ans[a[x]] -= dis(l,r);
    if(l) ans[a[x]] += dis(l,x);
    if(r) ans[a[x]] += dis(x,r);
}
void Del(int x){
    auto it = G[a[x]].find(x);
    int l = 0,r = 0;
    ++ it;
    if(it != G[a[x]].end()) r = *it;
    -- it;
    if(it != G[a[x]].begin()){
        -- it;
        l = *it;
    }
    if(l && r) ans[a[x]] += dis(l,r);
    if(l) ans[a[x]] -= dis(l,x);
    if(r) ans[a[x]] -= dis(x,r);
    G[a[x]].erase(x);
}
int main(){
    n = read(); t = (int)(log(n)/log(2)) + 1;
    for(int i = 2;i <= n; i ++){
        int x = read(),y = read();
        add(x,y); add(y,x);
    }
    bfs();dfs(1,0);
    for(int i = 1; i <= n; i ++) {
        a[i] = read();
        Add(i);
    }
    m = read();
    while(m --){
        char str[2]; scanf("%s",str);
        if(str[0] == 'Q') {
            int x = read();
            if(G[x].empty()) printf("-1\n");
            else if(G[x].size() == 1) printf("%d\n",ans[x]);
            else printf("%d\n",(ans[x] + dis(*G[x].begin(),*G[x].rbegin()))/2);
        } else {
            int x = read(),y = read();
            Del(x);a[x] = y;
            Add(x);
        }
    }
}


