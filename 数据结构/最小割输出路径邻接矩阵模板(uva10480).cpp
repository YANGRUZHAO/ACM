///���ӣ�https://vjudge.net/problem/UVA-10480
/*����: n����㣬m·����������1��2�Ž�㲻Ҫ���ӣ��ƻ�һ��·���Ļ���Ϊk��
  ��⣺��С����·���Ļ���x��yһ��ʼ��·����xֻ��1�ŵ����ӣ�yֻ��2�ŵ����ӣ���ô���Ǹ�ߡ�
  ���ڴˣ������������ڽӾ���洢��Ϊ���㣻
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
int mp[maxn][maxn];//��ʼ����
int flow[maxn][maxn];//�����
int path[maxn];//��¼·��
int a[maxn];//i����������е�����
int start,End;
int x[maxn],y[maxn];
int maxflow()
{
    queue<int> q;
    memset(flow,0,sizeof flow);
    int max_flow=0;
    while(true){
        memset(a,0,sizeof a);//��ձ��
        a[start]=INF;//Դ��Ȩֵ���޴�
        while(!q.empty())   q.pop();
        q.push(start);
        while(!q.empty()){
            int temp=q.front();
            q.pop();
            for(int i=1;i<=n;i++){
                //δ�߹�������С������Ȩֵ
                if(!a[i]&&flow[temp][i]<mp[temp][i])
                {
                    path[i]=temp;//��¼ǰһ����
                    a[i]=min(a[temp],mp[temp][i]-flow[temp][i]);
                    q.push(i);
                }
            }

        }
        if(a[End]==0)   break;
        //����ʣ������
        for(int i=End;i!=start;i=path[i]){
            flow[path[i]][i]+=a[End];//����߼�
            flow[i][path[i]]-=a[End];//����߼�
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
            mp[u][v]=mp[v][u]=w;///����·��
            x[i]=u; y[i]=v;
        }
        start=1;End=2;
        int flow=maxflow();
        for(int i=1;i<=m;i++){//ö��ÿһ���ߵ�������
            //��һ���ȨֵΪ0��˵����ǰ�㱻ɾ��
            if((!a[x[i]]&&a[y[i]])||(a[x[i]]&&!a[y[i]]))
            printf("%d %d\n",x[i],y[i]);
        }
        printf("\n");
    }
    return 0;
}
