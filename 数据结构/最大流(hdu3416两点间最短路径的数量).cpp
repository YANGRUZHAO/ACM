///链接：http://acm.hdu.edu.cn/showproblem.php?pid=4280
/*题意: 两点A和B点间最短路径的数量
  题解: 求出A点到每个点的长度A[i],求出B点到每个点的长度B[i]；
  然后在此遍历边，如果满足A[i] + B[i] + w == 最短路径，那么就建边进去。
  最后跑最大流即可。
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

typedef struct Edge{
    int x,y,w;
    Edge(){}
    Edge(int a,int b,int c){
        x = a; y = b; w = c;
    }
}Edge;
int n,m,t,s,tot;
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[N];
int w[N];
queue<int> q;
Edge A[N];int top;
vector<PII> G[N];
int dist[N][2];

void add(int x,int y,int z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = 0; Next[tot] = head[y]; head[y] = tot;
}

bool bfs(){
    memset(d,0,sizeof(d));
    while(q.size())q.pop();
    q.push(s); d[s] = 1;
    while(q.size()){
        int x = q.front(); q.pop();// Debug
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
struct node{
    int x,w;
    node(){}
    node(int a,int b){
        x = a; w = b;
    }
    friend bool operator < (node a,node b){
        return a.w > b.w;
    }
};
void bfs1(int x,int id){
    priority_queue<node>Q;
    Q.push({x,0});
    dist[x][id] = 0;
    while(!Q.empty()){
       node B = Q.top(); Q.pop();
       int x = B.x,w = B.w;
       for(int i = 0; i < G[x].size(); i ++){
           int y = G[x][i].first,d = G[x][i].second;
           if(dist[y][id] <= w + d) continue;
           dist[y][id] = w + d;
          // printf("x = %d y = %d w = %d d = %d\n",x,y,w,d);
           Q.push({y,dist[y][id]});
       }
    }
}
void init(){
    for(int i = 0; i <= n; i ++) {
        dist[i][0] = dist[i][1] = inf;
        G[i].clear(); head[i] = 0;
    }
}
int main(){
    int T = read();
    while(T --){
        n = read(); m = read();
        tot = 1;
        init();
        for(int i = 1; i <= m; i ++){
            A[i].x = read(); A[i].y = read(); A[i].w = read();
         //   printf("check %d %d %d\n",A[i].x,A[i].y,A[i].w);
            G[A[i].x].push_back({A[i].y,A[i].w});
         //   G[A[i].y].push_back({A[i].x,A[i].w});
        }
        s = read(); t = read();
        bfs1(s,0);
        for(int i = 0; i <= n; i ++){
            G[i].clear();
        }
        for(int i = 1; i <= m; i ++){
            G[A[i].y].push_back({A[i].x,A[i].w});
        }
        bfs1(t,1);
        /*for(int i = 1; i <= n; i ++){
            printf("%d ",dist[i][0]);
        }OK;
        for(int i = 1; i <= n; i ++){
            printf("%d ",dist[i][1]);
        }OK;*/
        for(int i = 1; i <= m; i ++){
           int x = A[i].x,y = A[i].y,w = A[i].w;
           if(dist[x][0] + dist[y][1] + w == dist[t][0]){
              add(x,y,1); //printf("x = %d y = %d\n",x,y);
           }
        }

        ll flow = 0; maxflow = 0;
        while(bfs())
            while(flow = dinic(s,inf)) maxflow += flow;
        printf("%lld\n",maxflow);
    }
}
