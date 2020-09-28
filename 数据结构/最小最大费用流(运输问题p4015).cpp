///链接：https://www.luogu.com.cn/problem/P4015
/*题意: n个仓库，m个商店，仓库有货物，商店要货物，每个仓库运输货物到商店的费用是不同的，现在问
        在成功运输的基础之上的最小费用是多少。
  题解：明显是最小费用最大流，怎么建图。我们能可以把仓库跟S点连接，商店跟T点连接，然后仓库在跟商店连接
     费用为输入值，流量为inf。
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
int n, k, tot, s, t, maxflow,m,q[E];
int store1[N],store2[N],store[N][N];


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

int main() {
        n = read(); m = read();  tot = 1;
        t = n + m + 2;
        s =  n + m + 1;
        for(int i = 1; i <= n; i ++) {
            scanf("%d",&store1[i]);
            add(s,i,store1[i],0);
        }
        for(int i = 1; i <= m; i ++) {
            scanf("%d",&store2[i]);
            add(i + n,t,store2[i],0);
        }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
               int x; scanf("%d",&x);
               store[i][j] = x;
               add(i,j + n,inf,x);
            }
        }
        maxflow = ans = 0;
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",ans);


        memset(head,0,sizeof(head)); tot = 1;
        for(int i = 1; i <= n; i ++) {
            add(s,i,store1[i],0);
        }
        for(int i = 1; i <= m; i ++) {
            add(i + n,t,store2[i],0);
        }
        for(int i = 1; i <= n; i ++){
            for(int j = 1; j <= m; j ++){
               add(i,j + n,inf,-store[i][j]);
            }
        }
        maxflow = ans = 0;
        while(spfa()){
         update();
        // printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);
}
