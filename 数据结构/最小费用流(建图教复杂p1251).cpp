///链接：https://www.luogu.com.cn/problem/P1251
/*题意: n天里每天都要使用不同数量的手巾；使用完的手巾可送到快洗店和慢洗店；
  当然费用不同，同时，当天也可以去商店买新的手巾；
  现在问你如何决策才能使用最小的费用，达到每天都有足够的手巾使用；
  题解：拆点，把每一天拆成两个点i，i+n，表示第i天的上午和下午；
  考虑建图：1，每天晚上(i+n)通过快洗店和慢洗店到达之后某天的早上，费用为洗衣店费用；
            2，每天晚上的脏手巾可留到第二天的晚上
            3，起点应该和每天早上相连，表示当天买手巾
            4，同时每天早上使用n的手巾应该流向当天晚上，但是注意今天用的手巾是可以今天送去洗
            的，所以我们需要直接从源点向晚上建边，代替此边；
            5，每天早上应该向汇点建一条边，费用为0，流量为r[i]，这样才能检验当天纸巾是否够用；
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
const int inf=2147483647;
const int N=4010,M=100100,E=100100;

int ver[E], edge[E], Next[E], head[E];
int cost[E],d[M];
ll incf[M]; int pre[M], v[M];
ll maxflow,ans;
int nn, k, tot, s, t, q[E];
int r[N],p,m,f,n,s1;
int sum;
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
	for(int i = 0; i < N; i ++) {d[i] = inf;v[i] = 0;}
	q.push(s); d[s] = 0; v[s] = 1; // SPFA 求最长路
	incf[s] = inf; // 增广路上各边的最小剩余容量
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue; // 剩余容量为0，不在残量网络中，不遍历
			int y = ver[i];
			if (d[y]>d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], (ll)edge[i]);
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
	ans += (ll)d[t] * incf[t];
	//printf("%d %d sd\n ",d[t],incf[t]);
}


int main() {
     nn = read();
     tot = 1;
     s = nn + nn + 1; t = s + 1;
     for(int i = 1; i <= nn; i ++) {
        r[i] = read();
        add(s,i + nn,r[i],0);
        add(i,t,r[i],0);
     }
     p = read(); m = read(); f = read(); n = read();s1 = read();
     for(int i = 1; i <= nn; i ++){
        if(i + 1 <= nn)add(i + nn,i+nn+1,inf,0);
        if(i + m <= nn)
        add(i + nn,i + m,inf,f);
        if(i + n <= nn)
        add(i + nn,i + n,inf,s1);
        add(s,i,inf,p);
     }
     maxflow = ans = 0;
     while(spfa()){
        update();
        //printf("%lld %lld\n",maxflow,ans);
    }

    printf("%lld\n",ans);

}
