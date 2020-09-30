///���ӣ�https://www.luogu.com.cn/problem/P1251
/*����: n����ÿ�춼Ҫʹ�ò�ͬ�������ֽ�ʹ������ֽ���͵���ϴ�����ϴ�ꣻ
  ��Ȼ���ò�ͬ��ͬʱ������Ҳ����ȥ�̵����µ��ֽ�
  ����������ξ��߲���ʹ����С�ķ��ã��ﵽÿ�춼���㹻���ֽ�ʹ�ã�
  ��⣺��㣬��ÿһ����������i��i+n����ʾ��i�����������磻
  ���ǽ�ͼ��1��ÿ������(i+n)ͨ����ϴ�����ϴ�굽��֮��ĳ������ϣ�����Ϊϴ�µ���ã�
            2��ÿ�����ϵ����ֽ�������ڶ��������
            3�����Ӧ�ú�ÿ��������������ʾ�������ֽ�
            4��ͬʱÿ������ʹ��n���ֽ�Ӧ�����������ϣ�����ע������õ��ֽ��ǿ��Խ�����ȥϴ
            �ģ�����������Ҫֱ�Ӵ�Դ�������Ͻ��ߣ�����˱ߣ�
            5��ÿ������Ӧ�����㽨һ���ߣ�����Ϊ0������Ϊr[i]���������ܼ��鵱��ֽ���Ƿ��ã�
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
