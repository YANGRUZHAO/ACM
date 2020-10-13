///链接：http://acm.hdu.edu.cn/showproblem.php?pid=3081
/*题意:
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
int far[N];
vector<int> G[N],g[220];
int P[110][110];

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
int Find(int x){
    if(x == far[x]) return x;
    return far[x] = Find(far[x]);
}
int check(int x){
    memset(head,0,sizeof(head)); tot = 1;
    for(int i = 1; i <= n; i ++){
        add(s,i,x); add(i + n,t,x);
    }
    for(int i = 1; i <= n; i ++){
        int fx = Find(i);
        for(int j = 1; j <= n; j ++){
            if(P[fx][j] == 0) continue;
            add(i,j + n,1);
        }
    }
    ll flow = 0; maxflow = 0;
    while(bfs())
        while(flow = dinic(s,inf)) maxflow += flow;
   // printf("%lld x\n",maxflow);
    return maxflow == x * n;
}
int main(){
    int T = read();
    while(T --){
        n = read(); m = read(); int f = read();
        memset(P,0,sizeof(P));
        tot = 1;s = n + n + 1; t = s + 1;
        for(int i = 0; i <= n + n + 5; i ++) {
                far[i] = i; G[i].clear(); g[i].clear();
        }
        for(int i = 1; i <= m; i ++){
            A[i].x = read(); A[i].y = read();
            g[A[i].x].push_back(A[i].y);
        }
        for(int i = 1; i <= f; i ++){
            int x = read(),y = read();
            int fx = Find(x),fy = Find(y);
            if(fx == fy) continue;
            far[fx] = fy;
        }
        for(int i = 1; i <= n; i ++){
            far[i] = Find(i);
        }
        for(int i = 1; i <= n; i ++){
            int fx = far[i];
            for(int j = 0; j < g[i].size(); j ++)
                P[fx][g[i][j]] = 1;
        }

        int l = 0,r = n;
        int ans = 0;
        while(l <= r){
            int mid = (l + r) >> 1;
            if(check(mid) == 1){
                l = mid + 1; ans = mid;
            } else r = mid - 1;
        }
        printf("%d\n",ans);

    }
}
