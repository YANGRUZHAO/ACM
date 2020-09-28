///���ӣ�https://ac.nowcoder.com/acm/contest/6874/A
/*����: һ�������ʴ�ÿ�����������ȫ���ĵ㣨��������������·����
  ��⣺��A������ص�A���·�����Ⱦ������еı������Σ����ڲ���Ҫ��������ôҲ���Ǿ���A����Զ������·���ĳ�����Ҫ��ȥ��
        �������ǿ�������ҵ�ÿ�����������Զ�ĵ㣻���ǿ��Է��־���ÿ����A��Զ�ĵ�һ��������ֱ���е�һ���˵㣻
        ����������Ҫ������ֱ�Ӵ���������ɡ�
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
const ll inf=1e18;
const int N=100010,M=N*N+N+7,E=500005;
int head[N],ver[N << 1],Next[N << 1],Edge[N << 1],tot;
int vis[N];int n; ll m;
int ans1,ans2;
ll dist[N],dist2[N];
ll ans[N],sum;
queue<int> Q;
void add(int x,int y,int w){
    ver[++ tot] = y; Next[tot] = head[x];
    Edge[tot] = w; head[x] = tot;
}
void bfs(){
   Q.push(1);
   vis[1] = 1;dist[1] = 0;ans1 = 1;
   while(!Q.empty()){
        int x = Q.front(); Q.pop();
        vis[x] = 0;
        if(dist[x] > dist[ans1]) ans1 = x;
        for(int i = head[x]; i ;i = Next[i]){
            int y = ver[i];
            if(dist[y] <= dist[x] + Edge[i]) continue;
            dist[y] = dist[x] + Edge[i];
            if(!vis[y]){
                vis[y] = 1; Q.push(y);
            }
        }
   }
}

void bfs1(){
   Q.push(ans1);
   vis[ans1] = 1;dist[ans1] = 0;ans2 = ans1;
   while(!Q.empty()){
        int x = Q.front(); Q.pop();
        vis[x] = 0;
        if(dist[x] > dist[ans2]) ans2 = x;
        for(int i = head[x]; i ;i = Next[i]){
            int y = ver[i];
            if(dist[y] <= dist[x] + Edge[i]) continue;
            dist[y] = dist[x] + Edge[i];
            if(!vis[y]){
                vis[y] = 1; Q.push(y);
            }
        }
   }
}
void bfs2(){
   Q.push(ans2);
   vis[ans2] = 1;dist2[ans2] = 0;
   while(!Q.empty()){
        int x = Q.front(); Q.pop();
        vis[x] = 0;
        for(int i = head[x]; i ;i = Next[i]){
            int y = ver[i];
            if(dist2[y] <= dist2[x] + Edge[i]) continue;
            dist2[y] = dist2[x] + Edge[i];
            if(!vis[y]){
                vis[y] = 1; Q.push(y);
            }
        }
   }
}
int main() {
    n = read();scanf("%lld",&m);
    for(int i = 1; i < n; i ++){
        int x = read(),y = read(),w = read();
        add(x,y,w); add(y,x,w);
        dist[i] = inf; sum += w;
    }
    dist[n] = inf;
    bfs();
    for(int i = 0; i <= n; i ++){
        vis[i] = 0; dist[i] = inf;dist2[i] = inf;
    }
    bfs1();
    bfs2();
    sum *= 2;
    for(int i = 1; i <= n; i ++){
       ans[i] = sum - max(dist[i],dist2[i]);
    }
    sort(ans + 1,ans + n + 1);

    int cnt = 0;
    for(int i = 1; i <= n; i ++){
        if(m >= ans[i]){
            m -= ans[i]; cnt ++;
        } else break;
    }
    printf("%d\n",cnt);
}
