///链接：https://www.luogu.com.cn/problem/P2754
/*题意: n太空站，m飞船，每个飞船有以一固定且循环的航线，每一秒能移动一步，现在问你最起码要多少秒，才能把地球上的
        k个人转移到月球上去。
  题解：首先无解的情况，地球和月球之间没有路线，那么直接输出0；现在要考虑的是有解的情况。
  这里我们需要按照时间进行分层，即第一秒的时候图是怎么样的，跑下最大流，看最大流是否大于等于k。如果是，则直接退出；
  如果不是，则就证明当前时间还不满足，我们就看s+1秒的时候的最大流。直到满足最大流大于等于k。
  按时间建的分层图；有东西。
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
int far[220];
int ans;
void add(int x,int y,int z){
    ver[++ tot] = y; Next[tot] = head[x];  edge[tot] = z; head[x] = tot;
    ver[++ tot] = x; edge[tot] = 0; Next[tot] = head[y]; head[y] = tot;
}
int Find(int x){
    if(x == far[x]) return x;
    return far[x] = Find(far[x]);
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
    for(int i = 0; i <= 200; i ++) far[i] = i;
    for(int i = 1; i <= m; i ++){
       //w[i] = read();len[i] = read();
       scanf("%d%d",&w[i],&len[i]);
       int fx = 0;
       for(int j = 0; j < len[i]; j ++){
//          G[i][j] = read();
          scanf("%d",&G[i][j]);
          if(G[i][j] == -1) G[i][j] = n + 2;
          if(G[i][j] == 0) G[i][j] = n + 1;
          if(j == 0) continue;

          int fy = Find(G[i][j]);
          int fx = Find(G[i][j - 1]);
          if(fx != fy) far[fx] = fy;

       }
    }
    if(Find(n + 1) != Find(n + 2))
    {printf("0\n"); return 0;}

    ///地球n+1，月球n+2 起点n+3，源点n+4
    s = 0; t = 999;
    int eq = n + 1,mq = n + 2;
    tot = 1;
    ans = 0; int tt = n + 2;
    while(ans >= 0){
        add(s,ans * tt + eq,inf);
        add(ans * tt + mq,t,inf);
        if(ans != 0){
            for(int i = 1; i <= n + 2; i ++)
                add((ans - 1) * tt + i,ans * tt + i,inf);
            for(int i = 1; i <= m; i ++){
                int x = G[i][(ans - 1)%len[i]];
                int y = G[i][ans%len[i]];
                add((ans - 1) * tt + x,ans * tt + y,w[i]);
                //printf("i = %d m = %d\n",i,m);
            }//printf("ok");
        }
        ll flow = 0,s1 = 0;
        while(bfs())
          while(flow = dinic(s,inf)) s1 += flow;
        sum += s1;
        if(sum >= k) break;
        ans ++;
       // printf("ans = %d\n",ans);
    }
    //if(ans == 101) printf("0\n");
     printf("%d\n",ans);
}
/*
3
1 2 3
2
2 6
*/
