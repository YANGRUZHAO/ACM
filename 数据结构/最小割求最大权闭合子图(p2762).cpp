///���ӣ�https://www.luogu.com.cn/problem/P2774
/*�ο����ͣ�https://blog.csdn.net/can919/article/details/77603353
   ��һ������ͼ��ÿһ���㶼��һ��Ȩֵ������Ϊ���򸺻�0����ѡ��һ��Ȩֵ��������ͼ��ʹ��ÿ����ĺ�̶�����ͼ���棬�����ͼ�ͽ����Ȩ�պ���ͼ��
  ����: ̫�շ��мƻ���
  ���: ���պ���ͼ��Ŀ�����ǽ�ͼ�е��Ѷȣ�ͬʱ���뵽�����պ���ͼҲ���е��ѵģ�
  ע��������������һ���d�������ܲ�������õ��ģ��������d�����б�ǣ���ô֤��һ������·������i���ģ�
  ���ԣ���С������i��t�������·����
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
//����ֵ�������Ƿ�����
//��ʵ�ö����³���Ի������ã������ĩ�пո��GG��
    char c;x=0;
    while(c<'0'||c>'9')c=getchar();
    while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return c=='\r'||c=='\n'?0:1;
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
    read(n);read(m);s = n + m + 1; t = s + 1;
    tot = 1; ll sum = 0;
    for(int i = 1; i <= n; i ++){
       int x;
       read(x); sum += x;
       add(s,i,x);
       while(x){
         int w;
         x = read(w); add(i,n + w,inf);
       }
    }
    for(int i = 1; i <= m; i ++){
        int x;read(x);
        add(n + i,t,x);
    }
    ll flow = 0;
    while(bfs())
        while(flow = dinic(s,inf)) maxflow += flow;
  /*  int tot1 = 0;
    for(int i = head[s]; i; i = Next[i]){
        if(edge[i]){
            printf("%d ",ver[i]);
        }
    }
    printf("\n");
    for(int i = n + 1; i <= n + m; i ++){
        for(int j = head[i]; j; j = Next[j]){
            int y = ver[j];
            if(y != t) continue;
            if(edge[j] == 0){
                printf("%d ",i - n);
            }
            break;
        }
    }printf("\n");
    */
    	for(int i = 1; i <= n; i++)
		if(d[i]) printf("%d ", i);
	puts("");
	for(int i = 1; i <= m; i++)
		if(d[i + n]) printf("%d ", i);printf("\n");
    printf("%lld\n",sum - maxflow);
}
/*
3
1 2 3
2
2 6
*/
