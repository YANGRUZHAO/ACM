///���ӣ�https://www.luogu.com.cn/problem/P3356
/*����: һ��p*qͼ��������n��������(1,1)�㣬Ҫȥ��(n,n)�㣬ͬʱͼ�����ϰ����ʯ�飬����ֻ�����º������ߣ�����Ҫ��
        �ܵ���(n,n)���������࣬�����ռ���ʯ��������ࡣ
  ��⣺���������������ʯ��ĵط�Ҫ���������ߣ���㽨ͼ��
        ע�⳵������Ϊn������Ӧ��ҪŪ����ʼ�������ƣ�һ��ʼ��ΪûŪ��ʼ�����ƣ���������Ϊn�����´���
        ͬʱ��ע��98�к�96�е�return��һ��·����dfs���ˣ��Ǿ�û�б�Ҫ�ڵ�����·����dfs�ˡ�һ���ǵ�return��
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
	for(int i = 0; i <= t; i ++) d[i] = inf;
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
int get_id(int x,int y){
    return (x - 1) * p + y;
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
        n = read();  tot = 1;
        p = read(); q = read();
        t = p * q * 2 + 1;
        s = 0; T = p * q;
        add(s,get_id(1,1),n,0);
        add(get_id(q,p) + T,t,n ,0);
        for(int i = 1; i <= q; i ++) {
            for(int j = 1; j <= p; j ++){
                G[i][j] = read();
                if(G[i][j] == 1) continue;
                if(G[i][j] == 0)
                add(get_id(i,j),get_id(i,j) + T,inf,0);
                else {
                    add(get_id(i,j),get_id(i,j) + T,1,-1);
                    add(get_id(i,j),get_id(i,j) + T,inf,0);
                }
            }
        }
        for(int i = 1; i <= q; i ++){
            for(int j = 1; j <= p; j ++){
                if(G[i][j] == 1) continue;
                int x = i + 1,y = j;
                if(x <= q && G[x][y] != 1){
                    int id1 = get_id(i,j) + T,id2 = get_id(x,y);
                    add(id1,id2,inf,0);
                }
                x = i,y = j + 1;
                if(y <= p && G[x][y] != 1){
                    int id1 = get_id(i,j) + T,id2 = get_id(x,y);
                    add(id1,id2,inf,0);
                }
            }
        }

        maxflow = ans = 0;
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
      //  printf("%lld\n",-ans);
        for(int i = 1; i <= maxflow; i ++){
        //    printf("i = %d ��\n",i);
            dfs(1,0,i);
        }
}
