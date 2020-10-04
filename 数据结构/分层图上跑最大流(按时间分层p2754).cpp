///链接：https://www.luogu.com.cn/problem/P2754
/*题意: n根柱子，现在依次放1-x的数，柱子上相邻的两个数的和要是完全平方数，现在问你能放多少个数，并输出方案
  题解：注意到依次放数，所以对于每个数来说只有两种可能，要么放到别的数的后面，要么自己重新开一根柱子
        所以我们可能在当前是放到了别的数后面，但是后面有可能会发现单独开一根柱子才是最优的；
        这就是一个反悔的过程；对于这个反悔的过程我们利用网络流来解决，因为网络流是有个反向边的；
        同时，此题必要拆点；
        注意：我的最大流模板跑不过去，全wa，但是别人的可以； 吐了
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
const int N = 1000010,M = 1000010;
const int inf = 1 << 29;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
int n,m,t,s,tot;
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[N];
queue<int> q;
int w[220],len[220];
int G[210][210];
int ans;
void add(int x,int y,int z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = 0; Next[tot] = head[y]; head[y] = tot;
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
    //n = read(); m = read();
    int k; // = read();
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 1; i <= n; i ++){
       //w[i] = read();len[i] = read();
       scanf("%d%d",&w[i],&len[i]);
       for(int j = 0; j < len[i]; j ++){
//          G[i][j] = read();
          scanf("%d",&G[i][j]);
          if(G[i][j] == -1) G[i][j] = n + 2;
          if(G[i][j] == 0) G[i][j] = n + 1;
       }
    }//printf("0\n"); return 0;

    ///地球n+1，月球n+2 起点n+3，源点n+4
    s = 0; t = 999;
    int eq = n + 1,mq = n + 2;
    tot = 1;
    ans = 0; int tt = n + 2;
    while(ans <= 100){
        add(s,ans * tt + eq,inf);
        add(ans * tt + mq,t,inf);
        if(ans != 0){
            for(int i = 1; i <= n + 2; i ++)
                add((ans - 1) * tt + i,ans * tt + i,inf);
            for(int i = 1; i <= m; i ++){
                int x = G[i][(ans - 1)%len[i]];
                int y = G[i][ans%len[i]];
                add((ans - 1) * tt + x,ans * tt + y,w[i]);
            }
        }
        ll flow = 0,s1 = 0;
        while(bfs())
          while(flow = dinic(s,inf)) s1 += flow;
        sum += s1;
        if(sum >= k) break;
        ans ++;
    }
    if(ans == 101) printf("0\n");
    else printf("%d\n",ans);
}
/*
3
1 2 3
2
2 6
*/


