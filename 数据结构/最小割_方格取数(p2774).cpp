///链接：https://www.luogu.com.cn/problem/P2774
/*题意: 每个点有一个权值，n*m的网格，现在从其中选数要和最大，选取的格点不能有公共边；
  题解: 每相邻的两格点不能同时选取，观察n和m的范围，可得知此算法的复杂度应该是比较大的；
  考虑网络流，网络流在格点问题上，一般把其分为黑白两种格点颜色；
  假设起点连接黑点，终点连接白点，并根据上下左右进行格点之间的连线
  那么现在的问题就转变为在构建的图中，如果选择了对应了黑点，则不能选择与其相连接的白点；
  同最小割问题了，可是现在我们要选取的数是要求和最大；所以我们需要用sum-最小割
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
const int N = 50010,M = 300010;
const  double pi = acos(-1);
const int inf = 1 << 29;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
int n,m,t,s,tot;
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[N];
queue<int> q;

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
    n = read(),m = read();s = n * m + m + 1; t = n * m + m + 2;
    tot = 1;
    for(int i = 1; i <= n; i ++)
      for(int j = 1; j <= m; j ++){
         int x = read(); sum += x;
         if(((i + j) & 1) == 0){
            add(s,i * m + j,x);
         } else add(i * m + j,t,x);
         if(((i + j) & 1) == 0)
             for(int k = 0; k < 4; k ++){
                int X = i + dirx[k];
                int Y = j + diry[k];
                if(X < 1 || X > n || Y < 1 || Y > m) continue;
                add(i * m + j,X * m + Y,inf);
             }
    }
    ll flow = 0;
    while(bfs())
        while(flow = dinic(s,inf)) maxflow += flow;
    printf("%lld\n",sum - maxflow);
}
/*
3
1 2 3
2
2 6
*/
