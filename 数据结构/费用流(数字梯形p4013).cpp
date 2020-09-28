///���ӣ�https://www.luogu.com.cn/problem/P4013
/*����: һ���������Σ������ʸ�һ���Ĺ����ڸ����Ĺ����£���ѡȡ�����ֵ�Ƕ��١�
  ��⣺����������������ݹ�����в�ͬ��ͼ����������������Բ��ò�㽨ͼ��
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
const int N=1000,M=300000,E=300000;
int ver[E], edge[E], Next[E], head[N];
int cost[E],d[M];
int incf[M], pre[M], v[M];
ll ans;
int n, k, tot, s, t, maxflow,m,q[E];
int G[40][1010],id[40][1010];


void add(int x, int y, int z, int c){
	// ����ߣ���ʼ����z����λ����c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// ����ߣ���ʼ����0����λ����-c��������ߡ��ɶԴ洢��
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}


bool spfa() {
	queue<int> q;
	for(int i = 0; i < N; i ++) {d[i] = inf;v[i] = 0;}
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
}

int main() {
        n = read(); m = read();  tot = 1;
        s = 0; int top1 = n;
        for(int i = 1; i <= m; i ++){
            for(int  j = 1; j <= n + i - 1; j ++){
                G[i][j] = read();
                ++ s;
                id[i][j] = s;
            }
        }
        top1 = s; s = s * 2+1;t = s + 1;
        for(int i = 1; i <= m; i ++){
           for(int j = 1; j <= n + i - 1; j ++){
               if(i == 1){
                add(s,id[i][j],1,0);
               }
               add(id[i][j],id[i][j] + top1,1,-G[i][j]);
               if(i != m){
                  add(id[i][j] + top1,id[i + 1][j],1,0);
                  add(id[i][j] + top1,id[i + 1][j + 1],1,0);
               } else {
                   add(id[i][j] + top1,t,1,0);
               }
           }
        }
        maxflow = ans = 0;
       // printf("YES\n");
        while(spfa()){
         update();
         //printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);

        memset(head,0,sizeof(head)); tot = 1;

        for(int i = 1; i <= m; i ++){
           for(int j = 1; j <= n + i - 1; j ++){
               if(i == 1){
                add(s,id[i][j],1,0);
               }
              // add(id[i][j],id[i][j] + top1,inf,-G[i][j]);
               if(i != m){
                  add(id[i][j],id[i + 1][j],1,-G[i][j]);
                  add(id[i][j],id[i + 1][j + 1],1,-G[i][j]);
               } else {
                   add(id[i][j],t,inf,-G[i][j]);
               }
           }
        }

        maxflow = ans = 0;
        while(spfa()){
         update();
        // printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);


        memset(head,0,sizeof(head)); tot = 1;

        for(int i = 1; i <= m; i ++){
           for(int j = 1; j <= n + i - 1; j ++){
               if(i == 1){
                add(s,id[i][j],1,0);
               }
              // add(id[i][j],id[i][j] + top1,inf,-G[i][j]);
               if(i != m){
                  add(id[i][j],id[i + 1][j],inf,-G[i][j]);
                  add(id[i][j],id[i + 1][j + 1],inf,-G[i][j]);
               } else {
                   add(id[i][j],t,inf,-G[i][j]);
               }
           }
        }

        maxflow = ans = 0;
        while(spfa()){
         update();
        // printf("%lld %lld\n",maxflow,ans);
        }
        printf("%lld\n",-ans);
}
