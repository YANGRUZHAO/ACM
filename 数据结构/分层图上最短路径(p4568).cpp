///链接：https://www.luogu.com.cn/problem/P4568
/*题意: n点m条边，问s到t的最短路径，可使用k次瞬移技能，则当前边长度变为0；
  题解：分层图上最短路径；每层都是原图，同时第i层有权值为0的边连到第i+1层，表示使用了一次瞬移技能。
        注意到此题是可以把最多k条边的权值变为0；
        问题延申：则我们可以计算把最多k条边权值变为当前边的一半或者其他值；
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
#define ll long long
#define PII pair<int,int>
using namespace std;
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}

const int INF = 1e9 + 7;
const int N = 20010,M = 3000100;
int head[13 * N],ver[M],edge[M],Next[M],tot;
int n,m,k,s,t;
int dist[N * 13];
int vis[N * 13];

void add(int u,int v,int w){
    ver[++ tot] = v; edge[tot] = w;
    Next[tot] = head[u]; head[u] = tot;
}

struct com{
    bool operator()(const PII &t1,const PII &t2)
    {
        return t1.second > t2.second ;
    }
};
void dfs(){
    priority_queue<PII,vector<PII>,com> Q;
    Q.push({s,0});
    for(int i = 0; i <= n * k + n; i ++) dist[i] = INF;
    dist[s] = 0;
    while(!Q.empty()){
        PII p = Q.top(); Q.pop();
        int u = p.first;
        int w = p.second;
        if(dist[u] != w) continue;
        if(vis[u] == 1) continue;
        vis[u] = 1;
        for(int i = head[u]; i; i = Next[i]){
            int v = ver[i];
            int val = edge[i];
            if(dist[v] > w + val){
                dist[v] = w + val;
                Q.push({v,dist[v]});
            }
        }
    }
}

int main(){

    n = read(); m = read(); k = read();
    s = read(); t = read();
    s ++;t ++;
    for(int i = 1; i <= m; i ++){
        int a,b,c;
        a = read(); b = read(); c = read();
        a ++; b ++;
        for(int j = 0; j <= k; j ++){
            add(j * n + a,j * n + b,c);
            add(j * n + b,j * n + a,c);
            if(j < k){
                add(j * n + a,(j + 1) * n + b,0);
                add(j * n + b,(j + 1) * n + a,0);
            }
        }
    }
    dfs();
    int ans = INF;
    for(int i = 0; i <= k; i ++)
        ans = min(ans,dist[i * n + t]);
    printf("%d\n",ans);
}
