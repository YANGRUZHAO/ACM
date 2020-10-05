///���ӣ�https://www.luogu.com.cn/problem/P4012
/*����: һ��p*qͼ��������a����㣬b���յ㣬����ͼ�л���һЩ�м�ֵ��ֲ���������������㵽�յ��·���У����Ի�õ�����ֵ�Ƕ��١�
  ��⣺��������������о�������https://www.luogu.com.cn/problem/P3356�ļ򻯰棻
        ���Ǵ��������Ƚ϶��ģ�һ�����˿�������ͬʱ��Ȼ���̽�գ����������������Ȩֵ�����Բ���Ҫ���в�������
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
