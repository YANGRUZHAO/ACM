///���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=6183
/*����: ���ֲ�����0��������е㡣1���ڣ�x,y������������һ����ɫΪc�ĵ㣬2����ѯ��1<=i<=x��(y1<=j<=y2)����������ж�������ɫ��ͬ�ĵ㣬3���˳�
  ��⣺�߶�����ע�����ݷ�Χ����ɫ���50�֣������ǿ��Կ��Ƕ�ÿ����ɫ������һ���߶������۲��ѯ�����ǿ��Է���x�Ĳ�ѯ�Ƚ���֣�
        �������ǿ��Ը���y�����н���������ÿ��y��Ӧ��x������Ӧ������С��x��
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
#define inf 1e9
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

const int N = 1000100;
int n,m,OK;
int root[55],lson[N << 2],rson[N << 2],tot,minx[N << 2];

void Update(int &rt,int l,int r,int pos,int val){
     if(rt == 0) {
        rt = ++ tot;
        lson[rt] = rson[rt] = 0; minx[rt] = inf;
     }
     if(l == r){
     //   printf("c = %d l = %d val = %d\n",c,l,val);
        minx[rt] = min(minx[rt],val); return ;
     }
     int mid = (l + r) >> 1;
     if(pos <= mid) Update(lson[rt],l,mid,pos,val);
     else Update(rson[rt],mid + 1,r,pos,val);
     minx[rt] = min(minx[lson[rt]],minx[rson[rt]]);
     return ;
}

void query(int rt,int L,int R,int l,int r,int x){
    if(rt == 0 || OK) return ;
    if(l <= L && r >= R) {
        if(minx[rt] <= x) OK = 1;
        return ;
    }
    int mid = (L + R) >> 1;
    if(l <= mid)  query(lson[rt],L,mid,l,r,x);
    if(r > mid) query(rson[rt],mid + 1,R,l,r,x);
    return ;
}
void init(){
   tot = 0;
   minx[0] = 1e9;
    for(int i = 0; i <= 50; i ++){
      root[i] = 0;
   }
}
int main(){
    init();
    while(1){
        int op = read();
        if(op == 3) return 0;
        if(op == 0){
            init();  ;
        }
        if(op == 2){
            int x = read(),y1 = read(),y2 = read();
            int ans = 0;
            for(int i = 0; i <= 50; i ++){
                OK = 0;
                query(root[i],1,1e6,y1,y2,x);
                ans += OK;
                //if(y != 1e9)
                //printf("y = %d\n",y);
            }
            printf("%d\n",ans);
            continue;
        }
        if(op == 1){
            int x = read(),y = read(),c = read();
            Update(root[c],1,1e6,y,x);
            continue;
        }
    }
}
