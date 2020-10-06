///���ӣ�https://www.luogu.com.cn/problem/P3358
/*����:n�������䣬ÿ�������ȨֵΪ���䳤�ȡ���������ѡ��s(����)��������ѡ�����s��������ͬʱ����һ����
  ����k�Σ�������ѡ������Ȩֵ�Ƕ��١�
  ��⣺ÿ���㲻�ܳ���k�Σ�����ÿ���㶨��һ�����ƣ�Ȼ��ÿ��������һȨֵ����Ӧ�Ƿ��ã�
  ���ԣ����ǿ��Կ�����ν�ͼ�����忴���������ͣ�
  1�õ��������˼���ͼ ����ÿ��ÿ���㱻���� ���ҽ����߶ε��������յ㱻���� ��ȫ������ɢ�ɵ���Ϊһ���߶ε��м�ĵ��ǲ���Ҫ�ġ�
  2����ÿ�������Ƿ�������౻����k�Σ�Ҳ����˵һ���߶��ܸ��Ǻö�㵫��һ������౻����k�Σ�������ǽ�ÿ���߶�����Դ���ʾʹ�õ�ǰ�����߶� �������߶���Ҫ�����Լ����ǵ���Щ�� ��Щ�������� ����Ϊk��ʾ�Լ���౻����k�Ρ�
  3���������ձ����ǵĵ�ͨ�������������Ʊ�֤����������󣬵����Ⲣ����ȷ����Ϊ���Ƿ������������߶ε�ֵ�϶����䳤�ȣ�������Ϊ1�����Ϊ��Ļ����ý��ᱻͳ�ƵĲ���ȷ������Ϊ1�Ļ�һ���߶ε�����Ȼ����ĳ���� ��������������һ�����������еĵ���ô��ô�죿
  4���Է���������һ��һ���Զ��������⣬������ȻҲ��ת���������ʹ��һ�����������ɸ��㣬������Ҫ��ô����Ȼ��Щ��ú�������һ��Ȼ��ʹ��һ�����������ǣ����Ծ��б���Ļ���ģ���˰�һЩ�㴮��������
  �ο����ͣ�https://www.luogu.com.cn/blog/qingyuhongchen/solution-p3358
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
