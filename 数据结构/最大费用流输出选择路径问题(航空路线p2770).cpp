///���ӣ�https://www.luogu.com.cn/problem/P2770
/*����: ����һ�ź���ͼ�������Ǵ������ң���1�ŵ���һ����·��n�ŵ㣬Ȼ���ڴ�n�ŵ����������·���Ķ��㲻�����ظ��ߣ�
       ���Ƿ����һ������ඥ���·����������·��
  ��⣺�����������������������·��1-n-1������������1-n��·�������ǵ���һ�㣬�ͻᷢ�ֽ�ͼҲ���Ǻ����ˡ�
        ÿ��������һ�Σ����ǲ��֮������Ϊ1��
        ������һ���ط����˺þ�bug�������·����ʱ��û��ע�⵽����ߣ�ͬʱ����ߵ������ǲ����ġ�
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include"set"
#include"string"
#include"map"
using namespace std;
typedef long long ll;

inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}
const int inf=1e9;
const int N=300,M=N*N+N+7,E=500005;
int ver[E], edge[E], Next[E], head[E];
map<string,int> Q;
int cost[E],d[M];
string str[N];
int incf[M], pre[M], v[M],vis[N];
ll ans;
int n, k, tot, s, t, maxflow,m,q[E];
int store1[N],store2[N],store[N][N];
int out[N << 1],top;


void add(int x, int y, int z, int c) {
	// ����ߣ���ʼ����z����λ����c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// ����ߣ���ʼ����0����λ����-c��������ߡ��ɶԴ洢��
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}


bool spfa() {
	queue<int> q;
	for(int i = 0; i <= n + m + m + n; i ++) d[i] = inf;
	memset(v, 0, sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1; // SPFA ���·
	incf[s] = 1 << 30; // ����·�ϸ��ߵ���Сʣ������
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue; // ʣ������Ϊ0�����ڲ��������У�������
			int y = ver[i];
			if (d[y]>d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i; // ��¼ǰ���������ҵ��·��ʵ�ʷ���
				if (!v[y]) v[y] = 1, q.push(y);
			}
		}
	}
	if (d[t] == inf) return false; // ��㲻�ɴ����������
	return true;
}

// ���������·���䷴��ߵ�ʣ������
void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t]; // ���á��ɶԴ洢����xor 1����
		x = ver[i ^ 1];
	}
	maxflow += incf[t];
	ans += d[t] * incf[t];
	//printf("%d %d sd\n ",d[t],incf[t]);
}
void dfs1(int u)
{
 vis[u]=1;

// printf("u = %d\n",u);
 cout<<str[u-n]<<endl;if(u == n + n) return ;
 for(int i=head[u];i;i=Next[i])
  if(ver[i]<=n&& (edge[i] == inf - 1 || edge[i] == inf - 2))
  {
   dfs1(ver[i] + n);
   break;
  }
}
void dfs2(int u)
{
   // printf("u = %d\n",u);
    if(u == n + n) return ;
 for(int i=head[u];i;i=Next[i])
  if(ver[i]<=n&&!vis[ver[i]+n]&&(edge[i] == inf - 1 || edge[i] == inf - 2)){
        dfs2(ver[i]+n);break;
  }
 cout<<str[u-n]<<endl;
}
int main() {
        n = read(); m = read();  tot = 1;
        for(int i = 1; i <= n; i ++){
            cin >> str[i];
            Q[str[i]] = i;
            if(i == 1 || i == n) add(i,i + n,2,-1);
            else add(i,i + n,1,-1);
        }
        s = 1; t = n;
        for(int i = 1;i <= m; i ++){
            string s1,s2; cin >> s1 >> s2;
            int x = Q[s1],y = Q[s2];
            if(x > y) swap(x,y);
            add(x + n,y,inf,0);
        }

        maxflow = ans = 0;
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
        if(ans == 0 || ans == 1){
            printf("No Solution!\n"); return 0;
        }
        printf("%d\n",-ans);
        dfs1(1 + n);
        dfs2(1 + n);

}
