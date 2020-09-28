///链接：https://www.luogu.com.cn/problem/P3355
/*题意: 一个n*n的棋盘，马走日的规则互相攻击，棋盘有一些点不可放置马，问在都不互相攻击的前提下，能放多少马。
  题解：有点类似网格取数的最小割。
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
const  double pi = acos(-1);
const int inf = 1 << 29;
const int dirx[9] = {-2,-2,2,2,1,1,-1,-1};
const int diry[9] = {-1,1,-1,1,-2,2,-2,2};
int n,m,t,s,tot;
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[M];
queue<int> q;
int id[210][210];


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
    n = read(),m = read();s = n * n + 1; t = s + 1;
    tot = 1;
    for(int i = 1; i <= m;i ++){
        int x = read(),y = read();
        id[x][y] = -1;
    }
    int top1 = 1;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++)
            if(id[i][j] != -1) id[i][j] = (i - 1) * n + j;
    }

    for(int i = 1; i <= n; i ++)
      for(int j = 1; j <= n; j ++){
         if(id[i][j] == -1) continue;
         if(((i + j) & 1) == 0){
            add(s,id[i][j],1);
         } else add(id[i][j],t,1);

         if(((i + j) & 1) == 0)
             for(int k = 0; k < 8; k ++){
                int X = i + dirx[k];
                int Y = j + diry[k];
                if(X < 1 || X > n || Y < 1 || Y > n || id[X][Y] == -1) continue;
                add(id[i][j],id[X][Y],inf);
             }
    }
    ll flow = 0;
    sum = n * n - m;
    while(bfs())
        while(flow = dinic(s,inf)) maxflow += flow;
  //  printf("maxflow = %lld\n",maxflow);
    printf("%lld\n",sum - maxflow);
}
/*
3
1 2 3
2
2 6
*/

