///���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=3954
/*���� �������������ÿ�������ľ���ֵΪk���ȼ���*e(i);
  ��⣺���ÿ����㶼�����޸ĵĻ����϶��ᳬʱ�ģ�����������Ҫ������δ������ǡ������ǵı���
  ���Ǽ����޸Ĵ��������ǿ��Զ�ÿ�����ά��һ����ǰ��������Ҫ�ĵ���С����ֵ�������δ�ּӵľ��鶼������
  ����������ڵĽ�������������Ǿ�û�б�Ҫ�����½��и����ˡ�ͬʱ�����ǿ���ͨ��һ��С����ѧ����
  ������������Ҫ�� - ��ǰ���飩/ �ȼ� ������ȡ��������������ȼ������ǵ������ǵ�Ӱ�졣
  ����ÿ�������Ҫά������ֵ��
        ��ǰ��������������С����ֵ����ǰ�����ڵ������ֵ����ǰ�����ڵ����ȼ�
*/

#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <stdlib.h>
#include <cstdlib>
#include <math.h>
#include <set>
#include"queue"
#include <vector>
#define inf 107374182
#define M 10010001
#define ll long long
#define PII pair<int,int>
using namespace std;
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}

const int N = 1000010;
int n,m;
int root,lson[N << 2],rson[N << 2],tot,max_val[N << 2],min_val[N << 2],max_top[N << 2];
int laze[N << 2],a[N];

void push_up(int rt){
    max_val[rt] = max(max_val[lson[rt]],max_val[rson[rt]]);
    min_val[rt] = min(min_val[lson[rt]],min_val[rson[rt]]);
    max_top[rt] = max(max_top[lson[rt]],max_top[rson[rt]]);
}
void push_down(int rt){
    if(laze[rt] == 0) return ;
    laze[lson[rt]] += laze[rt]; laze[rson[rt]] += laze[rt];
    ///�����ʱ��laze[rt] * max_top[rt];δע�⵽!!
    max_val[lson[rt]] += laze[rt] * max_top[lson[rt]]; max_val[rson[rt]] += laze[rt] * max_top[rson[rt]];
    ///��ʼֱ�Ӿ�����д�����ˣ���Ȼ����laze[rt]��������Ҫ�ľ���Ϳ϶�Ҫ��Ӧ�ļ�ȥ
    min_val[lson[rt]] -= laze[rt]; min_val[rson[rt]] -= laze[rt];
    laze[rt] = 0;
}
void Build_Tree(int &rt,int l,int r){
  rt = ++ tot; laze[rt] = 0;
  if(l == r){
    max_val[rt] = 0; max_top[rt] = 1; laze[rt] = 0;
    min_val[rt] = a[max_top[rt] + 1] - max_val[rt];
    return ;
  }
  int mid = (l + r) >> 1;
  Build_Tree(lson[rt],l,mid);
  Build_Tree(rson[rt],mid + 1,r);
  push_up(rt);
}

void Update(int rt,int L,int R,int l,int r,int val){
   if(l <= L && r >= R && min_val[rt] > val){
       max_val[rt] += val * max_top[rt];
       ///ͬ��
       min_val[rt] -= val;
       laze[rt] += val; return ;
   }
   if(L == R){
     max_val[rt] += val * max_top[rt];
    // printf("%d max_val =%d\n",L,max_val[rt]);
     while(max_top[rt] + 1 <= m && a[max_top[rt] + 1] <= max_val[rt]) max_top[rt] += 1;
     min_val[rt] = (a[max_top[rt] + 1] - max_val[rt]) / max_top[rt];
     if((a[max_top[rt] + 1] - max_val[rt]) % max_top[rt]) min_val[rt] ++;
     return ;
   }
   push_down(rt);
   int mid = (L + R) >> 1;
   if(l <= mid) Update(lson[rt],L,mid,l,r,val);
   if(r > mid) Update(rson[rt],mid + 1,R,l,r,val);
   push_up(rt);
}

int query(int rt,int L,int R,int l,int r){
    if(R < L) return 0;
    if(l <= L && r >= R) return max_val[rt];
    push_down(rt);
    int mid = (L + R) >> 1;
    int ans = 0;
    if(l <= mid) ans = max(ans,query(lson[rt],L,mid,l,r));
    if(r > mid) ans = max(ans,query(rson[rt],mid + 1,R,l,r));
    return ans;
}

void init(){
    tot = 0;
}
int main(){
    int T = read(); int cont = 1;
    while(T --){

        n = read(); m = read(); int q = read();
        init();a[1] = 0;
        for(int i = 2; i <= m; i ++) a[i] = read();
        a[m + 1] = 1<<30;
        Build_Tree(root,1,n);
        printf("Case %d:\n",cont ++);
        while(q --){
            char str[5]; scanf("%s",str);
            int l = read(),r = read();
            if(str[0] == 'W'){
               int x = read();
               Update(root,1,n,l,r,x);
            } else if(str[0] == 'Q'){
               int sum = query(root,1,n,l,r);
               printf("%d\n",sum);
            }
        }
        printf("\n");
    }
}
