///链接：http://acm.hdu.edu.cn/showproblem.php?pid=4289
/*题意: 无向图，阻止别人从s点到t点，问最少需要多少费用；
  题解：这个和别的最小割有一点不同的地方，就在于这个的最小割是无向图；
        那么我们考虑，无向图最小割，所以我们需要进行拆点；
*/
#include"stdio.h"
#include"string.h"
#include"stack"
#include"map"
#include"math.h"
#include"iostream"
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
const int N = 500,M = 500100;
const ll inf = 1LL << 61;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
int n,m,t,s,tot;
ll maxflow,sum;
int a[N];
int head[N],ver[M],Next[M],d[N];
ll edge[M];
queue<int> q;

void add(int x,int y,ll z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = 0; Next[tot] = head[y]; head[y] = tot;
}

bool bfs(){
    for(int i = 0; i <= n + n; i ++) d[i] = 0;
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

ll dinic(int x,ll flow){
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
    while(~scanf("%d%d",&n,&m)){

        tot = 1; for(int i = 0; i <= n + n;i ++) head[i] = 0;
        s = n + n + 1; t = n + 1;
        int x = read(),y = read();
        add(s,x,inf); add(y + n,t,inf);
        for(int i = 1; i <= n; i ++) {
            int x = read();
            add(i,i + n,x);
        }
        for(int i = 1; i <= m; i ++){
            int x = read(),y = read();
            add(x + n,y,inf);
            add(y + n,x,inf);
        }
        ll flow = 0;
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
*/
