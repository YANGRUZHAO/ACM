///���ӣ�https://www.luogu.com.cn/problem/P4009
/*����: n*nͼ��������(1,1)�㵽(n,n)�㣬����һ��������k����·;����������վ��������ͣ��ҷ���ΪA
  ��������㴦���һ������վ������ΪC(�������ͷ���A)��ͬʱ������������ߵĹ�����x����y�����������
  �����Ҫ��B������С���ѣ�

  ��⣺���û�������������������ôֱ�ӽ�ͼ����С���������ɣ�
  ���������������������һ������k�����������ǿ��ǽ��ֲ�ͼ��1-k+1�㣬��һ���ʾ�������ģ���
  i+1���ʾʹ����i���������ǽ�ͼ��
  1�����ȵ�l��͵�(l + 1)��(i,j)���꣬Ӧ��һ������Ϊ0������Ϊ1�ı�;�����߿ɲ���
  2��if(i,j)���Ϳ⣬��l���(i,j)�͵�(l + 1)��(i + 1,j)(i,j + 1)��Ӧ���������ӵģ�����Ϊ0������Ϊ1��
  3��if(i,j)���Ϳ⣬��l���(i,j)�͵�(l + 1)��(i - 1,j)(i,j - 1)��Ӧ���������ӵģ�����ΪB������Ϊ1��
  4��if(i,j)���Ϳ⣬��l���(i,j)Ӧ�ú͵�һ���(i,j)��һ������ΪA������1�ıߣ���ʾ�����¼������ˡ�
  5��if(i,j)���Ϳ⣬�����ǿ��Կ�����(i,j)�Ͻ�һ���Ϳ⣬������Ӧ�����һ���(i,j)������һ��
     ����Ϊ1������ΪC+A�ıߣ�
  6��if(i,j)���Ϳ⣬���ǻ�Ӧ�üǵðѵ�һ���(i,j)�͵ڶ����(i+1,j)(i,j+1)��һ������Ϊ1������Ϊ0�ıߣ�
     ��һ���(i,j)�͵ڶ����(i-1,j)(i,j-1)��һ������ΪB������Ϊ0�ıߣ�
     ��Ϊ(i,j)���Ϳ⣬���Կ϶������(���ص���һ��)���ص���һ��֮��Ҫ���Ǽ�������ȥ�������������ĸ�����
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
	// ����ߣ���ʼ����z����λ����c
	ver[++tot] = y, edge[tot] = z, cost[tot] = c;
	Next[tot] = head[x], head[x] = tot;
	// ����ߣ���ʼ����0����λ����-c��������ߡ��ɶԴ洢��
	ver[++tot] = x, edge[tot] = 0, cost[tot] = -c;
	Next[tot] = head[y], head[y] = tot;
}


bool spfa() {

	for(int i = 0; i <= t; i ++) {d[i] = inf;v[i] = 0;}
	q.push(s); d[s] = 0; v[s] = 1; // SPFA ���·
	incf[s] = inf; // ����·�ϸ��ߵ���Сʣ������
	while (q.size()) {
		int x = q.front(); v[x] = 0; q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			if (!edge[i]) continue; // ʣ������Ϊ0�����ڲ��������У�������
			int y = ver[i];
			if (d[y]>d[x] + cost[i]) {
				d[y] = d[x] + cost[i];
				incf[y] = min(incf[x], (ll)edge[i]);
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
