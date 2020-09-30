///链接：http://poj.org/problem?id=2987
/*参考博客：https://blog.csdn.net/can919/article/details/77603353
   有一个有向图，每一个点都有一个权值（可以为正或负或0），选择一个权值和最大的子图，使得每个点的后继都在子图里面，这个子图就叫最大权闭合子图。
  题意: 裁员有收益，收益可为正或者负数，同时有个附属关系，如果裁k，那么k的小弟都要被裁；问怎么裁员收益最高；
  题解: 最大收益直接跑最大权闭合子图就好了。注意到是裁员有收益，所以最终残留网络上留下来的点都是要裁掉的；
  直接在上面统计即可
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

inline int read(int &x){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
   x = s * w;
   return 0;
}
const ll mod = 998244353;
const int N = 50010,M = 300010;
const  double pi = acos(-1);
const int inf = 1 << 29;
const int dirx[4] = {-1,0,1,0};
const int diry[4] = {0,1,0,-1};
int n,m,t,s,tot;
int ans[N];
ll maxflow,sum;
int head[N],ver[M],Next[M],edge[M],d[N];
int cnt1 = 0;
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
        s = n + 1; t = s + 1;
        for(int i = 0; i <= t; i ++) head[i] = 0;
        tot = 1; sum = 0;
        for(int i = 1; i <= n; i ++){
           read(ans[i]);
           if(ans[i]>0){
            sum += ans[i];
            add(s,i,ans[i]);
           } else {
               add(i,t,-ans[i]);
           }
        }
        for(int i = 1; i <= m; i ++){
            int x,y; read(x); read(y);
            add(x,y,inf);
        }
        ll flow = 0; maxflow = 0;
        while(bfs())
            while(flow = dinic(s,inf)) maxflow += flow;
        //    printf("sum = %lld\n",sum);
        cnt1 = 0;
        for(int i = 1; i <= n; i ++)
            if(d[i]) cnt1 ++;
        printf("%d ",cnt1);
        printf("%lld\n",sum - maxflow);
    }
}
/*
3
1 2 3
2
2 6
*/
