///���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=3605
/*����: n����ҪǨ�㵽m��������ȥ��ͬʱÿ���˶��ԣ�m���������в���������һ������ȥ�ġ�������������n
  �����Ƿ���Ǩ�㵽m��������ȥ��
  ��⣺1��ɵ���������������t��������Ϊ����������ÿ�������ʺ�ס����������Ϊ1��ÿ���������s������Ϊ1��
  �ã���ʱ����ɵ�ƣ�
  �����ݷ�Χ1<=n<=100000,1<=m<=10;
  �϶���ʱ�ˣ��������ǿ�����������������;ע�⵽���ֻ��10����������Ҳ����˵��������ѡ���״̬
  ״̬���ֻ��1<<m��;Ҳ����1024��;
  �������ǿ��Կ���ͨ��������״ѹ����ʹ����ٵ���;
  ״ѹ֮������Ӧ�ð�s��ÿ��״̬�����ӣ�����Ϊ��״̬��������ÿ��״̬���������ӣ�����Ϊ��״̬��������
  ÿ�������t���ӣ�����Ϊ��������������������������ɣ�
  ���ԣ�����������Ĺ����У���ʱ��Ҫ�࿼��һ����ô��������ģ����ͬ���Ĺ�ģ��������
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
const int N = 500010,M = 1200010;
const int inf = 1 << 29;
const int maxn=1e5;

int n,m,t,s,tot;
ll maxflow;
int head[N],ver[M],Next[M],d[N];
ll edge[M];
int cnt[2010];
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
    while(~scanf("%d",&n)){
       m = read(); memset(head,0,sizeof(head));
       s = 0; t = 2000 + m + 1;  tot = 1;maxflow = 0;
       memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++){
				int tmp=0,fg;
				for(int j=1;j<=m;j++){
					int x = read();
                    if(x == 1)
						tmp|=(1<<(j-1));
					}

				cnt[tmp]++;
        }
        for(int i = 1; i <= 2000; i ++){
            if(cnt[i] == 0) continue;
            add(s,i,cnt[i]);
            for(int j = 1; j <= m; j ++){
                if((i & (1LL << (j - 1)))){
                    add(i,2000 + j,cnt[i]);
                }
            }
        }
        for(int  i = 1; i <= m; i ++){
            int x = read();
            add(i + 2000,t,x);
        }

        ll flow = 0;
        while(bfs())
            while(flow = dinic(s,inf)) maxflow += flow;
     //   printf("maxflow = %lld\n",maxflow);
        if(maxflow == n) printf("YES\n");
        else printf("NO\n");
    }
}
/*
3
1 2 3
2
2 6
*/

