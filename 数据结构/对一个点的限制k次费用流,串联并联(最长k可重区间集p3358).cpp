///链接：https://www.luogu.com.cn/problem/P3358
/*题意:n个开区间，每个区间的权值为区间长度。现在让你选择s(不定)个，并且选择的这s个，不能同时覆盖一个点
  超过k次，问你能选择的最大权值是多少。
  题解：每个点不能超过k次，即给每个点定了一个限制，然后每个区间有一权值，理应是费用；
  所以，我们可以考虑如何建图；具体看下面两博客；
  1拿到这道题后画了几个图 发现每个每个点被覆盖 当且仅当线段的起点或者终点被覆盖 完全可以离散成点因为一条线段的中间的点是不必要的。
  2对于每个点我们发现其最多被覆盖k次，也就是说一条线段能覆盖好多点但是一个点最多被覆盖k次，如果我们将每条线段连向源点表示使用当前这条线段 而这条线段需要连向自己覆盖的那些点 这些点连向汇点 容量为k表示自己最多被覆盖k次。
  3我们让最终被覆盖的点通过汇点的流量限制保证了这个条件后，但是这并不正确，因为这是费用流，这条线段的值肯定是其长度，而流量为1，如果为多的话费用将会被统计的不正确，但是为1的话一条线段的流必然流向某个点 但是我们想让这一条流流过所有的点那么怎么办？
  4可以发现这变成了一个一流对多流的问题，问题自然也被转换成了如何使用一条流流过若干个点，发现想要这么做必然这些点得横着连到一块然后使用一条流流过他们，所以就有本题的基本模型了把一些点串联起来。
  参考博客：https://www.luogu.com.cn/blog/qingyuhongchen/solution-p3358
            https://www.luogu.com.cn/blog/chdy/solution-p3358
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
const int N=3000,M=N*N+N+7,E=500005;
int ver[E], edge[E], Next[E], head[E];
int cost[E],d[M];
int incf[M], pre[M], v[M];
ll ans;
int n, k, tot, s, t, maxflow,m;
int L[N],R[N],a[N],top;

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


int main() {
        n = read(); k = read(); tot = 1;
        for(int i = 1; i <= n; i ++){
           L[i] = read(); R[i] = read();
           a[++ top] = L[i]; a[++ top] = R[i];
        }
        sort(a + 1,a + top + 1);
        int len = unique(a + 1,a + top + 1) - a - 1;
        t = len + 1;
        s = 0;
        for(int i = 2; i <= len; i ++){
            add(i - 1,i,k,0);
        }
        add(s,1,k,0); add(len,t,k,0);
        for(int i = 1; i <= n; i ++){
            int x = lower_bound(a + 1,a + len + 1,L[i]) - a;
            int y = lower_bound(a + 1,a + len + 1,R[i]) - a;
            add(x,y,1,-(a[y] - a[x]));
        }

        maxflow = ans = 0;
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);
}
