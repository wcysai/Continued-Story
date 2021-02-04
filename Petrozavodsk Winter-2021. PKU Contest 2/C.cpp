#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef vector <int> VI;
const int INF = 0x3f3f3f3f;
const double eps = 1e-9;
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

struct Circle
{
    Point c;
    double r;
    Circle() {}
    Circle(Point c, double r):c(c), r(r) {}
    inline Point point(double a) //根据圆心角求点坐标
    {
        return Point(c.x+cos(a)*r, c.y+sin(a)*r);
    }
    inline void read()
    {
        scanf("%lf%lf%lf", &c.x, &c.y, &r);
    }
};

//点在p线段上(包括端点)
inline bool OnSegment(Point p, Point a1, Point a2)
{
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) <= 0;
}

//求a点到b点(逆时针)在的圆上的圆弧长度
double DisOnCircle(Point a, Point b, Circle C)
{
    double ang1 = angle(a - C.c);
    double ang2 = angle(b - C.c);
    if (ang2 < ang1) ang2 += 2 * PI;
    return C.r * (ang2 - ang1);
}

//直线与圆交点 返回个数
int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol)
{
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
    double delta = f*f - 4*e*g; // 判别式
    if(dcmp(delta) < 0) return 0; // 相离
    if(dcmp(delta) == 0)
    {
        // 相切
        t1 = t2 = -f / (2 * e);
        sol.push_back(L.point(t1));
        return 1;
    }
    // 相交
    t1 = (-f - sqrt(delta)) / (2 * e);
    sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2 * e);
    sol.push_back(L.point(t2));
    return 2;
}

// 过点p到圆C的切点
int getTangentPoints(Point p, Circle C, vector<Point>& v)
{
    Vector u = C.c - p;
    double dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0)   // p在圆上，只有一条切线
    {
        v.push_back(p);
        return 1;
    }
    else
    {
    	//assert();
        double ang = asin(min(1.0,max(-1.0,C.r / dist)));
        double d = sqrt(dist * dist - C.r * C.r);
        v.push_back(p + Unit(Rotate(u, -ang)) * d);
        v.push_back(p + Unit(Rotate(u, +ang)) * d);
        return 2;
    }
}
int T;
Point A,B;
Circle O;
inline double calc(double ang)
{
	Point X=O.point(ang);
	return Length(A-X)+Length(B-X);
}
double work()
{
	double l=atan2(A.y,A.x),r=atan2(B.y,B.x);
	if(l>r)swap(l,r);
	if(r-l>PI+eps)l+=2*PI;
	if(l>r)swap(l,r);
	int cnt=0;
	while(++cnt<=120)
	{
		double m1=l+(r-l)/3,m2=r-(r-l)/3;
		if(calc(m1)<calc(m2))r=m2;
		else l=m1;
	}
	return calc(l); 
}
int main()
{
	scanf("%d",&T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y,&O.c.x,&O.c.y,&O.r);
		A.x-=O.c.x;A.y-=O.c.y;B.x-=O.c.x;B.y-=O.c.y;
		O.c.x=0;O.c.y=0;
		vector<Point> I;I.clear();
		double t1,t2;
		int num=getLineCircleIntersection(Line(A,B-A),O,t1,t2,I);
		double ans=1e18;
		if(num==0)
		{
			ans=work();
		}
		else if(num==1)
		{
			ans=work();
		}
		else
		{
			if(OnSegment(I[0],A,B)&&OnSegment(I[1],A,B))
			{
				vector<Point> U,V;
				U.clear();V.clear();
				int s1=getTangentPoints(A,O,U);
				int s2=getTangentPoints(B,O,V);
				for(Point u:U)
					for(Point v:V)
					{
						ans=min(ans,Length(A-u)+Length(B-v)+min(DisOnCircle(u,v,O),DisOnCircle(v,u,O)));
					}
			}
			else
			{
				ans=work();
			}
		}
		printf("%.3f\n",ans);
	}
}