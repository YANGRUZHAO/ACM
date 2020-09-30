///链接：https://www.luogu.com.cn/problem/P2765
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
const int N = 500010,M = 500010;
const  double pi = acos(-1);
const int inf = 1 << 29;
const int dirx[9] = {-2,-2,2,2,1,1,-1,-1};
const int diry[9] = {-1,1,-1,1,-2,2,-2,2};
const int maxn=1e5;
int id[210],tot1;
int to1[N];


int n,all=0,num=0,nxt[maxn],to[maxn],head[maxn],d[maxn];
int w[maxn],cnt=1,s=0,t=50003,re[maxn],xia[maxn],vis[maxn];
    queue<int>q;
    void add(int x,int y,int we)
    {
        nxt[++cnt]=head[x];head[x]=cnt;to[cnt]=y;w[cnt]=we;
        nxt[++cnt]=head[y];head[y]=cnt;to[cnt]=x;w[cnt]=0;
    }
    int bfs()
    {
        while(q.size()) q.pop();q.push(s);
        memset(d,0,sizeof(d));d[s]=1;
        while(q.size())
        {
            int x=q.front();q.pop();
            for(int i=head[x];i;i=nxt[i])
            {
                int u=to[i];
                if(d[u]||w[i]<=0) continue;
                d[u]=d[x]+1;
                q.push(u);
            }
        }
        return d[t];
    }
    int dfs(int x,int flow)
    {
        if(x==t) return flow;
        int k;
        for(int i=head[x];i;i=nxt[i])
        {
            int u=to[i];
            if(d[u]!=d[x]+1||w[i]<=0) continue;
            if(k=dfs(u,min(w[i],flow)))
            {
                w[i]-=k;w[i^1]+=k;
                if(u!=t) xia[x>>1]=u>>1;
                return k;
            }
        }
        return 0;
    }
    int dinic()
    {
        int k=0;
        while(bfs())
        {
            while(1)
            {
                int p=dfs(s,1e9);
                if(!p) break;
                k+=p;
            }
        }
        return k;
    }
int main(){
    n = read(),s = 0; t = 50003;
    int flow = 0; int num = 0;
    for(int i = 1; ; i ++){
       add(s,i * 2,1); add(i * 2 + 1,t,1);
       /*for(int j = 1; j < i; j ++){
          int sum = i + j;
          if(sqrt(sum) * sqrt(sum) == sum){
            add(j * 2,i * 2 + 1,1);
          }
       }*/
       num = i;
        for(int j=sqrt(num)+1;j*j<2*num;++j)
            add((j*j-num)<<1,(num<<1)|1,1);
       flow = dinic();
       if(!flow) {
          id[++ tot1] = i;
       }
       if(tot1 > n) {
         num = i;    break;
       }
    }
    printf("%d\n",num - 1);
    for(int i = 1; i < num; i ++){
        for(int j = head[i * 2]; j;j = nxt[j]){
            if(w[j] == 0){
                to1[i] = to[j] / 2; break;
            }
        }
    }
    for(int i = 1; i <= n; i ++){
        int k = id[i];
        while(to1[k] != 0){
            printf("%d ",k); k = to1[k];
        }
        printf("%d\n",k);
    }
}
/*
3
1 2 3
2
2 6
*/

