///���ӣ�http://acm.hdu.edu.cn/showproblem.php?pid=1255
/*����: �ڶ�ά����ϵ�ϣ�����n����������������n�������ص���������Ƕ��١�
  ��⣺�Ƽ����ͣ�https://blog.csdn.net/riba2534/article/details/76851233(�ͱ�����С���)
  ɨ���ߣ�������ͳ�������ʱ�򣬿��Խ���ֳ�С�������ͳ�ƣ��Ӷ�����άת����һά�������Ƽ�������ͼ
  �����Ǹ���һ�Σ������Ǹ������Σ��������ǿ���ͳ�Ƴ��ȵ�ʱ�򣬿����Ƿ񸲸������Σ�����ͳ�Ƴ��ȣ�����ÿ�μ��������
  ʱ�򣬼ǵ�query�������е�laze����µ���ײ���ȥ���㳤�ȡ�
*/
#include"stdio.h"
#include"string.h"
#include"stack"
#include"map"
#include"math.h"
#include"iostream"
#include"vector"
#include"queue"
#include"algorithm"
using namespace std;
#define OK printf("\n");
#define Debug printf("this_ok\n");
#define inf 1e9
#define INF 1e18
typedef long long ll;
#define scanll(a,b) scanf("%lld%lld",&a,&b);
#define scanl(a) scanf("%lld",&a);
#define printl(a,b) if(b == 0) printf("%lld ",a); else printf("%lld\n",a);
#define print_int(a,b) if(b == 0) printf("%d ",a); else printf("%d\n",a);
typedef pair<int,int> PII;
inline int read(){
    int s = 0, w = 1; char ch = getchar();
    while(ch < '0' || ch > '9')   { if(ch == '-') w = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') { s = (s << 3) + (s << 1) + (ch ^ 48); ch = getchar(); }
    return s * w;
}
const ll mod = 998244353;
const int N = 300100;
struct Edge{
    double x1,x2,h; int val;
    Edge(){}
    Edge(double a,double b,double c,int v){
        x1 = a; x2 = b; h = c; val = v;
    }
};
double X[N];
Edge edge[N];
int top,len,tot,n;
int root,lson[N << 1],rson[N << 1];double sum[N << 1];
int cnt[N << 1],laze[N << 1];
int cmp(Edge A,Edge B){
    return A.h < B.h;
}
void push_down(int rt,int L,int R){
    if(!laze[rt]) return ;
    cnt[lson[rt]] += laze[rt];
    cnt[rson[rt]] += laze[rt];
    laze[lson[rt]] += laze[rt];
    laze[rson[rt]] += laze[rt];
    laze[rt] = 0;
}
void push_up(int rt,int L,int R){
    if(cnt[rt] >= 2){
        sum[rt] = X[R + 1] - X[L];
        return ;
    } else if(L == R) sum[rt] = 0;
    else sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
void Build_Tree(int &rt,int l,int r){
   rt = ++ tot; sum[rt] = 0; cnt[rt] = 0;laze[rt] = 0;
  // printf("l = %d r = %d\n",l,r);
   if(l == r) return ;
   int mid = (l + r) >> 1;
   Build_Tree(lson[rt],l,mid);
   Build_Tree(rson[rt],mid + 1,r);
}
void Update(int rt,int L,int R,int l,int r,int v){
    if(l <= L && r >= R) {
      cnt[rt] += v;laze[rt] += v;
      push_up(rt,L,R);
      return ;
    }
    push_down(rt,L,R);
    int mid = (L + R) >> 1;
    if(l <= mid) Update(lson[rt],L,mid,l,r,v);
    if(r > mid) Update(rson[rt],mid + 1,R,l,r,v);
    push_up(rt,L,R);
}
void query(int rt,int L,int R){
    if(L == R){
        push_up(rt,L,R);
        return ;
    }
    push_down(rt,L,R);
    int mid = (L + R) >> 1;
    query(lson[rt],L,mid);
    query(rson[rt],mid + 1,R);
    push_up(rt,L,R);
}
int main(){
    int q = 1;
    q = read();
    while(q --){
        n = read();
        top = 0; len = 0;tot = 0;
        for(int i = 1; i <= n; i ++){
           double x1,x2,y1,y2;
           scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
           X[++ top] = x1;
           edge[top] = {x1,x2,y1,1};
           X[++ top] = x2;
           edge[top] = {x1,x2,y2,-1};
        }
        sort(X + 1,X + top + 1);
        sort(edge + 1,edge + top + 1,cmp);
        len = unique(X + 1,X + top + 1) - X - 1;
        Build_Tree(root,0,len);
        double ans = 0;
        for(int i = 1; i <= top; i ++){
           int idl = lower_bound(X + 1,X + len + 1,edge[i].x1) - X;
           int idr = lower_bound(X + 1,X + len + 1,edge[i].x2) - X - 1;
           Update(root,0,len,idl,idr,edge[i].val);
           query(root,0,len);
           ans += sum[root] * (edge[i + 1].h - edge[i].h);
        }
        printf("%.2lf\n",ans);
    }
}
/*
3
1 2 3
2
2 6
*/

