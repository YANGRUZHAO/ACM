///链接：https://vjudge.net/problem/UVA-10480
/*题意: n个结点，m路径，现在让1和2号结点不要连接，破坏一条路径的花费为k。
  题解：最小割，输出路径的话，x和y一开始有路径，x只和1号点连接，y只和2号点连接，那么就是割边。
  鉴于此，本题我们用邻接矩阵存储更为方便；
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
#define INF 0x3f3f3f3f
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
const int maxn=1e3+10;
int n,m;
int mp[maxn][maxn];//初始流量
int flow[maxn][maxn];//最大流
int path[maxn];//记录路径
int a[maxn];//i点在最大流中的流量
int start,End;
int x[maxn],y[maxn];
int maxflow()
{
    queue<int> q;
    memset(flow,0,sizeof flow);
    int max_flow=0;
    while(true){
        memset(a,0,sizeof a);//清空标记
        a[start]=INF;//源点权值无限大
        while(!q.empty())   q.pop();
        q.push(start);
        while(!q.empty()){
            int temp=q.front();
            q.pop();
            for(int i=1;i<=n;i++){
                //未走过且流量小于他的权值
                if(!a[i]&&flow[temp][i]<mp[temp][i])
                {
                    path[i]=temp;//记录前一个点
                    a[i]=min(a[temp],mp[temp][i]-flow[temp][i]);
                    q.push(i);
                }
            }

        }
        if(a[End]==0)   break;
        //更新剩余网络
        for(int i=End;i!=start;i=path[i]){
            flow[path[i]][i]+=a[End];//反向边加
            flow[i][path[i]]-=a[End];//正向边减
        }
        max_flow+=a[End];
    }
    return max_flow;
}
int main()
{
    while(~scanf("%d%d",&n,&m)){
        if(n == 0) break;
        memset(mp,0,sizeof mp);
        for(int i=1;i<=m;i++)
        {
            int u = read(),v = read(),w = read();
            mp[u][v]=mp[v][u]=w;///无向路径
            x[i]=u; y[i]=v;
        }
        start=1;End=2;
        int flow=maxflow();
        for(int i=1;i<=m;i++){//枚举每一条边的两个点
            //有一点的权值为0，说明当前点被删除
            if((!a[x[i]]&&a[y[i]])||(a[x[i]]&&!a[y[i]]))
            printf("%d %d\n",x[i],y[i]);
        }
        printf("\n");
    }
    return 0;
}
