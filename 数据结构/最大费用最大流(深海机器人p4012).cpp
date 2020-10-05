///链接：https://www.luogu.com.cn/problem/P4012
/*题意: 一张p*q图，现在有a个起点，b个终点，其中图中还有一些有价值的植物，现在问你在让起点到终点的路径中，可以获得的最大价值是多少。
  题解：最大费用最大流。感觉更像是https://www.luogu.com.cn/problem/P3356的简化版；
        但是此题的输入比较恶心，一度让人看不懂。同时相比火星探险，这题是网格边上有权值，所以不需要进行拆点操作。
*/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include"set"
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
int cost[E],d[M];
int incf[M], pre[M], v[M];
ll ans;
int n, k, tot, s, t, maxflow,m;
int G[N][N],q,p,T;
int a,b,Q,P;

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
	for(int i = 0; i <= t; i ++) d[i] = inf;
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
int get_id(int x,int y){
    return (x-1)*Q+y;
}
void dfs(int x,int far,int v){
   for(int i = head[x + T]; i; i = Next[i]){
       int y = ver[i];
      //

       if(!(y >= 1 && y <= T)) continue;
       if(y == far || y == x) continue;
       if(edge[i] == 1 || edge[i] == inf) continue;
    //  printf("x = %d y = %d edge[i] = %d\n",x,y,edge[i]);
          edge[i] ++;
          if(y == x + 1){
            printf("%d 1\n",v);
          } else printf("%d 0\n",v);
          if(y == t || y == T) return ;
          dfs(y,x,v);
          return ;
   }
}
int main() {
        tot = 1;
        scanf("%d%d%d%d",&a,&b,&P,&Q);
        P++,Q++;s = 0; t = P * Q + 1;
        for(int i=1;i<=P;i++)
          for(int j=1;j<Q;j++){
                int x = read(),id1=get_id(i,j),id2 = id1 + 1;
                add(id1,id2,1,-x);
                add(id1,id2,inf,0);
            }
        for(int j=1;j<=Q;j++)
          for(int i=1;i<P;i++){
                int x = read(),id1=get_id(i,j),id2 = id1 + Q;
                add(id1,id2,1,-x);
                add(id1,id2,inf,0);
            }
        for(int i=1;i<=a;i++){
              int k,x,y;
              scanf("%d%d%d",&k,&x,&y);
              x++,y++;
              add(s,get_id(x,y),k,0);
          }
        for(int i=1;i<=b;i++)
          {
              int k,x,y;
              scanf("%d%d%d",&k,&x,&y);
              x++,y++;
              add(get_id(x,y),t,k,0);
          }
        maxflow = ans = 0;
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);

}
