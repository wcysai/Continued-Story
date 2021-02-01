#include<bits/stdc++.h> 
using namespace std;
//LOOP
#define FF(i, a, b) for(int i = (a); i < (b); ++i)
#define FE(i, a, b) for(int i = (a); i <= (b); ++i)
#define FED(i, b, a) for(int i = (b); i>= (a); --i)
#define REP(i, N) for(int i = 0; i < (N); ++i)
#define CLR(A,value) memset(A,value,sizeof(A))
#define FC(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it++)
//OTHER
#define SZ(V) (int)V.size()
#define PB push_back
#define MP make_pair
#define all(x) (x).begin(),(x).end()
//INPUT
#define RI(n) scanf("%d", &n)
#define RII(n, m) scanf("%d%d", &n, &m)
#define RIII(n, m, k) scanf("%d%d%d", &n, &m, &k)
#define RIV(n, m, k, p) scanf("%d%d%d%d", &n, &m, &k, &p)
#define RV(n, m, k, p, q) scanf("%d%d%d%d%d", &n, &m, &k, &p, &q)
#define RS(s) scanf("%s", s)
//OUTPUT
#define WI(n) printf("%d\n", n)
#define WS(n) printf("%s\n", n)
//debug
//#define online_judge
#ifndef online_judge
#define debugt(a) cout << (#a) << "=" << a << " ";
#define debugI(a) debugt(a) cout << endl
#define debugII(a, b) debugt(a) debugt(b) cout << endl
#define debugIII(a, b, c) debugt(a) debugt(b) debugt(c) cout << endl
#define debugIV(a, b, c, d) debugt(a) debugt(b) debugt(c) debugt(d) cout << endl
#else
#define debugI(v)
#define debugII(a, b)
#define debugIII(a, b, c)
#define debugIV(a, b, c, d)
#endif
typedef long long LL;
typedef unsigned long long ULL;
typedef vector <int> VI;
const int INF = 0x3f3f3f3f;
const double eps = 1e-10;
const int MOD = 100000007;
const int MAXN = 1000010;
const double PI = acos(-1.0);


///*************基础***********/
double torad(double deg)
{
    return deg / 180 * PI;
}
inline int dcmp(double x)
{
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
struct Point
{
    double x, y;
    Point(double x=0, double y=0):x(x),y(y) { }
    inline void read()
    {
        scanf("%lf%lf", &x, &y);
    }
};
typedef vector<Point> Polygon;
typedef Point Vector;

inline Vector operator + (Vector A, Vector B)
{
    return Vector(A.x+B.x, A.y+B.y);
}
inline Vector operator - (Point A, Point B)
{
    return Vector(A.x-B.x, A.y-B.y);
}
inline Vector operator * (Vector A, double p)
{
    return Vector(A.x*p, A.y*p);
}
inline Vector operator / (Vector A, double p)
{
    return Vector(A.x/p, A.y/p);
}
inline bool operator < (Point a, Point b)
{
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}


inline bool operator == (Point a, Point b)
{
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}


inline double Dot(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y;
}
inline double Length(Vector A)
{
    return sqrt(Dot(A, A));
}
inline double Angle(Vector A, Vector B)
{
    return acos(Dot(A, B) / Length(A) / Length(B));
}
inline double angle(Vector v)
{
    return atan2(v.y, v.x);
}
inline double Cross(Vector A, Vector B)
{
    return A.x*B.y - A.y*B.x;
}
inline Vector Unit(Vector x)
{
    return x / Length(x);   //单位向量
}
inline Vector Normal(Vector x)
{
    return Point(-x.y, x.x) / Length(x);   //垂直法向量
}
inline Vector Rotate(Vector A, double rad)
{
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
inline double Area2(Point A, Point B, Point C)
{
    return Cross(B-A, C-A);
}

template <class T> T sqr(T x)
{
    return x * x ;
}
/****************直线与线段**************/


//求直线p+tv和q+tw的交点 Cross(v, w) == 0无交点
Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
{
    return p + v * Cross(w, p - q) / Cross(v, w);
}

//点p在直线ab的投影
inline Point GetLineProjection(Point P, Point A, Point B)
{
    Vector v = B-A;
    return A+v*(Dot(v, P-A) / Dot(v, v));
}


//点到直线距离
inline double DistanceToLine(Point P, Point A, Point B)
{
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1); // 如果不取绝对值，得到的是有向距离
}
//点在p线段上(包括端点)
inline bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) <= 0;
}
// 过两点p1, p2的直线一般方程ax+by+c=0
// (x2-x1)(y-y1) = (y2-y1)(x-x1)
inline void getLineGeneralEquation(Point p1, Point p2, double& a, double& b, double &c)
{
    a = p2.y-p1.y;
    b = p1.x-p2.x;
    c = -a*p1.x - b*p1.y;
}
//点到线段距离
double DistanceToSegment(Point p, Point a, Point b)
{
    if(a == b) return Length(p-a);
    Vector v1 = b-a, v2 = p-a, v3 = p-b;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}
