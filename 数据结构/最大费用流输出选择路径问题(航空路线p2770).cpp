///链接：https://www.luogu.com.cn/problem/P2770
/*题意: 给定一张航空图，顶点是从左往右，从1号点找一条线路到n号点，然后在从n号点回来；两条路径的顶点不允许重复走，
       问是否存在一种走最多顶点的路径；并输入路径
  题解：明显是最大费用最大流。两条路径1-n-1；不就是两条1-n的路径；考虑到这一点，就会发现建图也不是很难了。
        每个顶点走一次，岂不是拆点之后容量为1；
        本题有一个地方找了好久bug，在输出路径的时候，没有注意到返祖边，同时返祖边的容量是不定的。
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
	// 正向边，初始容量z，单位费用c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// 反向边，初始容量0，单位费用-c，与正向边“成对存储”
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}


bool spfa() {
	queue<int> q;
	for(int i = 0; i <= n + m + m + n; i ++) d[i] = inf;
	memset(v, 0, sizeof(v));
	q.push(s); d[s] = 0; v[s] = 1; // SPFA 求最长路
	incf[s] = 1 << 30; // 增广路上各边的最小剩余容量
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue; // 剩余容量为0，不在残量网络中，不遍历
			int y = ver[i];
			if (d[y]>d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], edge[i]);
				pre[y] = i; // 记录前驱，便于找到最长路的实际方案
				if (!v[y]) v[y] = 1, q.push(y);
			}
		}
	}
	if (d[t] == inf) return false; // 汇点不可达，已求出最大流
	return true;
}

// 更新最长增广路及其反向边的剩余容量
void update() {
	int x = t;
	while (x != s) {
		int i = pre[x];
		edge[i] -= incf[t];
		edge[i ^ 1] += incf[t]; // 利用“成对存储”的xor 1技巧
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
