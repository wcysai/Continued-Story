#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-9;
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
//线段相交判定
inline bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2)
{
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
           c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) <= 0 && dcmp(c3)*dcmp(c4) <= 0;
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
/***********多边形**************/
double PolygonArea(vector<Point> p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}
#define maxn 15
int n,m; 
Polygon A,B;
Vector da,db;
Polygon Polymov(Polygon A,Vector v)
{
	Polygon res;res.clear();
	for(Point u:A)res.push_back(u+v);
	return res;
}
double calc(double t)
{
	Polygon C=Polymov(A,da*t);
	vector<Line> S;S.clear();
	for(int i=0;i<n;++i)S.push_back(Line(C[(i+1)%n],C[i]-C[(i+1)%n]));
	for(int i=0;i<m;++i)S.push_back(Line(B[(i+1)%m],B[i]-B[(i+1)%m]));
	vector<Point> T=HalfplaneIntersection(S);
	return max(0.0,PolygonArea(T));
}
int main()
{
	A.clear();B.clear(); 
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		Point p;
		p.read();
		A.push_back(p);
	}
	da.read();
	scanf("%d",&m);
	for(int i=0;i<m;++i)
	{
		Point p;
		p.read();
		B.push_back(p); 
	}
	db.read();
	da=da-db;
	db=Vector(0,0)-da;
	double mint=1e9,maxt=0;
	for(int i=0;i<n;++i)
	{
		for(int j=0;j<m;++j)if(dcmp(Cross(da,B[(j+1)%m]-B[j]))!=0)
		{
			Point u=GetLineIntersection(A[i],da,B[j],B[(j+1)%m]-B[j]);
			if(!SegmentProperIntersection(A[i],u,B[j],B[(j+1)%m]))continue;
			if(dcmp(Dot(u-A[i],da))<0)continue;
			double t=Length(u-A[i])/Length(da);
			mint=min(mint,t);maxt=max(maxt,t);
		}
	}
	for(int i=0;i<m;++i)
	{
		for(int j=0;j<n;++j)if(dcmp(Cross(db,A[(j+1)%n]-A[j]))!=0)
		{
			Point u=GetLineIntersection(B[i],db,A[j],A[(j+1)%n]-A[j]);
			if(!SegmentProperIntersection(B[i],u,A[j],A[(j+1)%n]))continue;
			if(dcmp(Dot(u-B[i],db))<0)continue;
			double t=Length(u-B[i])/Length(db);
			mint=min(mint,t);maxt=max(maxt,t);
		}
	}
	if(dcmp(mint-maxt)>0)
	{
		puts("never");
	}
	else
	{
		double l=mint,r=maxt;
		for(int cnt=1;cnt<=100;++cnt)
		{
			double m1=l+(r-l)/3,m2=r-(r-l)/3;
			if(dcmp(calc(m1)-calc(m2))<0)l=m1;
			else r=m2;
		}
		printf("%.10f\n",l);
	}
}