//两线段最近距离
inline double dis_pair_seg(Point p1, Point p2, Point p3, Point p4)
{
    return min(min(DistanceToSegment(p1, p3, p4), DistanceToSegment(p2, p3, p4)),
               min(DistanceToSegment(p3, p1, p2), DistanceToSegment(p4, p1, p2)));
}
//线段相交判定
inline bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
           c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}
// 有向直线。它的左边就是对应的半平面
struct Line
{
    Point p;    // 直线上任意一点
    Vector v;   // 方向向量
    double ang; // 极角，即从x正半轴旋转到向量v所需要的角（弧度）
    Line() {}
    Line(Point P, Vector v):p(P),v(v)
    {
        ang = atan2(v.y, v.x);
    }
    inline bool operator < (const Line& L) const
    {
        return ang < L.ang;
    }
    inline Point point(double t)
    {
        return p + v * t;
    }
    inline Line move(double d)
    {
        return Line(p + Normal(v) * d, v);
    }
    inline void read()
    {
        Point q;
        p.read(), q.read();
        v = q - p;
        ang = atan2(v.y, v.x);
    }
};
//两直线交点
inline Point GetLineIntersection(Line a, Line b)
{
    return GetLineIntersection(a.p, a.v, b.p, b.v);
}


// 点p在有向直线L的左边（线上不算）
inline bool OnLeft(const Line& L, const Point& p)
{
    return Cross(L.v, p-L.p) > 0;
}
// 半平面交主过程
vector<Point> HalfplaneIntersection(vector<Line> L)
{
    int n = L.size();
    sort(L.begin(), L.end()); // 按极角排序
    int first, last;         // 双端队列的第一个元素和最后一个元素的下标
    vector<Point> p(n);      // p[i]为q[i]和q[i+1]的交点
    vector<Line> q(n);       // 双端队列
    vector<Point> ans;       // 结果
    q[first=last=0] = L[0];  // 双端队列初始化为只有一个半平面L[0]
    for(int i = 1; i < n; i++)
    {
        while(first < last && !OnLeft(L[i], p[last-1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps)   // 两向量平行且同向，取内侧的一个
        {
            last--;
            if(OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last-1])) last--; // 删除无用平面
    if(last - first <= 1) return ans; // 空集
    p[last] = GetLineIntersection(q[last], q[first]); // 计算首尾两个半平面的交点
    // 从deque复制到输出中
    for(int i = first; i <= last; i++) ans.push_back(p[i]);
    return ans;
}
double PolygonArea(vector<Point> p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}
#define maxn 500005
int n;
Point p[maxn];
vector<Line> A;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)scanf("%lf%lf",&p[i].x,&p[i].y);
	for(int i=0;i<n;++i)
	{
		A.push_back(Line(p[(i+1)%n],p[i]-p[(i+1)%n]));
	}
	vector<Point> P=HalfplaneIntersection(A);
	double ans=PolygonArea(P);
	printf("%.10f\n",ans);
}