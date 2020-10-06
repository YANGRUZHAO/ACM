///链接：https://www.luogu.com.cn/problem/P4009
/*题意: n*n图，汽车从(1,1)点到(n,n)点，汽车一箱油能走k步，路途中遇到加油站必须加满油，且费用为A
  可在网格点处添加一个加油站，费用为C(不含加油费用A)，同时，如果我们在走的过程中x或者y的坐标减少了
  则费用要加B。问最小花费；

  题解：如果没有油这个限制条件，那么直接建图跑最小费用流即可；
  现在有了油这个条件，且一箱油走k步，所以我们考虑建分层图，1-k+1层，第一层表示油是满的，第
  i+1层表示使用了i油量；考虑建图：
  1，首先第l层和第(l + 1)的(i,j)坐标，应连一条费用为0，容量为1的边;这条边可不建
  2，if(i,j)无油库，第l层的(i,j)和第(l + 1)的(i + 1,j)(i,j + 1)，应该是相连接的，费用为0，容量为1；
  3，if(i,j)无油库，第l层的(i,j)和第(l + 1)的(i - 1,j)(i,j - 1)，应该是相连接的，费用为B，容量为1；
  4，if(i,j)有油库，第l层的(i,j)应该和第一层的(i,j)连一条费用为A，容量1的边，表示又重新加满油了。
  5，if(i,j)无油库，则我们可以考虑在(i,j)上建一个油库，则我们应该向第一层的(i,j)边连接一条
     容量为1，费用为C+A的边；
  6，if(i,j)有油库，我们还应该记得把第一层第(i,j)和第二层的(i+1,j)(i,j+1)连一条容量为1，费用为0的边；
     第一层第(i,j)和第二层的(i-1,j)(i,j-1)连一条容量为B，费用为0的边；
     因为(i,j)有油库，所以肯定会加满(即回到第一层)，回到第一层之后要考虑继续走下去，即上下左右四个方向。
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
const int N1=1000005,M=3000005,E=3000005;

int ver[E], edge[E], Next[E], head[E];
int cost[E],d[M];
ll incf[M]; int pre[M], v[M];
ll maxflow,ans;
int nn, k, tot, s, t;
int r[N1],p,m,f,n,s1;
int sum;queue<int> q;
int N,K,A,B,C;
void add(int x, int y, int z, int c) {
	// 正向边，初始容量z，单位费用c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// 反向边，初始容量0，单位费用-c，与正向边“成对存储”
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}


bool spfa() {

	for(int i = 0; i <= t; i ++) {d[i] = inf;v[i] = 0;}
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

int get_id(int x,int y,int l){
    return ((x - 1) * N + y) + (l - 1) * N * N;
}
int main() {
     N = read(); K = read(); A = read(); B = read(); C = read();
     tot = 1;
     s = 0; t = (K + 1) * N * N + 1;
     add(s,1,1,0);
     for(int l = 1; l <= K + 1; l ++){
         int x = get_id(N,N,l);
         add(x,t,1,0);
     }
     for(int i = 1; i <= N; i ++){
        for(int j = 1; j <= N; j ++){
            int oil = read();
            ///for(int l = 1; l <= K; l ++){
               /* int x = get_id(i,j,l);
                int y = get_id(i,j,l + 1);
                add(x,y,1,0);
            }*/
            if(oil){
               for(int l = 2; l <= K + 1; l ++){
                  int x = get_id(i,j,l),y = get_id(i,j,1);
                  add(x,y,1,A);
               }
               if(j + 1 <= N) {
                  int x = get_id(i,j,1),y = get_id(i,j + 1,2);
                  add(x,y,1,0);
               }
               if(i + 1 <= N){
                  int x = get_id(i,j,1),y = get_id(i + 1,j,2);
                  add(x,y,1,0);
               }
               if(i - 1 >= 1){
                  int x = get_id(i,j,1),y = get_id(i - 1,j,2);
                  add(x,y,1,B);
               }
               if(j - 1 >= 1){
                  int x = get_id(i,j,1),y = get_id(i,j - 1,2);
                  add(x,y,1,B);
               }
            } else {
                for(int l = 1; l <= K; l ++){
                   if(j + 1 <= N) {
                      int x = get_id(i,j,l),y = get_id(i,j + 1,l + 1);
                      add(x,y,1,0);
                   }
                   if(i + 1 <= N){
                      int x = get_id(i,j,l),y = get_id(i + 1,j,l + 1);
                      add(x,y,1,0);
                   }
                   if(i - 1 >= 1){
                      int x = get_id(i,j,l),y = get_id(i - 1,j,l + 1);
                      add(x,y,1,B);
                   }
                   if(j - 1 >= 1){
                      int x = get_id(i,j,l),y = get_id(i,j - 1,l + 1);
                      add(x,y,1,B);
                   }
                }
                for(int l = 2; l <= K + 1; l ++){
                   int x = get_id(i,j,l),y = get_id(i,j,1);
                   add(x,y,1,C + A);
                }
            }

        }
     }

     maxflow = ans = 0;
     while(spfa()){
        update();
    //    printf("%lld %lld\n",maxflow,ans);
    }

    printf("%lld\n",ans);

}
