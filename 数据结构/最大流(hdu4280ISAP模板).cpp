///链接：http://acm.hdu.edu.cn/showproblem.php?pid=4280
/*题意: 在最西边的点走到最东边的点最大容量。
  题解:ISAP模板题，Dinic过不了。
*/

#include"stdio.h"
#include"string.h"
#include"stack"
#include"map"
#include"math.h"
#include"iostream"
#include"string"
#include"vector"
#include"queue"
#include"algorithm"
using namespace std;
#define OK printf("\n");
#define Debug printf("this_ok\n");
#define INF 1e18
typedef long long ll;
#define scanll(a,b) scanf("%lld%lld",&a,&b);
#define scanl(a) scanf("%lld",&a);
#define printl(a,b) if(b == 0) printf("%lld ",a); else printf("%lld\n",a);
#define print_int(a,b) if(b == 0) printf("%d ",a); else printf("%d\n",a);
typedef pair<int,int> PII;

inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}
const ll mod = 998244353;
const int N = 200000,M = 800000;
const  double pi = acos(-1);
const int inf = 1 << 29;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
int n,m,t,s,tot;
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[N];
int w[N];
queue<int> q;
map<string,int> Q;
void add(int x,int y,int z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = z; Next[tot] = head[y]; head[y] = tot;
}

bool bfs(){
    memset(d,0,sizeof(d));
    while(q.size())q.pop();
    q.push(s); d[s] = 1;
    while(q.size()){
        int x = q.front(); q.pop();
        for(int i = head[x]; i; i = Next[i])
        if(edge[i] && !d[ver[i]]){
            q.push(ver[i]); d[ver[i]] = d[x] + 1;
            if(ver[i] == t) return 1;
        }
    }
    return 0;
}

int dinic(int x,ll flow){
    if(x == t) return flow;
    ll rest = flow,k;
    for(int i = head[x]; i && rest; i = Next[i]){
         if(edge[i] && d[ver[i]] == d[x] + 1){
            k = dinic(ver[i],min(rest,(ll)edge[i]));
            if(!k) d[ver[i]] = 0;
            edge[i] -= k;
            edge[i ^ 1] += k;
            rest -= k;
         }
    }
    return flow - rest;
}
int main(){
    int T = read();
    while(T --){
        n = read(); m = read();
        tot = 1;s = 1; t = 1;
        int tmax = -inf, tmin = inf;
         s = t= 1;
        for(int i = 1; i <= n; i ++) {
            int x = read(),y = read();
            if(x >= tmax) tmax = x, t = i;
            if(x <= tmin) tmin = x, s = i;
            head[i] = 0;
         }
        for(int i = 1; i <= m; i ++){
           int x = read(),y = read(),w = read();
           add(x,y,w);
        }
        ll flow = 0; maxflow = 0;
        while(bfs())
            while(flow = dinic(s,inf)) maxflow += flow;
        printf("%lld\n",maxflow);
    }
}
/*
3
1 2 3
2
2 6
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include <map>
#include <set>
using namespace std;
#define INF 0x3f3f3f3f
#define N 100010
typedef long long LL;
struct Edge {
    int u, v;
    LL cap;
    Edge () {}
    Edge (int u, int v, LL cap) : u(u), v(v), cap(cap) {}
}edge[N*4];
vector<int> G[N];
int dis[N], cur[N], num[N], pre[N], tot, S, T;

void Add(int u, int v, int cap) {
    edge[tot] = Edge(u, v, cap);
    G[u].push_back(tot++);
    edge[tot] = Edge(v, u, cap);
    G[v].push_back(tot++);
}

int BFS() { // 逆向BFS
    memset(dis, -1, sizeof(dis));
    queue<int> que; que.push(T);
    dis[T] = 0;
    while(!que.empty()) {
        int u = que.front(); que.pop();
        for(int i = 0; i < G[u].size(); i++) {
            Edge &e = edge[G[u][i]];
            if(dis[e.v] == -1) {
                dis[e.v] = dis[u] + 1;
                que.push(e.v);
            }
        }
    }
    return ~dis[S];
}

int DFS() { // 通过pre数组回溯更新流量
    int u = T; int flow = INF;
    while(u != S) {
        Edge &e = edge[pre[u]];
        if(e.cap < flow) flow = e.cap;
        u = e.u;
    } u = T;
    while(u != S) {
        Edge& e1 = edge[pre[u]];
        Edge& e2 = edge[pre[u]^1];
        e1.cap -= flow; e2.cap += flow;
        u = e1.u;
    }
    return flow;
}

int ISAP(int n) {
    if(!BFS()) return 0; // 从汇点到源点逆向BFS初始化dis数组
    memset(num, 0, sizeof(num));
    memset(cur, 0, sizeof(cur)); // 当前弧优化
    for(int i = 1; i <= n; i++)
        if(~dis[i]) num[dis[i]]++; // 当前距离为dis[i]的结点数
    int ans = 0, u = S;
    while(dis[S] < n) {
        if(u == T) ans += DFS(), u = S; //  回溯之前的结点并把更新流量
        int flag = 0;
        for(int i = 0; i < G[u].size(); i++) {
            Edge &e = edge[G[u][i]];
            if(dis[e.v] + 1 == dis[u] && e.cap > 0) { // 可以增广
                pre[e.v] = G[u][i]; cur[u] = i;
                flag = 1; u = e.v;
                break;
            }
        }
        if(!flag) { // 不能增广,retreat
            if(--num[dis[u]] == 0) break; // gap优化
            int md = n;
            for(int i = 0; i < G[u].size(); i++) {
                Edge &e = edge[G[u][i]];
                if(e.cap > 0 && dis[e.v] < md) {
                    md = dis[e.v]; cur[u] = i;
                }
            }
            num[dis[u] = md + 1]++;
            if(u != S) u = edge[pre[u]].u;
        }
    }
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        tot = 0; for(int i = 0; i <= n; i++) G[i].clear();
        int u, v, c, west = 100000000, east = -10000000;
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &u, &v);
            if(west > u) west = u, S = i;
            if(east < u) east = u, T = i;
        }
        for(int i = 1; i <= m; i++) {
            scanf("%d%d%d", &u, &v, &c);
            Add(u, v, c); // 无向图的话反向边的cap也是c
        }
        printf("%d\n", ISAP(n));
    }
    return 0;
}
*/
