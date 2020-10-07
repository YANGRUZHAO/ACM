///链接：http://poj.org/problem?id=3281
/*题意: n头牛，m菜，k饮料，菜和饮料一份只能给一头牛，每头牛有固定食谱只吃喝上面有的。每头牛要么不吃不喝，要么有吃有喝，问最多能有几头牛有吃有喝？
  题解：牛拆点拆成in和out，in和out连边，食物向可以吃他的牛连边，牛向所有可以喝的饮料连边，源点向所有食物连边，饮料向汇点连边，所有边权都为1，跑最大流。
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
const int N = 500010,M = 500010;
const int inf = 1 << 29;
const int maxn=1e5;

int n,m,t,s,tot;
ll maxflow;
int head[N],ver[M],Next[M],d[N];
ll edge[M];
char str[210][210];
queue<int> q;

void add(int x,int y,ll z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = 0; Next[tot] = head[y]; head[y] = tot;
}

bool bfs(){
    for(int i = 0; i <= t; i ++) d[i] = 0;
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
    while(~scanf("%d",&n)){
        int a = read(); int b = read();memset(head,0,sizeof(head));
    t = 2 * n + a + b + 1;s = t + 1;  tot = 1;maxflow = 0;
        for(int i = 1; i <= n; i ++){
            add(i,i + n,1);
            //add(s,i,1); add(i + a + b,t,1);
        }
        for(int i = 1; i <= a; i ++){
            int x = read();
            add(s,i + 2 * n,x);
        }
        for(int i = 1; i <= b; i ++){
            int y = read();
            add(i + 2 * n + a,t,y);
        }

        for(int i = 1; i <= n; i ++){
            scanf("%s",str[i] + 1);
            for(int j = 1; j <= a; j ++){
                if(str[i][j] == 'Y'){
                    add(j + 2 * n,i,1);
                }
            }
        }
        for(int i = 1; i <= n; i ++){
            scanf("%s",str[i] + 1);
            for(int j = 1; j <= b; j ++){
                if(str[i][j] == 'Y'){
                    add(i + n,j + 2 * n + a,1);
                }
            }
        }
        ll flow = 0;
        while(bfs())
            while(flow = dinic(s,inf)) maxflow += flow;
      //  printf("maxflow = %lld\n",maxflow);
        printf("%lld\n",maxflow);
    }
}
/*
3
1 2 3
2
2 6
*/

