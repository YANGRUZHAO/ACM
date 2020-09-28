///���ӣ�http://poj.org/problem?id=2195
/*����: n���ˣ�m�����ӣ�ÿ���˶���������ȥ������С���롣
  ��⣺��С�����������������ͼ���ɣ�������KM
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
const int N=1010,M=100100,E=100100;
typedef struct People{
    int x,y;
    People(){}
    People(int a,int b){
        x = a; y = b;
    }
}People;
typedef struct House{
    int x,y;
    House(){}
    House(int a,int b){
        x = a; y = b;
    }
}House;
int ver[E], edge[E], Next[E], head[E];
int cost[E],d[M];
int incf[M], pre[M], v[M];
int ans;
int n, k, tot, s, t, maxflow,m,q[E];
char str[110][110];
People peo[N];
House hou[N];

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
	for(int i = 0; i < N; i ++) d[i] = inf;
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

int get_dist(int a,int b){
    return abs(peo[a].x - hou[b].x) + abs(peo[a].y - hou[b].y);
}
int main() {
        while(~scanf("%d%d",&n,&m)){
            if(n == 0) break;
            tot = 1;   memset(head,0,sizeof(head));
            int x1 = 0,x2 = 0;
            for(int i = 1; i <= n; i ++) {
               scanf("%s",str[i] + 1);
            }
            for(int i = 1; i <= n; i ++){
                for(int j = 1; j <= m; j ++){
                   if(str[i][j] == '.') continue;
                   if(str[i][j] == 'm') peo[++ x1] = {i,j};
                   else hou[++ x2] = {i,j};
                }
            }
            s = x1 + x2 + 1; t = s + 1;
            maxflow = ans = 0;
            for(int i = 1; i <= x1; i ++){
                add(s,i,1,0);
            }
            for(int i = 1; i <= x2; i ++){
                add(i + x1,t,1,0);
            }
            for(int i = 1; i <= x1; i ++){
                for(int j = 1; j <= x2; j ++){
                    int dis = get_dist(i,j);
                   // printf("dis = %d\n",dis);
                    add(i,j + x1,1,dis);
                }
            }
            while(spfa()){
             update();
             //printf("%lld %lld\n",maxflow,ans);
            }
            printf("%d\n",ans);
        }
}
